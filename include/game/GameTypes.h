#ifndef GAME_TYPES_H
#define GAME_TYPES_H

#include <string>

namespace vector
{
    namespace game
    {
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

        struct LobbyState
        {
            uint8_t numSlots;
            uint8_t numPlayers;
            GAME_TYPE gameType;
        };
    } // namespace game
} // namespace vector

#endif // GAME_TYPES_H