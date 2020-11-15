#include "sim/GameEngine.h"

namespace vector
{
    namespace sim
    {
        bool GameEngine::AddMover(std::unique_ptr<MoverInterface> moverPtr)
        {
            if(m_AllMoversMap.find(moverPtr->GetID()) != m_AllMoversMap.end())
            {
                m_AllMoversMap.emplace(moverPtr->GetID(), std::move(moverPtr));
                return true;
            }

            return false;
        }

        void GameEngine::Tick()
        {
            // iterate over Movers, call Move
            
            // get each Mover's inertial data

            // pass inertial data to draw-er
        }
    } // namespace sim
} // namespace vector