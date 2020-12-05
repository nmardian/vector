#ifndef PLAYER_INTERFACE_H
#define PLAYER_INTERFACE_H

#include "game/GameTypes.h"

namespace vector
{
    namespace game
    {
        class PlayerInterface
        {
            public:
                virtual ~PlayerInterface() = default;

                /**
                 * @brief Get the ID of this Player's team
                 * 
                 * @return the ID of this Player's team 
                 */
                virtual vector::game::team_ID GetTeamID() const  = 0;
        }; // class PlayerInterface
    } // namespace game
} // namespace vector

#endif // PLAYER_INTERFACE_H