#include "game/GameManager.h"

namespace vector
{
    namespace game
    {
        bool GameManager::SetGameType(const vector::game::GAME_TYPE gameType)
        {
            return true;
        }
        bool GameManager::AddPlayer(const std::shared_ptr<vector::game::PlayerInterface> playerPtr)
        {
            return true;
        }

        bool GameManager::SetUnitData(const vector::game::team_ID teamID, const std::vector<vector::game::UnitData> unitData)
        {
            return true;
        }

        bool GameManager::Start()
        {
            return true;
        }
    } // namespace game
} // namespace vector