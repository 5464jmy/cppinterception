#pragma once
#include "interception/core.h"

namespace interception
{
    [[nodiscard]] point get_mouse_pos();

    [[nodiscard]] point get_16bit_loc(const point&);
}
