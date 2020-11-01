#ifndef FIGHTER_MOVER_H
#define FIGHTER_MOVER_H

#include "MoverInterface.h"

#include <mutex>

namespace vector
{
    namespace sim
    {
        class FighterMover : MoverInterface
        {
            public:
                
                /**
                 * @brief Default constructor
                 * 
                 */
                FighterMover::FighterMover() = default;

                /**
                 * @brief Default Destructor
                 * 
                 */
                virtual FighterMover::~FighterMover() = default;

                void Move();

                void SetNewHeading(const unsigned short newHeadingDegrees);

                bool SetInitialPosition(const PositionalData initialPosition) override;

                PositionalData GetPositionalData() const override;

            private:
                PositionalData m_Position;
                mutable std::mutex m_PositionMutex;    
        };
    }
}

#endif // FIGHTER_MOVER_H