#ifndef PLAYER_INTERFACE_H
#define PLAYER_INTERFACE_H

#include "game/GameTypes.h"
#include "sim/GameState.h"
#include "util/Command.h"

#include <functional>

namespace vector
{
    namespace game
    {
        class PlayerInterface
        {
            public:
                virtual ~PlayerInterface() = default;

                /**
                 * @brief Get the unique ID of the Player
                 * 
                 * @return std::string unique ID of the Player
                 */
                virtual std::string GetPlayerID() const = 0;

                /**
                 * @brief Get the ID of this Player's team
                 * 
                 * @return the ID of this Player's team 
                 */
                virtual vector::game::team_ID GetTeamID() const  = 0;

                /**
                 * @brief Is the Player ready to begin the Game
                 * 
                 * @return true if the Player has indicated they are ready
                 * @return false if the Player has not indicated they are ready
                 */
                virtual bool IsReady() const = 0;

                /**
                 * @brief Update the locally held GameState, to be pushed to the client connection
                 * 
                 * @param gameState the current locall held game state
                 */
                virtual void UpdateGameState(const vector::sim::GameState gameState) = 0;

                /**
                 * @brief Register the function Clients will invoke to input commands
                 *
                 */
                virtual void RegisterCommandFunction(std::function<bool (const std::string playerID, const vector::util::Command cmd)>) = 0;
        }; // class PlayerInterface
    } // namespace game
} // namespace vector

#endif // PLAYER_INTERFACE_H