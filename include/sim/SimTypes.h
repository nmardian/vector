#ifndef SIM_TYPES_H
#define SIM_TYPES_H

#include <type_traits>

namespace vector
{
    namespace sim
    {
        typedef std::make_unsigned_t<short> angle;
        typedef double speed;
        typedef double coord;
    }  // namespace sim
} // namespace vector

#endif // SIM_TYPES_H