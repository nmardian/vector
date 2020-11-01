#include "sim/FighterMover.h"
#include "sim/SimConstants.h"

namespace vector
{
    namespace sim
    {
        void FighterMover::Move()
        {
            std::scoped_lock<std::mutex> lock(m_PositionMutex);

            // TODO: implement this       
        }

        void FighterMover::SetNewHeading(const unsigned short newHeadingDegrees)
        {
            std::scoped_lock<std::mutex> lock(m_PositionMutex);
        }

        bool FighterMover::SetInitialPosition(const PositionalData initialPosition)
        {
            // TODO: check for max x and y coords?
            if(initialPosition.heading >= HEADING_MIN && initialPosition.heading <= HEADING_MAX && 
                initialPosition.xCoord >= X_COORD_MIN && initialPosition.yCoord >= Y_COORD_MIN)
            {
                std::scoped_lock<std::mutex> lock(m_PositionMutex);

                m_Position.heading = initialPosition.heading;
                m_Position.xCoord = initialPosition.xCoord;
                m_Position.yCoord = initialPosition.yCoord;

                return true;
            }

            return false;
        }

        PositionalData FighterMover::GetPositionalData() const
        {
            std::scoped_lock<std::mutex> lock(m_PositionMutex);

            return m_Position;
        }
    } // namespace sim
} // namespace vector

