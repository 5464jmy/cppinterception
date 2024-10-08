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
    };

}
