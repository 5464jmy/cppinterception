#include "context.h"

#include "exceptions.h"

namespace interception
{
    InterceptionContext get_ctx()
    {
        static InterceptionContext g_context = interception_create_context();
        if (!g_context) { throw interception_not_installed(); }
        return g_context;
    }
}
