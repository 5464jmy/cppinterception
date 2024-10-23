#pragma once
#include <vector>
#include "core.h"

namespace interception
{
    using bezier_curve_t = std::vector<point>;

    struct bezier_curve_parameters final
    {
    public:
        int32_t knots = 2;
        int32_t points = 100;

        float mean_distortion = 1.f;
        float stdev_distortion = 1.f;
        float distortion_frequency = 0.5f;
    };

    [[nodiscard]] bezier_curve_t generate_curve(const point& from, const point& to,
                                                const bezier_curve_parameters& = {});
}
