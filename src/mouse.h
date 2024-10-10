#pragma once
#include "interception/core.h"
#include "interception_c_api/interception.h"

namespace interception
{
    [[nodiscard]] point get_mouse_pos();

    [[nodiscard]] point get_16bit_loc(const point&);

    /**
     * @return The mouse button from the inputable variant.
     */
    [[nodiscard]] std::optional<MouseButton> get_button_from_variant(const inputable_t& input);

    /**
     * @brief Makes an interception mouse stroke from a MouseButton enum.
     *
     * @param button The mouse button to send the stroke for.
     * @param down Whether the button should be down or up.
     *
     * @return The interception mouse stroke to send the event.
     */
    [[nodiscard]] InterceptionMouseStroke make_stroke(MouseButton button, bool down);
}
