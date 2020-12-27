#ifndef GAME_SETTINGS_INTERFACE_H
#define GAME_SETTINGS_INTERFACE_H

#include "game/GameTypes.h"

#include <stdint.h>

namespace vector
{
    namespace game
    {
        class GameSettingsInterface
        {
            public:
                virtual ~GameSettingsInterface() = default;

                /**
                 * @brief Get the GameType
                 * 
                 * @return vector::game::GAME_TYPE this Game's GameType
                 */
                virtual vector::game::GAME_TYPE GetGameType() const = 0;

                /**
                 * @brief Get the number of Players for this GameType
                 * 
                 * @return uint8_t the number of Players for this GameType
                 */
                virtual uint8_t GetNumPlayers() const = 0;

                /**
                 * @brief Set the number of Players
                 * 
                 * @param numPlayers the number of players to be set
                 * 
                 * @return whether the number of Players was set (ie. between Min and Max players)
                 */
                virtual bool SetNumPlayers(const uint8_t numPlayers) = 0;

                /**
                 * @brief Get the number of Movers per team for this GameType
                 * 
                 * @return uint8_t the number of Movers per team for this GameType
                 */
                virtual uint8_t GetNumMoversPerSide() const = 0;

                /**
                 * @brief Set the number of Movers on each side
                 * 
                 * @param numMoversPerSide the number of Movers on each side
                 * @return true if the number of Movers is between Min and Max
                 * @return false otherwise
                 */
                virtual bool SetNumMoversPerSide(uint8_t numMoversPerSide) = 0;
        }; // class GameSettingsInterface
    } // namespace game
} // namespace vector

#endif // GAME_SETTINGS_INTERFACE_H