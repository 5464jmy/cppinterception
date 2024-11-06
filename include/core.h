#pragma once
#include <chrono>
#include <variant>
#include <string>

#ifdef CV_VERSION
#include <opencv2/core/types.hpp>
#endif

#ifdef INTERCEPTION_STATIC
#define INTERCEPTION_API
#else
#define INTERCEPTION_API __declspec(dllexport)
#endif

using namespace std::chrono_literals;

namespace interception
{
    struct point
    {
        point(const int32_t x, const int32_t y) : x(x), y(y) {}

        #ifdef CV_VERSION
        explicit point(const cv::Point& p)
            : x(static_cast<int32_t>(p.x)), y(static_cast<int32_t>(p.y)) {}
        #endif

        point operator-(const point& other) const { return {x - other.x, y - other.y}; }

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

    using inputable_t = std::variant<std::reference_wrapper<const std::string>, char,
        MouseButton, const char*>;

    using ms = std::chrono::milliseconds;
}
