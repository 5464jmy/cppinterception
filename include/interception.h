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

    template<Inputable T>
    INTERCEPTION_API void press(T input, int32_t times = 1, std::chrono::milliseconds interval = 50ms);

    template<Inputable T>
    INTERCEPTION_API void hold(T input);

    template<Inputable T>
    INTERCEPTION_API void release(T input);

    INTERCEPTION_API void move_to(const Point& point);

    INTERCEPTION_API void move_to(int32_t x, int32_t y);
}
