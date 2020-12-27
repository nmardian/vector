#include "sim/FighterMover.h"
#include "sim/SimConstants.h"
#include "util/MathUtil.h"

#include <algorithm>

namespace vector
{
    namespace sim
    {
        FighterMover::FighterMover(const std::string& ID, const uint8_t teamID, MoverParams performanceValues)
            : m_InertialData()
            , m_PerformanceValues(performanceValues)
            , m_DesiredHeading(0)
            , m_ID(ID)
            , m_Status(true)
            , m_TeamID(teamID)
        {
        }

        std::string FighterMover::GetID() const
        {
            return m_ID;
        }

        void FighterMover::Move()
        {
            InertialData newInertial = m_InertialData;
            if(m_InertialData.curHeading != m_DesiredHeading)
            {
                angle newHeading = m_InertialData.curHeading;

                // turn right
                if( (HEADING_FULL_CIRCLE + m_InertialData.curHeading - m_DesiredHeading) > HEADING_HALF_CIRCLE)
                {
                    newHeading = (HEADING_FULL_CIRCLE + m_InertialData.curHeading + FIGHTER_TURN_RATE) % HEADING_FULL_CIRCLE;
                }
                // turn left
                else
                {
                    newHeading = (HEADING_FULL_CIRCLE + m_InertialData.curHeading - FIGHTER_TURN_RATE) % HEADING_FULL_CIRCLE;
                }

                newInertial.curHeading = newHeading;
                
                // turn decreases speed
                newInertial.curSpeed = std::max(SPEED_MIN, (m_InertialData.curSpeed - FIGHTER_ACCL_DCCL));
            }
            else
            {
                // flying straight increases speed
                newInertial.curSpeed = std::min(SPEED_MAX, (m_InertialData.curSpeed + FIGHTER_ACCL_DCCL));
            }
            
            newInertial.xCoord = m_InertialData.xCoord + vector::util::MathUtil::GetXComponentOfSpeed(m_InertialData.curSpeed, m_InertialData.curHeading);;
            newInertial.yCoord = m_InertialData.yCoord + vector::util::MathUtil::GetYComponentOfSpeed(m_InertialData.curSpeed, m_InertialData.curHeading);;

            if(newInertial.xCoord < vector::sim::X_COORD_MIN || newInertial.xCoord > vector::sim::X_COORD_MAX ||
                newInertial.yCoord < vector::sim::Y_COORD_MIN || newInertial.yCoord > vector::sim::Y_COORD_MAX)
            {
                m_Status = false;
            }

            m_InertialData = newInertial;
        }

        bool FighterMover::SetNewHeading(const angle newHeadingDegrees)
        {
            if(newHeadingDegrees >= HEADING_MIN && newHeadingDegrees <= HEADING_MAX)
            {
                m_DesiredHeading = newHeadingDegrees;
                return true;
            }

            return false;
        }

        bool FighterMover::SetInitialInertialData(const InertialData initialInertialData)
        {
            if(initialInertialData.curHeading >= HEADING_MIN && initialInertialData.curHeading <= HEADING_MAX && 
                initialInertialData.curSpeed >= SPEED_MIN && initialInertialData.curSpeed <= FIGHTER_SPEED_MAX &&
                initialInertialData.xCoord >= X_COORD_MIN && initialInertialData.yCoord >= Y_COORD_MIN &&
                initialInertialData.xCoord <= X_COORD_MAX && initialInertialData.yCoord <= Y_COORD_MAX)
            {
                m_InertialData.curHeading = initialInertialData.curHeading;
                m_InertialData.curSpeed = initialInertialData.curSpeed;
                m_InertialData.xCoord = initialInertialData.xCoord;
                m_InertialData.yCoord = initialInertialData.yCoord;

                m_DesiredHeading = m_InertialData.curHeading;

                return true;
            }

            return false;
        }

        InertialData FighterMover::GetInertialData() const
        {
            return m_InertialData;
        }

        void FighterMover::Destroy()
        {
            m_Status = false;
        }
        
        bool FighterMover::GetStatus() const
        {
            return m_Status;
        }

        vector::sim::team_ID FighterMover::GetTeam() const
        {
            return m_TeamID;
        }

        std::string FighterMover::ToString() const
        {
            return "" + m_ID + "\nx: " + std::to_string(m_InertialData.xCoord) + "\ny: " + std::to_string(m_InertialData.yCoord) +
                            "\nheading: " + std::to_string(m_InertialData.curHeading) + "\nspeed: " + std::to_string(m_InertialData.curSpeed);

        }
    } // namespace sim
} // namespace vector

