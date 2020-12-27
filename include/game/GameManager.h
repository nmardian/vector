#ifndef GAME_MANAGER_H
#define GAME_MANAGER_H

#include "game/GameTypes.h"
#include "game/PlayerInterface.h"
#include "game/GameConstants.h"
#include "game/GameSettingsInterface.h"
#include "sim/GameEngine.h"

#include <vector>
#include <memory>
#include <unordered_map>
#include <mutex>
#include <atomic>
#include <thread>
#include <functional>

namespace vector
{
    namespace game
    {
        class GameManager
        {
            public:
                /**
                 * @brief Default construtor
                 * 
                 */
                GameManager(std::unique_ptr<vector::sim::GameEngine> gameEnginePtr, std::unique_ptr<vector::game::GameSettingsInterface> gameSettingsPtr)
                    : m_GameEnginePtr(std::move(gameEnginePtr))
                    , m_GameSettingsPtr(std::move(gameSettingsPtr))
                {
                }
                
                /**
                 * @brief Default destructor
                 * 
                 */
                virtual ~GameManager() = default;

                /**
                 * @brief Set the GameType of this Game
                 * 
                 * @param gameType GameType of this Game
                 * @return true if the GameType was successfully set
                 * @return false if an UNK GameType is passed, or the Game is in a state where GameType cannot be set
                 */
                bool SetGameType(const vector::game::GAME_TYPE gameType);

                /**
                 * @brief Set the number of Player slots in the Game
                 * 
                 * @param numPlayers The number of Player slots in the Game
                 * @return true if the number of Player slots is between Min and Max allowed or the Game has not started
                 * @return false if the number of Player slots is outside Min and Max allowed or the Game has started
                 */
                bool SetNumPlayerSlots(const uint8_t numPlayerSlots);

                /**
                 * @brief Get the number of Player slots in the Game
                 * 
                 * @return uint8_t the number of Player slots in the game
                 */
                uint8_t GetNumPlayerSlots() const;

                /**
                 * @brief Add a Player to this game
                 * 
                 * @param player The Player to be added to this Game
                 * @return true if the Player was successfully added
                 * @return false if the Player was not added
                 */
                bool AddPlayer(std::shared_ptr<vector::game::PlayerInterface> playerPtr);

                /**
                 * @brief Set the UnitData for a team.
                 * Unit data is the callsign and UNIT_TYPE of the team's units
                 * 
                 * @param teamID    ID of the Team whose units are being set
                 * @param unitData  vector of UnitData representing this Team's units
                 * 
                 * @return true if the UnitData is successfully set
                 * @return false if the UnitData could not be set
                 */
                bool SetUnitData(const vector::sim::team_ID teamID, const std::vector<vector::game::UnitData> unitData);

                /**
                 * @brief Determine whether the Game is in a state suitable for starting
                 * Game has not already started
                 * All Player slots are filled
                 * All Players have indicated they are ready
                 * GameType is selected
                 * Unit data has been set
                 * 
                 * @return true 
                 * @return false 
                 */
                bool IsReadyToStart() const;

                /**
                 * @brief Start the Game
                 * 
                 * @return true if the Game was successfully started
                 * @return false if the Game was not able to be Started, if some component of the Game had not been set yet
                 */
                bool Start();

                /**
                 * @brief Stop the Game
                 * 
                 * @return true if the Game was successfully stopped
                 * @return false if the game was not sucessfully stopped
                 */
                bool Stop();

                // delete copy and move constructors and operators
                GameManager(const GameManager&) = delete;
                GameManager& operator=(const GameManager&) = delete;
                GameManager(GameManager&&) = delete;
                GameManager& operator=(GameManager&&) = delete;

            private:

                /**
                 * @brief Function registered with Clients for them to invoke to input Commands
                 * 
                 * @param playerID the ID of the Player who issued the command
                 * @param cmd   the command issued by the Player
                 * @return true if the command is successfully executed in the simulation
                 * @return false if the command is unsuccessfully executed in the simulation
                 */
                bool InputCommand(const std::string playerID, const vector::util::Command cmd);

                /**
                 * @brief Map user issued commands to commands acceptable to the GameEngine
                 * Command.subject is the Player's ID + the input Subject to allow for Players to have
                 * units with the same callsign
                 * 
                 * @param playerID The ID of the Player issuing the command
                 * @param cmd The command issued by the Player
                 * @return vector::util::Command A command suitable for the GameEngine
                 */
                vector::util::Command DeconflictCommand(const std::string playerID, const vector::util::Command cmd);

                /**
                 * @brief Get the GameState from the GameEngine
                 * 
                 * @return the current GameState
                 */
                void UpdateGameState();

                /**
                 * @brief Game thread
                 * 
                 */
                void Run();

                /**
                 * @brief Randomly generate callsigns for unset units
                 */
                void AssignCallsignsAsNeeded();

                vector::game::GAME_TYPE m_GameType{vector::game::GAME_TYPE::UNK};
                std::unordered_map<std::string, std::shared_ptr<vector::game::PlayerInterface>> m_PlayerMap;
                uint8_t m_NumPlayerSlots{MIN_NUM_PLAYERS};
                std::atomic<bool> m_Started{false};
                std::atomic<bool> m_Ended{false};
                std::unordered_map<vector::sim::team_ID, bool> m_UnitDataSetMap;
                mutable std::mutex m_GameSetupMutex;
                std::unique_ptr<vector::sim::GameEngine> m_GameEnginePtr{nullptr};
                std::unique_ptr<std::thread> m_GameThreadPtr{nullptr};
                std::unique_ptr<GameSettingsInterface> m_GameSettingsPtr{nullptr};

        }; // class GameManager
    } // namespace game
} // namespace vector

#endif // GAME_MANAGER_H