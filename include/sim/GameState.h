#ifndef GAME_STATE_H
#define GAME_STATE_H

#include "sim/InertialData.h"
#include "sim/SimTypes.h"

#include "game/GameTypes.h"

#include <vector>
#include <string>

namespace vector
{
    namespace sim
    {
        /**
         * @brief Struct to store a Mover's state
         * 
         */
        struct MoverState
        {
            std::string ID;
            vector::sim::team_ID teamID;
            vector::sim::InertialData inertialData;
        }; // struct MoverState

        /**
         * @brief Struct to store a Game's state
         * 
         */
        struct GameState
        {
            std::vector<MoverState> moverList;
        }; // struct GameState
    } // namespace sim
} // namespace vector

#endif // GAME_STATE_H