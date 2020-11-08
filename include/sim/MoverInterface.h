#ifndef MOVER_INTERFACE_h
#define MOVER_INTERFACE_h

#include "InertialData.h"

namespace vector
{
    namespace sim
    {
        class MoverInterface
        {
            public:
                /**
                 * @brief Causes the Mover to update its PositionalData based on its speed, heading etc.
                 * 
                 */
                virtual void Move() = 0;

                /**
                 * @brief Set a new heading (0-359) for this Mover object.
                 *          The Mover will slew to the new heading based on its turn speed.
                 * 
                 * @param newHeading The new heading the Mover will slew to
                 */
                virtual void SetNewHeading(const angle newHeadingDegrees) = 0;

                /**
                 * @brief Set the initial position of this Mover
                 * 
                 * @param initialPosition this Mover's initial position
                 * @return true if the initial position is valid
                 * @return false if the initial position is not valid
                 */
                virtual bool SetInitialInertialData(const InertialData initialInertialData) = 0;

                /**
                 * @brief Get the PositionalData for this Mover
                 * 
                 * @return PositionalData The PositionalData of this Mover
                 */
                virtual InertialData GetInertialData() const = 0;
        };
    }
}

#endif // MOVER_INTERFACE_h