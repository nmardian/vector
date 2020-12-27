#ifndef SIM_TYPES_H
#define SIM_TYPES_H

#include <type_traits>
#include <stdint.h>
namespace vector
{
    namespace sim
    {
        typedef std::make_unsigned_t<short> angle;
        typedef double speed;
        typedef double coord;

        typedef uint8_t team_ID;
    }  // namespace sim
} // namespace vector

#endif // SIM_TYPES_H