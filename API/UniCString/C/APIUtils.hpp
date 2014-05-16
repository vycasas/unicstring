#if !defined(UNICSTRING_API_C_UTILS_HPP)
#define UNICSTRING_API_C_UTILS_HPP

// This is an internal helper utilities for C API.

#include <UniCString/C/UniCTypes.h>
#include <Core/Exception.hpp>
#include <Core/String.hpp>

namespace UniCString
{
    namespace API
    {
        namespace Utils
        {

inline void CreateUniCErrorTFromException(const UniCString::Core::Exception& e, UniCErrorT* ucError)
{
    if (ucError != NULLPTR)
        *ucError = reinterpret_cast<UniCErrorT>(new UniCString::Core::Exception(e));
    return;
}

inline void CreateUniCErrorTFromString(const char* message, UniCErrorT* ucError)
{
    if (ucError != NULLPTR)
        *ucError = reinterpret_cast<UniCErrorT>(new UniCString::Core::Exception(message));
    return;
}

#define UC_BEGIN_TRY_BLOCK() \
    UniCErrorT returnError = NULLPTR; \
    try {

#define UC_END_TRY_BLOCK() \
    } \
    catch (UniCString::Core::Exception& e) { \
        UniCString::API::Utils::CreateUniCErrorTFromException(e, &returnError); \
    } \
    catch (std::exception& e) { \
        UniCString::API::Utils::CreateUniCErrorTFromString(e.what(), &returnError); \
    } \
    catch (...) { \
        UniCString::API::Utils::CreateUniCErrorTFromString("Unknown Error.", &returnError); \
    } \
    return (returnError);

// dereferencing helpers
#define GET_EXCEPTION_PTR(ucError) ((UniCString::Core::Exception*) ucError)
#define GET_EXCEPTION_REF(ucError) ((UniCString::Core::Exception&) *(GET_EXCEPTION_PTR(ucError)))

#define GET_STRING_PTR(ucString) ((UniCString::Core::String*) ucString)
#define GET_STRING_REF(ucString) ((UniCString::Core::String&) *(GET_STRING_PTR(ucString)))

#define GET_CORE_STRING_ENCODING(ucEncoding) ((UniCString::Core::String::Encoding) ucEncoding)

        } // namespace Utils
    } // namespace API
} // namespace UniCString

#endif // UNICSTRING_API_C_UTILS_HPP
