#include "interception/exceptions.h"

namespace interception
{
    interception_error::interception_error(const std::string& t_info)
        : exception(t_info.c_str()) {}

    interception_not_installed::interception_not_installed()
        : interception_error("Device initialization failed - check your installation!") {}

    invalid_input::invalid_input(const std::string& input)
        : interception_error(std::format("Unknown/Invalid input: {}!", input)) {}

    invalid_device::invalid_device()
        : interception_error("Device number is not valid. Determine devices first!") {}
}
