#include "game/GameManager.h"


namespace vector
{
    namespace game
    {
        bool GameManager::SetGameType(const vector::game::GAME_TYPE gameType)
        {
            std::scoped_lock<std::mutex> lock(m_GameSetupMutex);
            if(gameType != vector::game::GAME_TYPE::UNK && !m_Started)
            {
                m_GameType = gameType;
                return true;
            }
            return false;
        }

        bool GameManager::SetNumPlayerSlots(const uint8_t numPlayerSlots)
        {
            std::scoped_lock<std::mutex> lock(m_GameSetupMutex);
            if(!m_Started && numPlayerSlots >= MIN_NUM_PLAYERS && numPlayerSlots <= MAX_NUM_PLAYERS)
            {
                m_NumPlayerSlots = numPlayerSlots;
                return true;
            }
            return false;
        }

        uint8_t GameManager::GetNumPlayerSlots() const
        {
            std::scoped_lock<std::mutex> lock(m_GameSetupMutex);
            return m_NumPlayerSlots;
        }

        bool GameManager::AddPlayer(std::shared_ptr<vector::game::PlayerInterface> playerPtr)
        {
            std::scoped_lock<std::mutex> lock(m_GameSetupMutex);
            auto playerMapItr = m_PlayerMap.find(playerPtr->GetPlayerID());
            if(!m_Started && playerMapItr == m_PlayerMap.end() && m_PlayerMap.size() < m_NumPlayerSlots)
            {
                m_PlayerMap.emplace(playerPtr->GetPlayerID(), playerPtr);

                playerPtr->RegisterCommandFunction(
                    std::bind(std::mem_fn(&GameManager::InputCommand), this,  std::placeholders::_1, std::placeholders::_2));
                return true;
            }
            return false;
        }

        bool GameManager::SetUnitData(const vector::game::team_ID teamID, const std::vector<vector::game::UnitData> unitData)
        {
            std::scoped_lock<std::mutex> lock(m_GameSetupMutex);
            if(!m_Started)
            {
                return true;
            }
            return false;
        }

        bool GameManager::IsReadyToStart() const
        {
            std::scoped_lock<std::mutex> lock(m_GameSetupMutex);

            if(!m_Started && m_NumPlayerSlots == m_PlayerMap.size() && m_GameType != vector::game::GAME_TYPE::UNK)
            {
                for(auto playerItr : m_PlayerMap)
                {
                    if(!playerItr.second->IsReady())
                    {
                        return false;
                    }
                }
                return true;
            }
            return false;
        }

        bool GameManager::Start()
        {   
            if(!m_Started && IsReadyToStart())
            {
                m_Started = true;

                m_GameThreadPtr = std::make_unique<std::thread>(&GameManager::Run, this);
                
                return true;
            }
            return false;
        }

        bool GameManager::Stop()
        {
            m_Ended = true;

            m_GameThreadPtr->join();

            return true;
        }

        bool GameManager::InputCommand(const std::string playerID, const vector::util::Command cmd)
        {
            vector::util::Command deconflictedCommand;
            
            deconflictedCommand = DeconflictCommand(playerID, cmd);

           return m_GameEnginePtr->InputCommand(deconflictedCommand);
        }

        vector::util::Command GameManager::DeconflictCommand(const std::string playerID, const vector::util::Command cmd)
        {
            vector::util::Command cmdOut;

            cmdOut.command = cmd.command;
            cmdOut.subject = playerID + cmd.subject;
            cmdOut.object = cmd.object;

            return cmdOut;
        }

        void GameManager::UpdateGameState()
        {
            vector::sim::GameState latestGameState = m_GameEnginePtr->GetGameState();

            for(auto clientItr : m_PlayerMap)
            {
                clientItr.second->UpdateGameState(latestGameState);
            }
        }

        void GameManager::Run()
        {
            while(!m_Ended)
            {
                m_GameEnginePtr->Tick();
                UpdateGameState();

                std::this_thread::sleep_for(GAME_THREAD_SLEEP_MILLIS);
            }
        }        
    } // namespace game
} // namespace vector