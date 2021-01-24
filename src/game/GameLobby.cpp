#include "game/GameLobby.h"

namespace vector
{
    namespace game
    {
        GameLobby::GameLobby(std::shared_ptr<vector::game::GamePhaseManager> mgr)
            : m_GamePhaseMgrPtr(mgr)
        {
        }

        GameLobby::~GameLobby()
        {
            if(m_LobbyThreadPtr)
            {
                m_LobbyThreadPtr->join();
            }
        }

        bool GameLobby::Start()
        {
            if(!m_Started)
            {
                m_Started = true;

                m_LobbyThreadPtr = std::make_unique<std::thread>(&GameLobby::Run, this);

                return true;
            }

            return false;
        }

        bool GameLobby::Stop()
        {
            if(m_Started && !m_Ended)
            {
                std::scoped_lock<std::mutex> lock(m_LobbyMutex);    
                m_Ended = true;
                
                if(m_LobbyThreadPtr)
                {
                    m_LobbyThreadPtr->join();
                    m_LobbyThreadPtr = nullptr;
                }

                return true;
            }

            return false;
        }

        bool GameLobby::SetGameType(const vector::game::GAME_TYPE gameType)
        {
            std::scoped_lock<std::mutex> lock(m_LobbyMutex);
            if(gameType != vector::game::GAME_TYPE::UNK)
            {
                m_GameType = gameType;
                return true;
            }
            return false;
        }

        vector::game::GAME_TYPE GameLobby::GetGameType()
        {
            return m_GameType;
        }

        bool GameLobby::SetNumPlayerSlots(const uint8_t numPlayerSlots)
        {
            std::scoped_lock<std::mutex> lock(m_LobbyMutex);
            if(numPlayerSlots >= MIN_NUM_PLAYERS && numPlayerSlots <= MAX_NUM_PLAYERS)
            {
                m_NumPlayerSlots = numPlayerSlots;
                return true;
            }
            return false;
        }

        uint8_t GameLobby::GetNumPlayerSlots() const
        {
            std::scoped_lock<std::mutex> lock(m_LobbyMutex);
            return m_NumPlayerSlots;
        }
    
        bool GameLobby::AddPlayer(std::shared_ptr<vector::game::PlayerInterface> playerPtr)
        {
            std::scoped_lock<std::mutex> lock(m_LobbyMutex);
            auto playerMapItr = m_PlayerMap.find(playerPtr->GetPlayerID());
            if(playerMapItr == m_PlayerMap.end() && m_PlayerMap.size() < m_NumPlayerSlots)
            {
                m_PlayerMap.emplace(playerPtr->GetPlayerID(), playerPtr);

                // TODO add this to actual run game phase
                /*
                playerPtr->RegisterCommandFunction(
                    std::bind(std::mem_fn(&GameManager::InputCommand), this,  std::placeholders::_1, std::placeholders::_2));
                    */
                return true;
            }
            return false;
        }

        bool GameLobby::IsReadyToStartGame() const
        {
            std::scoped_lock<std::mutex> lock(m_LobbyMutex);

            if(m_NumPlayerSlots == m_PlayerMap.size() && m_GameType != vector::game::GAME_TYPE::UNK)
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

        void GameLobby::UpdateLobbyState()
        {
            LobbyState state = GetLobbyState();

            for(auto clientItr : m_PlayerMap)
            {
                clientItr.second->UpdateLobbyState(state);
            }
        }

        void GameLobby::Run()
        {
            while(!m_Ended)
            {
                UpdateLobbyState();

                std::this_thread::sleep_for(GAME_THREAD_SLEEP_MILLIS);
            }
        }

        vector::game::LobbyState GameLobby::GetLobbyState()
        {
            std::scoped_lock<std::mutex> lock(m_LobbyMutex);

            LobbyState state;
            state.gameType = m_GameType;
            state.numSlots = m_NumPlayerSlots;
            state.numPlayers = m_PlayerMap.size();

            return state;
        }
    } // namespace game
} // namespace vector