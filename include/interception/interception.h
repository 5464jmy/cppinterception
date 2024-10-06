#pragma once
#include <cstdint>
#include <string>
#include <chrono>
#include <variant>

using namespace std::chrono_literals;

#ifdef INTERCEPTION_STATIC
#define INTERCEPTION_API
#else
#define INTERCEPTION_API __declspec(dllimport)
#endif

#ifdef CV_VERSION
#include <opencv2/core/types.hpp>
#endif

namespace interception
{
    struct Point
    {
        #ifdef CV_VERSION
        Point(const cv::Point& p)
            : x(static_cast<int32_t>(p.x)), y(static_cast<int32_t>(p.y)) {}
        #endif

        int32_t x{0};
        int32_t y{0};
    };

    enum MouseButton : uint32_t
    {
        MOUSE_LEFT,
        MOUSE_RIGHT,
        MOUSE_MIDDLE,
        MOUSE_X4,
        MOUSE_X5
    };

    enum ScrollDirection : uint32_t
    {
        SCROLL_UP,
        SCROLL_DOWN
    };

    using inputable_t = std::variant<std::reference_wrapper<const std::string>,
        MouseButton, char, const char*>;

    using ms = std::chrono::milliseconds;

    /**
     * @brief Sends one or more input event of the requested key or mouse button.
     *
     * @param input The key / mouse button to send the press events of.
     * @param times How many times to press the given input, default 1.
     * @param interval The duration to sleep between the individual strokes.
     */
    INTERCEPTION_API void press(inputable_t input, int32_t times = 1, ms interval = 50ms);

    /**
     * @brief Sends a down input event of the requested key or mouse button.
     *
     * @param input The key / mouse button to send the down event of.
     * @param time If specified, how long to hold the key until it is released.
     *
     * @remark If hold_for is not set (as per default), the key must be manually released.
     */
    INTERCEPTION_API void hold(inputable_t input, std::optional<ms> time = std::nullopt);

    /**
     * @brief Sends an up input event of the requested key or mouse button.
     *
     * @param input The key / mouse button to send the up event of.
     *
     * @remark Nothing will happen if the requested key was not previously held.
     */
    INTERCEPTION_API void release(inputable_t input);

    INTERCEPTION_API void scroll(ScrollDirection direction, int32_t times);

    INTERCEPTION_API void move_mouse_to(const Point& point);

    INTERCEPTION_API void move_mouse_to(int32_t x, int32_t y);

    INTERCEPTION_API void write(const std::string& text);

    INTERCEPTION_API void capture_devices();
}
