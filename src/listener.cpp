#include "interception/listener.h"

#include "context.h"
#include "interception_c_api/interception.h"

namespace interception
{
    std::array<std::wstring, 20> get_connected_hwids()
    {
        std::array<std::wstring, 20> ret;
        wchar_t buff[500];
        const auto ctx = get_ctx();

        for (InterceptionDevice i = 1; i <= INTERCEPTION_MAX_DEVICE; i++) {
            const uint32_t size = interception_get_hardware_id(ctx, i, buff, sizeof buff);
            if (size == 0) { continue; }

            ret[i - 1] = {buff, size};
        }
        return ret;
    }
}
