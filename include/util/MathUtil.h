#ifndef MATH_UTIL_H
#define MATH_UTIL_H

#include "sim/SimTypes.h"

namespace vector
{
    namespace util
    {
        class MathUtil
        {
            public:
                /**
                 * @brief Destructor
                 */
                virtual ~MathUtil() = default;

                /**
                 * @brief Get the x component of speed
                 * 
                 * @param input 
                 * @return vector::sim::coord 
                 */
                static vector::sim::coord GetXComponentOfSpeed(const vector::sim::speed speedIn, const vector::sim::angle angleIn);

                static vector::sim::coord GetYComponentOfSpeed(const vector::sim::speed speedIn, const vector::sim::angle angleIn);

                MathUtil() = delete;
                MathUtil(const MathUtil&) = delete;
                MathUtil& operator=(const MathUtil&) = delete;
                MathUtil(MathUtil&&) = delete;
                MathUtil& operator=(MathUtil&&) = delete;
        };
    } // namespace util
} // namespace vector

#endif //MATH_UTIL_H