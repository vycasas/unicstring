#include "UniCError.h"

#include <Config.h>

#if defined(__cplusplus)
extern "C"
{
#endif /* defined(__cplusplus) */

UC_API_SYMBOL_EXPORT
size_t UniCVersionGetYear(void)
{
    return (UNICSTRING_VERSION_YEAR);
}

UC_API_SYMBOL_EXPORT
size_t UniCVersionGetMonth(void)
{
    return (UNICSTRING_VERSION_MONTH);
}

UC_API_SYMBOL_EXPORT
size_t UniCVersionGetDay(void)
{
    return (UNICSTRING_VERSION_DAY);
}

UC_API_SYMBOL_EXPORT
size_t UniCVersionGetBuild(void)
{
    return (UNICSTRING_VERSION_BUILD);
}

UC_API_SYMBOL_EXPORT
const char* UniCVersionGetString(void)
{
    return (UNICSTRING_VERSION_STRING);
}

#if defined(__cplusplus)
}
#endif /* defined(__cplusplus) */
