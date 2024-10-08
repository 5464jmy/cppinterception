#pragma once
#include "core.h"

namespace interception
{
    // Quite a common thing to have to adjust based on what you're sending inputs to,
    // this provides a better way to apply it to all calls automatically.
    inline auto default_press_duration = 5ms;

    inline bool randomize_press_duration = false;

    INTERCEPTION_API bool capture_input_devices(const std::wstring& keyword = L"");

    /**
     * @brief Sends one or more input event of the requested key or mouse button.
     *
     * @param input The key / mouse button to send the press events of.
     * @param times How many times to press the given input, default 1.
     * @param duration The duration to keep the input pressed for.
     * @param interval The time to sleep between the individual presses.
     */
    INTERCEPTION_API void press(const inputable_t& input, int32_t times = 1,
                                ms duration = default_press_duration, ms interval = 50ms);

    /**
     * @brief Sends a down input event of the requested key or mouse button.
     *
     * @param input The key / mouse button to send the down event of.
     * @param duration If specified, how long to hold the key until it is released.
     *
     * @remark If hold_for is not set (as per default), the key must be manually released.
     */
    INTERCEPTION_API void hold(const inputable_t& input,
                               const std::optional<ms>& duration = std::nullopt);

    /**
     * @brief Sends an up input event of the requested key or mouse button.
     *
     * @param input The key / mouse button to send the up event of.
     *
     * @remark Nothing will happen if the requested key was not previously held.
     */
    INTERCEPTION_API void release(const inputable_t& input);

    INTERCEPTION_API void scroll(ScrollDirection direction, int32_t times);

    INTERCEPTION_API void move_mouse_to(const point& point);

    INTERCEPTION_API void move_mouse_to(int32_t x, int32_t y);

    INTERCEPTION_API void write(const std::string& text, bool randomize);
}
