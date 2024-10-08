#pragma once
#include "interception/core.h"

namespace interception
{
    [[nodiscard]] Point get_mouse_pos();

    [[nodiscard]] Point get_16bit_loc(const Point&);
}
