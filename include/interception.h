#pragma once
#include <cstdint>
#include <string>
#include <chrono>

using namespace std::chrono_literals;

#define INTERCEPTION_API __declspec(dllimport)

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

    template<typename T, typename... U>
    concept any_of = (std::same_as<T, U> || ...);

    template<typename T>
    concept Inputable = any_of<T, MouseButton, std::string, char, const char*>;

    /**
     * @brief Sends one or more input event of the requested key or mouse button.
     *
     * @tparam T Input types the api understands: string, char, const char*, MouseButton.
     * @tparam Duration Unit of the interval duration (milliseconds, seconds, minutes...).
     *
     * @param input The key / mouse button to send the press events of.
     * @param times How many times to press the given input, default 1.
     * @param interval The duration to sleep between the individual strokes.
     */
    template<Inputable T, typename Duration = std::chrono::milliseconds>
    INTERCEPTION_API void press(T input, int32_t times = 1, Duration interval = 50ms);


    /**
     * @brief Sends a down input event of the requested key or mouse button.
     *
     * @tparam T Input types the api understands: string, char, const char*, MouseButton.
     * @tparam Duration Unit of the interval duration (milliseconds, seconds, minutes...).
     *
     * @param input The key / mouse button to send the down event of.
     * @param hold_for If specified, how long to hold the key until it is released.
     *
     * @remark If hold_for is not set (as per default), the key must be manually released.
     */
    template<Inputable T, typename Duration = std::chrono::milliseconds>
    INTERCEPTION_API void hold(T input, std::optional<Duration> hold_for = std::nullopt);

    /**
     * @brief Sends an up input event of the requested key or mouse button.
     *
     * @tparam T Input types the api understands: string, char, const char*, MouseButton.
     *
     * @param input The key / mouse button to send the up event of.
     *
     * @remark Nothing will happen if the requested key was not previously held.
     */
    template<Inputable T>
    INTERCEPTION_API void release(T input);

    INTERCEPTION_API void move_to(const Point& point);

    INTERCEPTION_API void move_to(int32_t x, int32_t y);
}
