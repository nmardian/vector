#include "util/MathUtil.h"
#include "sim/SimConstants.h"

#include <math.h>

namespace vector
{
    namespace util
    {
        constexpr auto PI = 3.14159265358979323846;
        constexpr auto PI_RADIANS = vector::sim::HEADING_HALF_CIRCLE / PI;

        vector::sim::coord MathUtil::GetXComponentOfSpeed(const vector::sim::speed speedIn, const vector::sim::angle angleIn)
        {
            return (speedIn * sin(angleIn / (PI_RADIANS)));
        }

        vector::sim::coord MathUtil::GetYComponentOfSpeed(const vector::sim::speed speedIn, const vector::sim::angle angleIn)
        {
            return (speedIn * cos(angleIn / (PI_RADIANS)));
        }
    } // namespace util
} // namespace vector