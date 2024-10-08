#include "interception/input.h"
#include "interception/exceptions.h"
#include "interception_c_api/interception.h"

#include "keyboard.h"

#define CHECK_MODS(obj, action) \
    if (obj.shift) { action("shift"); } \
    if (obj.alt) { action("alt"); } \
    if (obj.ctrl) { action("ctrl"); }

namespace interception
{
    namespace
    {
        InterceptionDevice input_keyboard = 1;
        InterceptionDevice input_mouse = 11;

        [[nodiscard]] InterceptionContext get_ctx()
        {
            static InterceptionContext g_context = interception_create_context();
            if (!g_context) { throw interception_not_installed(); }
            return g_context;
        }

        [[nodiscard]] bool is_mouse_input(const inputable_t& input)
        {
            return std::holds_alternative<MouseButton>(input);
        }

        void send_stroke(const int32_t device, const InterceptionStroke* stroke)
        {
            interception_send(get_ctx(), device, stroke, 1);
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
        if (is_mouse_input(input)) {
            //
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
        if (is_mouse_input(input)) {
            //
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
        const signed short scroll = direction == SCROLL_UP ? 0x78 : -0x78;
        InterceptionMouseStroke stroke(INTERCEPTION_MOUSE_WHEEL, 0, scroll, 0, 0, 0);

        for (int32_t i = 0; i < times; i++) {
            send_stroke(input_mouse, reinterpret_cast<InterceptionStroke*>(&stroke));
            std::this_thread::sleep_for(interval);
        }
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

int main()
{
    interception::capture_input_devices();

    interception::scroll(interception::SCROLL_UP, 5, 500ms);
    return 0;
}
