#pragma once
#include "interception_c_api/interception.h"

namespace interception
{
    // Devices to use for input events, initially invalid. Set by capturing devices.
    inline InterceptionDevice input_keyboard = -1;
    inline InterceptionDevice input_mouse = -1;

    /**
     * @brief Getter for our global input context, initialization happens on the first
     * attempt to send inputs through the context.
     *
     * @return The initialized interception context if the initilization succeeded.
     *
     * @throws interception_not_installed If the context could not be created.
     */
    [[nodiscard]] InterceptionContext get_ctx();
}
