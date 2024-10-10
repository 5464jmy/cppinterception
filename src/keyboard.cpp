#include "keyboard.h"
#include "interception/exceptions.h"

#include <map>
#include <array>
#include <windows.h>

namespace interception
{
    static const std::array<std::string, 191> keys{
        "\t", " ", "!", "\"", "#", "$", "%", "&", "'", "(", ")", "*", "+", ",", "-",
        ".", "/", "0", "1", "2", "3", "4", "5", "6", "7", "8", "9", ":", ";", "<",
        "=", ">", "?", "@", "[", "\\", "]", "^", "_", "`", "a", "b", "c", "d", "e",
        "f", "g", "h", "i", "j", "k", "l", "m", "n", "o", "p", "q", "r", "s", "t",
        "u", "v", "w", "x", "y", "z", "{", "|", "}", "~", "accept", "add", "alt",
        "altleft", "altright", "apps", "backspace", "browserback", "browserfavorites",
        "browserforward", "browserhome", "browserrefresh", "browsersearch", "browserstop",
        "capslock", "clear", "convert", "ctrl", "ctrlleft", "ctrlright", "decimal",
        "del", "delete", "divide", "down", "end", "enter", "esc", "escape", "execute",
        "f1", "f10", "f11", "f12", "f13", "f14", "f15", "f16", "f17", "f18", "f19",
        "f2", "f20", "f21", "f22", "f23", "f24", "f3", "f4", "f5", "f6", "f7", "f8",
        "f9", "final", "fn", "hanguel", "hangul", "hanja", "help", "home", "insert",
        "junja", "kana", "kanji", "launchapp1", "launchapp2", "launchmail",
        "launchmediaselect", "left", "modechange", "multiply", "nexttrack",
        "nonconvert", "num0", "num1", "num2", "num3", "num4", "num5", "num6",
        "num7", "num8", "num9", "numlock", "pagedown", "pageup", "pause", "pgdn",
        "pgup", "playpause", "prevtrack", "printscreen", "prntscrn", "prtsc",
        "prtscr", "return", "right", "scrolllock", "select", "separator", "shift",
        "shiftleft", "shiftright", "sleep", "space", "stop", "subtract", "tab",
        "up", "volumedown", "volumemute", "volumeup", "win", "winleft", "winright",
        "yen", "command", "option", "optionleft", "optionright"
    };

    static const std::map<std::string, int32_t> static_vk_map = {
        {"backspace", 0x08}, {"\b", 0x08}, {"super", 0x5B}, {"tab", 0x09}, {"\t", 0x09},
        {"clear", 0x0C}, {"enter", 0x0D}, {"\n", 0x0D}, {"return", 0x0D}, {"shift", 0x10},
        {"ctrl", 0x11}, {"alt", 0x12}, {"pause", 0x13}, {"capslock", 0x14},
        {"kana", 0x15}, {"hanguel", 0x15}, {"hangul", 0x15}, {"junja", 0x17},
        {"final", 0x18}, {"hanja", 0x19}, {"kanji", 0x19}, {"esc", 0x1B},
        {"escape", 0x1B}, {"convert", 0x1C}, {"nonconvert", 0x1D}, {"accept", 0x1E},
        {"modechange", 0x1F}, {" ", 0x20}, {"space", 0x20}, {"pgup", 0x21},
        {"pageup", 0x21}, {"pgdn", 0x22}, {"pagedown", 0x22}, {"end", 0x23},
        {"home", 0x24}, {"left", 0x25}, {"up", 0x26}, {"right", 0x27}, {"down", 0x28},
        {"select", 0x29}, {"print", 0x2A}, {"execute", 0x2B}, {"prtsc", 0x2C},
        {"prtscr", 0x2C}, {"prntscrn", 0x2C}, {"printscreen", 0x2C}, {"insert", 0x2D},
        {"del", 0x2E}, {"delete", 0x2E}, {"help", 0x2F}, {"win", 0x5B}, {"winleft", 0x5B},
        {"winright", 0x5C}, {"apps", 0x5D}, {"sleep", 0x5F}, {"num0", 0x60},
        {"num1", 0x61}, {"num2", 0x62}, {"num3", 0x63}, {"num4", 0x64}, {"num5", 0x65},
        {"num6", 0x66}, {"num7", 0x67}, {"num8", 0x68}, {"num9", 0x69},
        {"multiply", 0x6A}, {"add", 0x6B}, {"separator", 0x6C}, {"subtract", 0x6D},
        {"decimal", 0x6E}, {"divide", 0x6F}, {"f1", 0x70}, {"f2", 0x71}, {"f3", 0x72},
        {"f4", 0x73}, {"f5", 0x74}, {"f6", 0x75}, {"f7", 0x76}, {"f8", 0x77},
        {"f9", 0x78}, {"f10", 0x79}, {"f11", 0x7A}, {"f12", 0x7B}, {"f13", 0x7C},
        {"f14", 0x7D}, {"f15", 0x7E}, {"f16", 0x7F}, {"f17", 0x80}, {"f18", 0x81},
        {"f19", 0x82}, {"f20", 0x83}, {"f21", 0x84}, {"f22", 0x85}, {"f23", 0x86},
        {"f24", 0x87}, {"numlock", 0x90}, {"scrolllock", 0x91}, {"shiftleft", 0xA0},
        {"shiftright", 0xA1}, {"ctrlleft", 0xA2}, {"ctrlright", 0xA3}, {"altleft", 0xA4},
        {"altright", 0xA5}, {"browserback", 0xA6}, {"browserforward", 0xA7},
        {"browserrefresh", 0xA8}, {"browserstop", 0xA9}, {"browsersearch", 0xAA},
        {"browserfavorites", 0xAB}, {"browserhome", 0xAC}, {"volumemute", 0xAD},
        {"volumedown", 0xAE}, {"volumeup", 0xAF}, {"nexttrack", 0xB0},
        {"prevtrack", 0xB1}, {"stop", 0xB2}, {"playpause", 0xB3}, {"launchmail", 0xB4},
        {"launchmediaselect", 0xB5}, {"launchapp1", 0xB6}, {"launchapp2", 0xB7}
    };

    std::map<std::string, int32_t> get_vk_map()
    {
        static std::map<std::string, int32_t> vk_map;
        if (vk_map.empty()) {
            for (const auto& key: keys) {
                if (static_vk_map.contains(key)) {
                    vk_map[key] = static_vk_map.at(key);
                } else {
                    vk_map[key] = VkKeyScanA(key.at(0));
                }
            }

            for (char i = 32; i < 127; i++) {
                vk_map[std::string(1, i)] = VkKeyScanA(i);
            }
        }
        return vk_map;
    }

    key_data get_key_information(const std::string& key)
    {
        static std::map<std::string, key_data> cache;
        if (cache.contains(key)) { return cache.at(key); }

        key_data ret;

        try {
            ret.vk_code = get_vk_map().at(key);
            const int32_t mods = ret.vk_code / 0x100;
            ret.vk_code %= 0x100;

            ret.shift |= mods & 0x1;
            ret.ctrl |= mods & 0x2;
            ret.alt |= mods & 0x4;
        } catch (const std::out_of_range&) { throw invalid_input(key); }

        const uint32_t scan_code = MapVirtualKeyA(ret.vk_code, MAPVK_VK_TO_VSC_EX);
        ret.scan_code = static_cast<int32_t>(scan_code & 0xFF);
        ret.extended = ((scan_code >> 8) & 0xFF) & 0xE0;
        return ret;
    }

    std::string get_key_from_variant(const inputable_t& input)
    {
        const std::string ret = std::visit([]<typename T0>(T0&& arg) -> std::string {
            using T = std::decay_t<T0>;
            if constexpr (std::is_same_v<T, char>) {
                return std::string(1, arg);
            } else if constexpr (std::is_same_v<T, std::reference_wrapper<const
                std::string> >) {
                return arg.get();
            } else if constexpr (std::is_same_v<T, const char*>) {
                return std::string(arg);
            }
            return "";
        }, input);

        if (ret.empty()) { throw std::bad_variant_access(); }
        return ret;
    }

    InterceptionKeyStroke make_stroke(const key_data& from_data,
                                      const unsigned short state)
    {
        return InterceptionKeyStroke(from_data.scan_code, state,
                                     from_data.extended ? INTERCEPTION_KEY_E0 : 0);
    }
}
