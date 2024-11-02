#pragma once
#include "core.h"

#include <vector>

namespace interception
{
    using bezier_curve_t = std::vector<point>;

    struct curve_params final
    {
    public:
        int32_t knots = 2;
        int32_t points = 100;

        float mean_distortion = 1.f;
        float stdev_distortion = 1.f;
        float distortion_frequency = 0.5f;

        float delay_chance = 1.f;
        std::chrono::nanoseconds delay = 230ns;
    };

    INTERCEPTION_API [[nodiscard]] bezier_curve_t generate_curve(const point& from,
        const point& to, const curve_params& = {});
}
