#ifndef SIM_PARAMS_H
#define SIM_PARAMS_H

#include "SimTypes.h"
#include "SimConstants.h"

namespace vector
{
    namespace sim
    {
        // TODO: These should be read in from config file
        static const speed FIGHTER_SPEED_MAX = 838;
        static const angle FIGHTER_TURN_RATE = 10;
        static const speed FIGHTER_ACCL_DCCL = 5;

        struct MoverParams
        {
            speed maxSpeed{SPEED_MAX};
            angle turnRate{DEFAULT_TURN_RATE};
        };
    } // namespace sim
} // namespace vector

#endif // SIM_PARAMS_H