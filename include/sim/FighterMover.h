#ifndef FIGHTER_MOVER_H
#define FIGHTER_MOVER_H

#include "MoverInterface.h"

#include "SimTypes.h"
#include "SimParams.h"
#include <mutex>

namespace vector
{
    namespace sim
    {
        class FighterMover : MoverInterface
        {
            public:
                
                FighterMover() = default;
                
                /**
                 * @brief Constructor
                 * 
                 * @param performanceValues Performance characteristics of this FighterMover
                 */
                FighterMover(MoverParams performanceValues);

                /**
                 * @brief Default Destructor
                 * 
                 */
                virtual FighterMover::~FighterMover() = default;

                /**
                 * @brief Set this Mover's unique ID
                 * 
                 * @param id this Mover's unique ID
                 */
                void SetID(const std::string& id) override;

                /**
                 * @brief Get this Mover's unique ID
                 * 
                 * @return std::string this Mover's unique ID
                 */
                std::string GetID() const override;

                /**
                 * @brief Causes the Mover to update its PositionalData based on its speed, heading etc.
                 * 
                 */
                void Move() override;

                /**
                 * @brief Set a new heading (0-359) for this Mover object.
                 *          The Mover will slew to the new heading based on its turn speed.
                 * 
                 * @param newHeading The new heading the Mover will slew to
                 * @return true if the heading was successfully updated, false otherwise
                 */
                bool SetNewHeading(const angle newHeadingDegrees) override;

                /**
                 * @brief Set the initial position of this Mover
                 * 
                 * @param initialPosition this Mover's initial position
                 * @return true if the initial position is valid
                 * @return false if the initial position is not valid
                 */
                bool SetInitialInertialData(const InertialData initialInertialData) override;

                /**
                 * @brief Get the PositionalData for this Mover
                 * 
                 * @return PositionalData The PositionalData of this Mover
                 */
                InertialData GetInertialData() const override;

                /**
                 * @brief Get a string representation of this Mover
                 * 
                 * @return std::string string representation of this Mover
                 */
                virtual std::string ToString() const override;

                FighterMover(const FighterMover&) = delete;
                FighterMover& operator=(const FighterMover&) = delete;
                FighterMover(FighterMover&&) = delete;
                FighterMover& operator=(FighterMover&&) = delete;

            private:
                InertialData m_InertialData;
                mutable std::mutex m_PositionMutex;
                MoverParams m_PerformanceValues;
                angle m_DesiredHeading;
                std::string m_ID;
        };
    }
}

#endif // FIGHTER_MOVER_H