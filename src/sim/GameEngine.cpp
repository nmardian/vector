#include "sim/GameEngine.h"
#include <stdexcept>

namespace vector
{
    namespace sim
    {
        bool GameEngine::AddMover(std::shared_ptr<MoverInterface> moverPtr)
        {
            if(m_AllMoversMap.find(moverPtr->GetID()) == m_AllMoversMap.end())
            {
                m_AllMoversMap.emplace(moverPtr->GetID(), std::move(moverPtr));
                return true;
            }

            return false;
        }

        std::shared_ptr<MoverInterface> GameEngine::GetMover(const std::string& moverID)
        {
            auto moverItr = m_AllMoversMap.find(moverID);

            if(moverItr != m_AllMoversMap.end())
            {
                return moverItr->second;
            }

            return nullptr;
        }

        bool GameEngine::InputCommand(util::Command cmd)
        {
            auto subject = m_AllMoversMap.find(cmd.subject);
            bool result = true;

            if(subject != m_AllMoversMap.end())
            {
                switch(cmd.command)
                {
                    case vector::util::COMMAND_TYPE::VECTOR:
                    {
                        try
                        {
                            subject->second->SetNewHeading(std::stoi(cmd.object));
                        }
                        catch (const std::invalid_argument& e)
                        {
                            result = false;
                        }
                        catch(const std::out_of_range& e)
                        {
                            result = false;
                        }
                        break;
                    }
                    case vector::util::COMMAND_TYPE::IDENTIFY:
                    {
                        break;
                    }
                    case vector::util::COMMAND_TYPE::AQUIRE:
                    {
                        break;
                    }
                    case vector::util::COMMAND_TYPE::LAUNCH:
                    {
                        break;
                    }
                    case vector::util::COMMAND_TYPE::UNK:
                    default:
                    break;
                }
            }
            else
            {
                result = false;
            }

            return result;
        }

        void GameEngine::Tick()
        {
            std::vector<std::string> markForRemove;
            for(auto mapItr : m_AllMoversMap)
            {
                if(mapItr.second->GetStatus())
                {
                    mapItr.second->Move();
                }
                else
                {
                    markForRemove.push_back(mapItr.first);
                }

                for(auto itr : markForRemove)
                {
                    auto toRemove = m_AllMoversMap.find(itr);
                    if(toRemove != m_AllMoversMap.end())
                    {
                        m_AllMoversMap.erase(toRemove);
                    }
                }
                
            }
        }
    } // namespace sim
} // namespace vector