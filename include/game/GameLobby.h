#ifndef GAME_LOBBY_H
#define GAME_LOBBY_H

#include "game/GamePhase.h"
#include "game/GamePhaseManager.h"
#include "game/GameTypes.h"
#include "game/GameConstants.h"
#include "game/PlayerInterface.h"

#include <atomic>
#include <memory>
#include <mutex>

namespace vector
{
    namespace game
    {
        class GameLobby : public GamePhase
        {
            public:
                GameLobby(std::shared_ptr<vector::game::GamePhaseManager> mgr);

                virtual ~GameLobby();

                /**
                 * @brief Start this Phase
                 * 
                 * @return true if the Phase was successfully started
                 * @return false if the Phase was not able to be Started
                 */
                bool Start() override;

                /**
                 * @brief Stop this phase
                 * 
                 * @return true if the Phase was successfully stopped
                 * @return false if the Phase was not able to be stopped
                 */
                bool Stop() override;

                /**
                 * @brief Set the GameType of this Game
                 * 
                 * @param gameType GameType of this Game
                 * @return true if the GameType was successfully set
                 * @return false if an UNK GameType is passed, or the Game is in a state where GameType cannot be set
                 */
                bool SetGameType(const vector::game::GAME_TYPE gameType);

                /**
                 * @brief Get the GameType of this Game
                 * 
                 * @return vector::game::GAME_TYPE GameType of this game
                 */
                vector::game::GAME_TYPE GetGameType();

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
                bool IsReadyToStartGame() const;

                /**
                 * @brief Update the clients of the current Lobby state
                 */
                void UpdateLobbyState();

            private:

                /**
                 * @brief Run this phase of the game
                 * 
                 */
                void Run();

                /**
                 * @brief Get the current state of the Lobby
                 * 
                 * @return vector::game::LobbyState the current lobby state
                 */
                vector::game::LobbyState GetLobbyState();

                std::shared_ptr<vector::game::GamePhaseManager> m_GamePhaseMgrPtr;
                mutable std::mutex m_LobbyMutex;
                uint8_t m_NumPlayerSlots{MIN_NUM_PLAYERS};
                std::atomic<bool> m_Started{false};
                std::atomic<bool> m_Ended{false};
                vector::game::GAME_TYPE m_GameType{vector::game::GAME_TYPE::UNK};
                std::unordered_map<std::string, std::shared_ptr<vector::game::PlayerInterface>> m_PlayerMap;
                std::unique_ptr<std::thread> m_LobbyThreadPtr{nullptr};
        }; // class GameLobby
    } // namespace game
} // namespace vector

#endif // GAME_LOBBY_H