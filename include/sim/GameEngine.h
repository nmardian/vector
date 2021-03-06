#ifndef GAME_ENGINE_H
#define GAME_ENGINE_H

#include "sim/MoverInterface.h"
#include "sim/GameState.h"
#include "util/Command.h"

#include <vector>
#include <unordered_map>
#include <memory>
#include <mutex>

namespace vector
{
    namespace sim
    {
        /**
         * @brief Class to act as a state machine for the sim aspect of the game.
         * 
         * Responsible for maintaining "truth" as to locations, status, etc of Movers,
         * as well as simulating the Game
         * 
         */
        class GameEngine
        {
            public:
                /**
                 * @brief Constructor
                 * 
                 */
                GameEngine() = default;

                /**
                 * @brief Destructor
                 * 
                 */
                virtual ~GameEngine() = default;

                /**
                 * @brief Add a Mover to this GameEngine
                 * 
                 * @param mover Mover to be added
                 * @return true If the Mover was successfully added
                 * @return false If the Mover was unable to be added (non-unique ID, etc)
                 */
                bool AddMover(std::shared_ptr<MoverInterface> moverPtr);

                /**
                 * @brief Retrieve the specified Mover
                 * 
                 * @param moverID ID of the Mover to be retrieved
                 * @return MoverInterface Ptr to the specified Mover,
                 *          nullptr if the specified Mover does not exist
                 */
                std::shared_ptr<MoverInterface> GetMover(const std::string& moverID);

                /**
                 * @brief Handle a command to the GameEngine
                 * 
                 * @param cmd Command to be handled
                 */
                bool InputCommand(util::Command cmd);

                /**
                 * @brief Get a snapshot representation of this GameEngine's state
                 * 
                 * @return this GameEngine's state (Mover intertial data, etc)
                 */
                GameState GetGameState() const;

                /**
                 * @brief Run the Engine for one tick
                 * 
                 */
                void Tick();
            
            private:
                std::unordered_map<std::string, std::shared_ptr<MoverInterface>> m_AllMoversMap;
                mutable std::mutex m_MoversMutex;
        };
    } // namespace sim
} // namespace vector


#endif // GAME_ENGINE_H