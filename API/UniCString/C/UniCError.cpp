#include "UniCError.h"

#include <limits>

#include <Core/Exception.hpp>

#include "APIUtils.hpp"

#if defined(__cplusplus)
extern "C"
{
#endif /* defined(__cplusplus) */

UC_API_SYMBOL_EXPORT
UniCBoolT UniCIsError(UniCErrorT ucError)
{
    return (UniCBoolSet(ucError != NULLPTR));
}

UC_API_SYMBOL_EXPORT
const char* UniCErrorGetMessage(UniCErrorT ucError)
{
    if (ucError == NULLPTR) return (NULLPTR);

    return (GET_EXCEPTION_REF(ucError).GetMessage().c_str());
}

UC_API_SYMBOL_EXPORT
const char* UniCErrorGetFileName(UniCErrorT ucError)
{
    if (ucError == NULLPTR) return (NULLPTR);

    return (GET_EXCEPTION_REF(ucError).GetFileName().c_str());
}

UC_API_SYMBOL_EXPORT
const char* UniCErrorGetFunctionName(UniCErrorT ucError)
{
    if (ucError == NULLPTR) return (NULLPTR);

    return (GET_EXCEPTION_REF(ucError).GetFunctionName().c_str());
}

UC_API_SYMBOL_EXPORT
size_t UniCErrorGetLineNumber(UniCErrorT ucError)
{
    if (ucError == NULLPTR) return (std::numeric_limits<size_t>::max());

    return (GET_EXCEPTION_REF(ucError).GetLineNumber());
}

UC_API_SYMBOL_EXPORT
const char* UniCErrorGetFullMessage(UniCErrorT ucError)
{
    if (ucError == NULLPTR) return (NULLPTR);

    return (GET_EXCEPTION_REF(ucError).GetFullMessage().c_str());
}

UC_API_SYMBOL_EXPORT
void UniCErrorDestroy(UniCErrorT ucError)
{
    if (ucError != NULLPTR)
        delete (GET_EXCEPTION_PTR(ucError));
    return;
}

#if defined(__cplusplus)
}
#endif /* defined(__cplusplus) */
