#pragma once
#include "core.h"

#include <functional>
#include <string>
#include <array>

namespace interception
{
    /**
     * @brief Gets the HWID of all devices connected to the computer in order.
     *
     * @remark Empty "device slots" are represented by an empty string.
     * @remark First 10 devices are keyboards, the remaining 10 are mouse devices.
     *
     * @return An array of 20 strings representing the HWIDS of connected input devices.
     */
    INTERCEPTION_API [[nodiscard]] std::array<std::wstring, 20> get_connected_hwids();

    class event_listener_thread
    {
    public:
        // 使用std::function可以兼容C++11及以上版本，无需更改。
        std::function<void()> on_key_event;
        std::function<void()> on_mouse_event;

    private:
        void run(); // 运行函数不使用C++20特性，直接保留即可。
    };
}