#ifndef POSITIONAL_DATA_H
#define POSITIONAL_DATA_H

#include "SimTypes.h"

namespace vector
{
    namespace sim
    {
        /**
         * @brief Struct to store a Mover's intertial data
         * 
         */
        struct InertialData
        {
            angle curHeading{0};
            speed curSpeed{0};
            coord xCoord{0.0};
            coord yCoord{0.0};
        };
    }
}

#endif // POSITIONAL_DATA_H