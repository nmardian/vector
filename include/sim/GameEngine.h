#ifndef GAME_ENGINE_H
#define GAME_ENGINE_H

#include "sim/MoverInterface.h"

#include <vector>
#include <unordered_map>
#include <memory>

namespace vector
{
    namespace sim
    {
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
                bool AddMover(std::unique_ptr<MoverInterface> moverPtr);

                /**
                 * @brief Run the Engine for one tick
                 * 
                 */
                void Tick();
            
            private:
                std::unordered_map<std::string, std::unique_ptr<MoverInterface>> m_AllMoversMap;
        };
    } // namespace sim
} // namespace vector


#endif // GAME_ENGINE_H