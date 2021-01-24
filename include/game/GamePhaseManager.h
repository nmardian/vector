#ifndef GAME_PHASE_MANAGER_H
#define GAME_PHASE_MANAGER_H

#include "game/GamePhase.h"

#include <memory>

namespace vector
{
    namespace game
    {
        class GamePhaseManager
        {
            public:
                /**
                 * @brief Set the current phase of the game
                 * 
                 * @param phase the current phase
                 */
                void SetPhase(std::unique_ptr<vector::game::GamePhase> phase);

            private:
                std::unique_ptr<vector::game::GamePhase> m_GamePhasePtr;
        }; // class GamePhaseManager
    } // namespace game
} // namespace vector

#endif // GAME_PHASE_MANAGER_H