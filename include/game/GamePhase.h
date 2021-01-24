#ifndef GAME_PHASE_H
#define GAME_PHASE_H

namespace vector
{
    namespace game
    {
        class GamePhase
        {
            public:

                /**
                 * @brief Start this Phase
                 * 
                 * @return true if the Phase was successfully started
                 * @return false if the Phase was not able to be Started
                 */
                virtual bool Start() = 0;

                /**
                 * @brief Stop this phase
                 * 
                 * @return true if the Phase was successfully stopped
                 * @return false if the Phase was not able to be stopped
                 */
                virtual bool Stop() = 0;
        }; // GamePhase
    } // namespace game
} // namespace vector

#endif // GAME_PHASE_H