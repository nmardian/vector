#ifndef GAME_CONSTANTS_H
#define GAME_CONSTANTS_H

#include <stdint.h>
#include <chrono>

namespace vector
{
    namespace game
    {
        constexpr uint8_t MIN_NUM_PLAYERS = 2;
        constexpr uint8_t MAX_NUM_PLAYERS = 4;

        constexpr uint8_t MIN_MOVERS_PER_SIDE = 1;
        constexpr uint8_t MAX_MOVERS_PER_SIDE = 10;

        constexpr uint8_t DOGFIGHT_DEFAULT_NUM_PLAYERS = 2;
        constexpr uint8_t DOGFIGHT_DEFAULT_NUM_MOVERS_PER_SIDE = 5;
        
        constexpr std::chrono::milliseconds GAME_THREAD_SLEEP_MILLIS = std::chrono::milliseconds(100);
    } // namespace game
} // namespace vector

#endif // GAME_CONSTANTS_H