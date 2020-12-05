#ifndef GAME_MANAGER_H
#define GAME_MANAGER_H

#include "game/GameTypes.h"
#include "game/PlayerInterface.h"

#include <vector>
#include <memory>

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
                GameManager() = default;
                
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
                 * @brief Add a Player to this game
                 * 
                 * @param player The Player to be added to this Game
                 * @return true if the Player was successfully added
                 * @return false if the Player was not added
                 */
                bool AddPlayer(const std::shared_ptr<vector::game::PlayerInterface> playerPtr);

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
                bool SetUnitData(const vector::game::team_ID teamID, const std::vector<vector::game::UnitData> unitData);

                /**
                 * @brief Start the Game
                 * 
                 * @return true if the Game was successfully started
                 * @return false if the Game was not able to be Started, if some component of the Game had not been set yet
                 */
                bool Start();

                // delete copy and move constructors and operators
                GameManager(const GameManager&) = delete;
                GameManager& operator=(const GameManager&) = delete;
                GameManager(GameManager&&) = delete;
                GameManager& operator=(GameManager&&) = delete;

            private:
                vector::game::GAME_TYPE m_GameType{vector::game::GAME_TYPE::UNK};
        }; // class GameManager
    } // namespace game
} // namespace vector

#endif // GAME_MANAGER_H