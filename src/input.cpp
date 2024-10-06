#include "interception/input.h"

#include "interception/exceptions.h"
#include "interception_c_api/interception.h"

namespace interception
{
    namespace
    {
        InterceptionDevice input_keyboard = 1;
        InterceptionDevice input_mouse = 11;

        [[nodiscard]] InterceptionContext get_ctx()
        {
            static InterceptionContext g_context = interception_create_context();
            // if (!g_context) { throw interception_not_installed(); }
            return g_context;
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
}


int main()
{
    interception::capture_input_devices();
}
