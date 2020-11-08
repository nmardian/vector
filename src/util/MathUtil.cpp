#include "util/MathUtil.h"

#include <math.h>

namespace vector
{
    namespace util
    {
        vector::sim::coord MathUtil::GetXComponentOfSpeed(const vector::sim::speed speedIn, const vector::sim::angle angleIn)
        {
            return (speedIn * cos(angleIn));
        }

        vector::sim::coord MathUtil::GetYComponentOfSpeed(const vector::sim::speed speedIn, const vector::sim::angle angleIn)
        {
            return (speedIn * sin(angleIn));
        }
    } // namespace util
} // namespace vector