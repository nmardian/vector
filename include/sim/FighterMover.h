#ifndef FIGHTER_MOVER_H
#define FIGHTER_MOVER_H

#include "MoverInterface.h"

#include "SimTypes.h"
#include "SimParams.h"

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
                 * @param ID                This Mover's unique ID
                 * @param teamID            The ID of the team this Mover belongs to
                 * @param performanceValues Performance characteristics of this FighterMover
                 */
                FighterMover(const std::string& ID, const uint8_t teamID, MoverParams performanceValues);

                /**
                 * @brief Default Destructor
                 * 
                 */
                virtual FighterMover::~FighterMover() = default;

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
                 * @brief Mark this Mover are destroyed.
                 * 
                 */
                void Destroy() override;

                /**
                 * @brief Get whether this Mover is destroyed or not
                 * 
                 * @return true if this Mover is functioning
                 * @return false if this mover is destroyed
                 */
                bool GetStatus() const override;

                /**
                 * @brief Get this Mover's team ID
                 * 
                 * @return this Mover's team ID
                 */
                vector::game::team_ID GetTeam() const override;

                /**
                 * @brief Get a string representation of this Mover
                 * 
                 * @return std::string string representation of this Mover
                 */
                std::string ToString() const override;

                FighterMover(const FighterMover&) = delete;
                FighterMover& operator=(const FighterMover&) = delete;
                FighterMover(FighterMover&&) = delete;
                FighterMover& operator=(FighterMover&&) = delete;

            private:
                InertialData m_InertialData;
                MoverParams m_PerformanceValues;
                angle m_DesiredHeading;
                std::string m_ID;
                bool m_Status{true};
                vector::game::team_ID m_TeamID{UNK_TEAM_ID};
        };
    }
}

#endif // FIGHTER_MOVER_H