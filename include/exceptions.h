#pragma once
#include "core.h"

namespace interception
{
    /**
     * @brief Base class for all exceptions directly thrown by interception.
     */
    struct interception_error : std::exception
    {
    public:
        explicit interception_error(const std::string& t_info);
    };

    struct interception_not_installed final : interception_error
    {
    public:
        interception_not_installed();
    };

    struct invalid_input final : interception_error
    {
    public:
        explicit invalid_input(const std::string& input);

        static std::basic_string<char, std::char_traits<char>, std::allocator<char>> create_invalid_input_message(const std::string &basicString);
    };

    struct invalid_device final : interception_error
    {
    public:
        explicit invalid_device();
    };

}
