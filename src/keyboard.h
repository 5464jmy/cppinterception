#pragma once
#include <cstdint>
#include <string>

namespace interception
{
    struct key_data
    {
        int32_t vk_code = -1;
        int32_t scan_code = -1;

        bool shift = false;
        bool ctrl = false;
        bool alt = false;
        bool extended = false;
    };

    [[nodiscard]] key_data get_key_information(const std::string& key);
}
