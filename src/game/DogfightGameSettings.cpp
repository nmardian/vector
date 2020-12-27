#include "game/DogfightGameSettings.h"

#include "game/GameConstants.h"

namespace vector
{
    namespace game
    {

        vector::game::GAME_TYPE DogfightGameSettings::GetGameType() const
        {
            return m_GameType;
        }

        uint8_t DogfightGameSettings::GetNumPlayers() const
        {
            return m_NumPlayers;
        }
        
        bool DogfightGameSettings::SetNumPlayers(const uint8_t numPlayers)
        {
            if(numPlayers >= vector::game::MIN_NUM_PLAYERS && numPlayers <= vector::game::MAX_NUM_PLAYERS)
            {
                m_NumPlayers = numPlayers;
                
                return true;
            }

            return false;
        }

        uint8_t DogfightGameSettings::GetNumMoversPerSide() const
        {
            return m_NumMoversPerSide;
        }

        bool DogfightGameSettings::SetNumMoversPerSide(uint8_t numMoversPerSide)
        {
            if(numMoversPerSide >= vector::game::MIN_MOVERS_PER_SIDE && numMoversPerSide <= vector::game::MAX_MOVERS_PER_SIDE)
            {
                m_NumMoversPerSide = numMoversPerSide;

                return true;
            }

            return false;
        }

    } // namespace game
} // namespace vector