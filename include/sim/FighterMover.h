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
                FighterMover(MoverParams performanceValues);

                /**
                 * @brief Default Destructor
                 * 
                 */
                virtual FighterMover::~FighterMover() = default;

                void Move();

                void SetNewHeading(const angle newHeadingDegrees);

                bool SetInitialInertialData(const InertialData initialInertialData) override;

                InertialData GetInertialData() const override;

                FighterMover() = delete;
                FighterMover(const FighterMover&) = delete;
                FighterMover& operator=(const FighterMover&) = delete;
                FighterMover(FighterMover&&) = delete;
                FighterMover& operator=(FighterMover&&) = delete;

            private:
                InertialData m_InertialData;
                mutable std::mutex m_PositionMutex;

                MoverParams m_PerformanceValues;

                angle m_DesiredHeading;
        };
    }
}

#endif // FIGHTER_MOVER_H