#ifndef GAME_TYPES_H
#define GAME_TYPES_H

#include <stdint.h>
#include <string>

namespace vector
{
    namespace game
    {
        typedef uint8_t team_ID;

        enum class GAME_TYPE
        {
            UNK,
            DOGFIGHT
        };

        enum class UNIT_TYPE
        {
            UNK, 
            FIGHTER
        };

        struct UnitData
        {
            std::string callsign;
            UNIT_TYPE unitType;
        };
    } // namespace game
} // namespace vector

#endif // GAME_TYPES_H