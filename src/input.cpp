#include "interception/input.h"
#include "interception/exceptions.h"
#include "interception_c_api/interception.h"
#include "interception/beziercurve.h"

#include "keyboard.h"
#include "mouse.h"

#include <random>
#include <windows.h>

#define CHECK_MODS(obj, action) \
    if (obj.shift) { action("shift"); } \
    if (obj.alt) { action("alt"); } \
    if (obj.ctrl) { action("ctrl"); }

namespace interception
{
    namespace
    {
        // Devices to use for input events, initially invalid. Set by capturing devices.
        InterceptionDevice input_keyboard = -1;
        InterceptionDevice input_mouse = -1;

        /**
         * @brief Getter for our global input context, initialization happens on the first
         * attempt to send inputs through the context.
         *
         * @return The initialized interception context if the initilization succeeded.
         *
         * @throws interception_not_installed If the context could not be created.
         */
        [[nodiscard]] InterceptionContext get_ctx()
        {
            static InterceptionContext g_context = interception_create_context();
            if (!g_context) { throw interception_not_installed(); }
            return g_context;
        }

        /**
         * @brief Thin wrapper to send a stroke to our context on a given device.
         *
         * The stroke could be a key stroke or a mouse stroke, doesnt matter to us.
         */
        void send_stroke(const int32_t device, const InterceptionStroke* stroke)
        {
            if (device < 0) { throw invalid_device(); }
            interception_send(get_ctx(), device, stroke, 1);
        }

        void set_mouse_acceleration_enabled(const bool enabled)
        {
            int mouse_params[3];
            SystemParametersInfo(SPI_GETMOUSE, 0, mouse_params, 0);
            mouse_params[2] = enabled;
            SystemParametersInfo(SPI_SETMOUSE, 0, mouse_params, SPIF_SENDCHANGE);
        }
    }


    bool capture_input_devices(const std::wstring& keyword)
    {
        wchar_t buffer[500];
        bool mouse_found = false;
        bool kb_found = false;

        const auto ctx = get_ctx();

        InterceptionDevice curr_device = 1;
        while (curr_device < 21) {
            const uint32_t size = interception_get_hardware_id(
                ctx, curr_device, buffer, sizeof buffer);
            if (size == 0) {
                curr_device++;
                continue;
            }

            std::wstring name(buffer, size);

            if (curr_device < 11) {
                input_keyboard = curr_device;
                kb_found = true;
                if (keyword.empty() || name.find(keyword) != std::string::npos) {
                    curr_device = 11;
                } else { curr_device++; }
                continue;
            }

            input_mouse = curr_device;
            mouse_found = true;
            if (keyword.empty() || name.find(keyword) != std::string::npos) { break; }
            curr_device++;
        }
        return kb_found && mouse_found;
    }

    void hold(const inputable_t& input, const std::optional<ms>& duration)
    {
        if (const std::optional<MouseButton> btn = get_button_from_variant(input)) {
            InterceptionMouseStroke stroke = make_stroke(*btn, true);
            send_stroke(input_mouse, reinterpret_cast<InterceptionStroke*>(&stroke));
        } else {
            const key_data data = get_key_information(get_key_from_variant(input));
            InterceptionKeyStroke stroke = make_stroke(data, INTERCEPTION_KEY_DOWN);
            CHECK_MODS(data, hold);
            send_stroke(input_keyboard, reinterpret_cast<InterceptionStroke*>(&stroke));
        }
        if (duration) {
            std::this_thread::sleep_for(*duration);
            release(input);
        }
    }

    void release(const inputable_t& input)
    {
        if (const std::optional<MouseButton> btn = get_button_from_variant(input)) {
            InterceptionMouseStroke stroke = make_stroke(*btn, false);
            send_stroke(input_mouse, reinterpret_cast<InterceptionStroke*>(&stroke));
            return;
        }

        const key_data data = get_key_information(get_key_from_variant(input));
        InterceptionKeyStroke stroke(data.scan_code, INTERCEPTION_KEY_UP, 0);
        if (data.extended) { stroke.information |= INTERCEPTION_KEY_E0; }
        send_stroke(input_keyboard, reinterpret_cast<InterceptionStroke*>(&stroke));
        CHECK_MODS(data, release);
    }

    void scroll(const ScrollDirection direction, const int32_t times, const ms interval)
    {
        // 0x78 is equivalent to one scroll, upwards = positive, downwards = negative.
        const signed short scroll = direction == SCROLL_UP ? 0x78 : -0x78;
        InterceptionMouseStroke stroke(INTERCEPTION_MOUSE_WHEEL, 0, scroll, 0, 0, 0);

        for (int32_t i = 0; i < times; i++) {
            send_stroke(input_mouse, reinterpret_cast<InterceptionStroke*>(&stroke));
            std::this_thread::sleep_for(interval);
        }
    }

    void move_mouse_to(const point& to)
    {
        static std::random_device rd;
        static std::mt19937 gen(rd());
        static std::uniform_int_distribution delay(150, 225);

        POINT m_pos;
        GetCursorPos(&m_pos);
        point curr(static_cast<int32_t>(m_pos.x), static_cast<int32_t>(m_pos.y));
        const bezier_curve_t curve = generate_curve(curr, to);

        if (auto_disable_mouse_accel) { set_mouse_acceleration_enabled(false); }
        for (const auto& point: curve) {
            const auto& rel = point - curr;
            curr = {curr.x + rel.x, curr.y + rel.y};

            InterceptionMouseStroke stroke(0, INTERCEPTION_MOUSE_MOVE_RELATIVE, 0, rel.x,
                                           rel.y, 0);
            send_stroke(input_mouse, reinterpret_cast<InterceptionStroke*>(&stroke));
            std::this_thread::sleep_for(std::chrono::nanoseconds(delay(gen)));
        }
        // have to delay the acceleration disable, otherwise we get weird mouse behavior
        // pretty sure the OS hangs behind on processing the inputs.
        std::this_thread::sleep_for(1ms);
        if (auto_disable_mouse_accel) { set_mouse_acceleration_enabled(false); }
    }

    void write(const std::string& text)
    {
        for (const auto& char_: text) { press(char_); }
    }

    void press(const inputable_t& input, const int32_t times, const ms duration,
               const ms interval)
    {
        for (int32_t i = 0; i < times; i++) {
            hold(input);
            std::this_thread::sleep_for(duration);
            release(input);

            if (i > 0 && i < times - 1) { std::this_thread::sleep_for(interval); }
        }
    }
}
