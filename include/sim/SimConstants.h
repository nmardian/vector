#ifndef SIM_CONSTANTS_H
#define SIM_CONSTANTS_H

#include "SimTypes.h"

namespace vector
{
    namespace sim
    {
        static const unsigned short HEADING_MIN = 0;
        static const unsigned short HEADING_MAX = 359;
        static const speed SPEED_MIN = 0.0;
        static const speed SPEED_MAX = 838.0;
        static const angle DEFAULT_TURN_RATE = 5;
        static const coord X_COORD_MIN = 0.0;
        static const coord X_COORD_MAX = 375500.0;
        static const coord Y_COORD_MIN = 0.0;
        static const coord Y_COORD_MAX = 375500.0;
        
    } // namespace sim
}  // namespace vector

#endif // SIM_CONSTANTS_H