#ifndef MOVER_INTERFACE_h
#define MOVER_INTERFACE_h

#include "InertialData.h"

#include "game/GameTypes.h"

#include <string>
#include <stdint.h>

namespace vector
{
    namespace sim
    {
        class MoverInterface
        {
            public:
                virtual ~MoverInterface() = default;

                /**
                 * @brief Get this Mover's unique ID
                 * 
                 * @return std::string this Mover's unique ID
                 */
                virtual std::string GetID() const = 0;

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
                 * @return true if the heading was successfully updated, false otherwise
                 */
                virtual bool SetNewHeading(const angle newHeadingDegrees) = 0;

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

                /**
                 * @brief Mark this Mover as destroyed.
                 * 
                 */
                virtual void Destroy() = 0;

                /**
                 * @brief Get whether this Mover is destroyed or not
                 * 
                 * @return true if this Mover is functioning
                 * @return false if this mover is destroyed
                 */
                virtual bool GetStatus() const = 0;

                /**
                 * @brief Get this Mover's team ID
                 * 
                 * @return this Mover's team ID
                 */
                virtual vector::game::team_ID GetTeam() const = 0;

                /**
                 * @brief Get a string representation of this Mover
                 * 
                 * @return std::string string representation of this Mover
                 */
                virtual std::string ToString() const = 0;
        };
    }
}

#endif // MOVER_INTERFACE_h