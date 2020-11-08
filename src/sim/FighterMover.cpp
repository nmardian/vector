#include "sim/FighterMover.h"
#include "sim/SimConstants.h"
#include "util/MathUtil.h"

namespace vector
{
    namespace sim
    {
        FighterMover::FighterMover(MoverParams performanceValues)
            : m_InertialData({0, 0, 0, 0})
            , m_PerformanceValues(performanceValues)
            , m_DesiredHeading(0)
        {
        }

        void FighterMover::Move()
        {
            std::scoped_lock<std::mutex> lock(m_PositionMutex);

            vector::sim::InertialData newInertial = m_InertialData;
            if(m_InertialData.curHeading == m_DesiredHeading)
            {
                newInertial.xCoord = m_InertialData.xCoord + vector::util::MathUtil::GetXComponentOfSpeed(m_InertialData.curSpeed, m_InertialData.curHeading);
                newInertial.yCoord = m_InertialData.yCoord + vector::util::MathUtil::GetYComponentOfSpeed(m_InertialData.curSpeed, m_InertialData.curHeading);
            }
            else
            {
                
            }

            m_InertialData = newInertial;
            
        }

        void FighterMover::SetNewHeading(const angle newHeadingDegrees)
        {
            std::scoped_lock<std::mutex> lock(m_PositionMutex);
        }

        bool FighterMover::SetInitialInertialData(const InertialData initialInertialData)
        {
            // TODO: check for max x and y coords?
            if(initialInertialData.curHeading >= HEADING_MIN && initialInertialData.curHeading <= HEADING_MAX && 
                initialInertialData.curSpeed >= SPEED_MIN && initialInertialData.curSpeed <= BLUE_FIGHTER_SPEED_MAX &&
                initialInertialData.xCoord >= X_COORD_MIN && initialInertialData.yCoord >= Y_COORD_MIN &&
                initialInertialData.xCoord <= X_COORD_MAX && initialInertialData.yCoord <= Y_COORD_MAX)
            {
                std::scoped_lock<std::mutex> lock(m_PositionMutex);

                m_InertialData.curHeading = initialInertialData.curHeading;
                m_InertialData.curSpeed = initialInertialData.curSpeed;
                m_InertialData.xCoord = initialInertialData.xCoord;
                m_InertialData.yCoord = initialInertialData.yCoord;

                return true;
            }

            return false;
        }

        InertialData FighterMover::GetInertialData() const
        {
            std::scoped_lock<std::mutex> lock(m_PositionMutex);

            return m_InertialData;
        }
    } // namespace sim
} // namespace vector

