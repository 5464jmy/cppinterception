#pragma once
#include <cstdint>
#include <string>

namespace interception
{
    /**
     * @struct key_data
     *
     * @brief Stores information about a key that is required to properly send the input.
     *
     */
    struct key_data
    {
        int32_t vk_code = -1;
        int32_t scan_code = -1;

        bool shift = false;
        bool ctrl = false;
        bool alt = false;
        bool extended = false;
    };

    /**
     * @param key The key to fetch the key data for.
     *
     * @return A key_data struct containing the relevant information about the key.
     *
     * @throws invalid_input If the provided key is not known or could not be translated.
     *
     * @remark The result per key is automatically cached, thus changing the keyboard layout
     * would required a reload.
     */
    [[nodiscard]] key_data get_key_information(const std::string& key);
}
