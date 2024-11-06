#include <sstream>
#include "exceptions.h"

namespace interception
{
    interception_error::interception_error(const std::string& t_info)
        : exception(t_info.c_str()) {}

    interception_not_installed::interception_not_installed()
        : interception_error("Device initialization failed - check your installation!") {}

    invalid_input::invalid_input(const std::string& input)
        : interception_error(create_invalid_input_message(input)) {}

    std::basic_string<char, std::char_traits<char>, std::allocator<char>>
    invalid_input::create_invalid_input_message(const std::string &input) {
        std::ostringstream oss;
        oss << "Unknown/Invalid input: " << input << "!";
        return oss.str();
    }

    invalid_device::invalid_device()
        : interception_error("Device number is not valid. Determine devices first!") {}

}
