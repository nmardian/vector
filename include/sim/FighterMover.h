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
                /**
                 * @brief Constructor
                 * 
                 * @param performanceValues Performance characteristics of this FighterMover
                 */
                FighterMover(MoverParams performanceValues);

                FighterMover(const FighterMover&) = delete;
                FighterMover& operator=(const FighterMover&) = delete;

                /**
                 * @brief Default move constructor
                 * 
                 */
                FighterMover(FighterMover&&) = delete;

                /**
                 * @brief Default move operator
                 * 
                 * @return FighterMover& 
                 */
                FighterMover& operator=(FighterMover&&) = delete;

                /**
                 * @brief Default Destructor
                 * 
                 */
                virtual FighterMover::~FighterMover() = default;

                void Move();

                bool SetNewHeading(const angle newHeadingDegrees);

                bool SetInitialInertialData(const InertialData initialInertialData) override;

                InertialData GetInertialData() const override;

                FighterMover() = default;
                

            private:
                InertialData m_InertialData;
                mutable std::mutex m_PositionMutex;

                MoverParams m_PerformanceValues;

                angle m_DesiredHeading;
        };
    }
}

#endif // FIGHTER_MOVER_H