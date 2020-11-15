#include "sim/GameEngine.h"

namespace vector
{
    namespace sim
    {
        bool GameEngine::AddMover(std::shared_ptr<MoverInterface> moverPtr)
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
            for(auto mapItr : m_AllMoversMap)
            {
                mapItr.second->Move();
            }
        }
    } // namespace sim
} // namespace vector