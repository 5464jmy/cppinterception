#include "mouse.h"

#define UP_OR_DOWN(common, down) \
    down ? common##_DOWN : common##_UP

namespace interception
{
    std::optional<MouseButton> get_button_from_variant(const inputable_t& input)
    {
        if (const auto ret = std::get_if<MouseButton>(&input)) {
            return *ret;
        }
        return std::nullopt;
    }

    InterceptionMouseStroke make_stroke(const MouseButton button, const bool down)
    {
        unsigned short state = 0;
        switch (button) {
            case MOUSE_LEFT:
                state = UP_OR_DOWN(INTERCEPTION_MOUSE_LEFT_BUTTON, down);
                break;
            case MOUSE_RIGHT:
                state = UP_OR_DOWN(INTERCEPTION_MOUSE_RIGHT_BUTTON, down);
                break;
            case MOUSE_MIDDLE:
                state = UP_OR_DOWN(INTERCEPTION_MOUSE_MIDDLE_BUTTON, down);
                break;
            case MOUSE_X4:
                state = UP_OR_DOWN(INTERCEPTION_MOUSE_BUTTON_4, down);
                break;
            case MOUSE_X5:
                state = UP_OR_DOWN(INTERCEPTION_MOUSE_BUTTON_5, down);
                break;
        }
        return InterceptionMouseStroke(state, 0, 0, 0, 0, 0);
    }
}
