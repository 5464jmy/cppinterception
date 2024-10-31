#pragma once
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
    [[nodiscard]] std::array<std::wstring, 20> get_connected_device_hwids();

    class event_listener_thread
    {
    public:
        std::function<void()> on_key_event;
        std::function<void()> on_mouse_event;

    private:
        void run();
    };
}
