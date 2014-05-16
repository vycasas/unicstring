#include "UniCString.h"

#include <algorithm>

#include <Core/Common.hpp>
#include <Core/Exception.hpp>
#include <Core/String.hpp>

#include "APIUtils.hpp"

#if defined(__cplusplus)
extern "C"
{
#endif /* defined(__cplusplus) */

#define NULLPTR_ARG_CHECK(arg) \
    if (arg == NULLPTR) \
        THROW_EXCEPTION("Null pointer passed as argument.");

UC_API_SYMBOL_EXPORT
UniCErrorT UniCStringCreate(UniCStringT* result)
{
    UC_BEGIN_TRY_BLOCK();
    NULLPTR_ARG_CHECK(result);
    *result = reinterpret_cast<UniCStringT>(new UniCString::Core::String());
    UC_END_TRY_BLOCK();
}

UC_API_SYMBOL_EXPORT
UniCErrorT UniCStringCreateFromString(UniCStringT source, UniCStringT* result)
{
    UC_BEGIN_TRY_BLOCK();
    NULLPTR_ARG_CHECK(source);
    NULLPTR_ARG_CHECK(result);
    *result = reinterpret_cast<UniCStringT>(new UniCString::Core::String(GET_STRING_REF(source)));
    UC_END_TRY_BLOCK();
}

UC_API_SYMBOL_EXPORT
UniCErrorT UniCStringCreateFromChar(const char character, UniCStringT* result)
{
    UC_BEGIN_TRY_BLOCK();
    NULLPTR_ARG_CHECK(result);
    *result = reinterpret_cast<UniCStringT>(new UniCString::Core::String(character));
    UC_END_TRY_BLOCK();
}

UC_API_SYMBOL_EXPORT
UniCErrorT UniCStringCreateFromCharString(
    const char* charString,
    const size_t charStringLength,
    UniCEncodingT encoding,
    UniCStringT* result
)
{
    UC_BEGIN_TRY_BLOCK();
    NULLPTR_ARG_CHECK(result);
    std::string tempString(charString, charStringLength);
    *result = reinterpret_cast<UniCStringT>(
        new UniCString::Core::String(tempString, GET_CORE_STRING_ENCODING(encoding))
    );
    UC_END_TRY_BLOCK();
}

UC_API_SYMBOL_EXPORT
UniCErrorT UniCStringCreateFromWChar(const wchar_t character, UniCStringT* result)
{
    UC_BEGIN_TRY_BLOCK();
    NULLPTR_ARG_CHECK(result);
    *result = reinterpret_cast<UniCStringT>(new UniCString::Core::String(character));
    UC_END_TRY_BLOCK();
}

UC_API_SYMBOL_EXPORT
UniCErrorT UniCStringCreateFromWCharString(
    const wchar_t* wcharString,
    const size_t wcharStringLength,
    UniCStringT* result
)
{
    UC_BEGIN_TRY_BLOCK();
    NULLPTR_ARG_CHECK(result);
    std::wstring tempString(wcharString, wcharStringLength);
    *result = reinterpret_cast<UniCStringT>(new UniCString::Core::String(tempString));
    UC_END_TRY_BLOCK();
}

UC_API_SYMBOL_EXPORT
UniCErrorT UniCStringCreateFromBuffer(
    const void* buffer,
    const size_t bufferLength,
    UniCEncodingT encoding,
    UniCStringT* result
)
{
    UC_BEGIN_TRY_BLOCK();
    NULLPTR_ARG_CHECK(result);
    *result = reinterpret_cast<UniCStringT>(
        new UniCString::Core::String(buffer, bufferLength, GET_CORE_STRING_ENCODING(encoding))
    );
    UC_END_TRY_BLOCK();
}

UC_API_SYMBOL_EXPORT
void UniCStringDestroy(UniCStringT ucString)
{
    if (ucString != NULLPTR)
        delete (GET_EXCEPTION_PTR(ucString));
    return;
}

UC_API_SYMBOL_EXPORT
UniCErrorT UniCStringGetLength(UniCStringT ucString, size_t* result)
{
    UC_BEGIN_TRY_BLOCK();
    NULLPTR_ARG_CHECK(ucString);
    NULLPTR_ARG_CHECK(result);
    *result = GET_STRING_REF(ucString).GetLength();
    UC_END_TRY_BLOCK();
}

UC_API_SYMBOL_EXPORT
UniCErrorT UniCStringIsEmpty(UniCStringT ucString, UniCBoolT* result)
{
    UC_BEGIN_TRY_BLOCK();
    NULLPTR_ARG_CHECK(ucString);
    NULLPTR_ARG_CHECK(result);
    *result = UniCBoolSet(UniCString::Core::String::IsEmpty(GET_STRING_REF(ucString)));
    UC_END_TRY_BLOCK();
}

UC_API_SYMBOL_EXPORT
UniCErrorT UniCStringAssign(UniCStringT ucString, UniCStringT ucStringToAssign)
{
    UC_BEGIN_TRY_BLOCK();
    NULLPTR_ARG_CHECK(ucString);
    NULLPTR_ARG_CHECK(ucStringToAssign);
    GET_STRING_REF(ucString) = GET_STRING_REF(ucStringToAssign);
    UC_END_TRY_BLOCK();
}

UC_API_SYMBOL_EXPORT
UniCErrorT UniCStringAppend(UniCStringT ucString, UniCStringT ucStringToAppend)
{
    UC_BEGIN_TRY_BLOCK();
    NULLPTR_ARG_CHECK(ucString);
    NULLPTR_ARG_CHECK(ucStringToAppend);
    GET_STRING_REF(ucString) += GET_STRING_REF(ucStringToAppend);
    UC_END_TRY_BLOCK();
}

UC_API_SYMBOL_EXPORT
UniCErrorT UniCStringCombine(UniCStringT ucString, UniCStringT ucStringToCombine, UniCStringT* result)
{
    UC_BEGIN_TRY_BLOCK();
    NULLPTR_ARG_CHECK(result);
    NULLPTR_ARG_CHECK(ucString);
    NULLPTR_ARG_CHECK(ucStringToCombine);
    UniCString::Core::String tempString = GET_STRING_REF(ucString) + GET_STRING_REF(ucStringToCombine);
    *result = reinterpret_cast<UniCStringT>(new UniCString::Core::String(tempString));
    UC_END_TRY_BLOCK();
}

UC_API_SYMBOL_EXPORT
UniCErrorT UniCStringIsEqual(UniCStringT ucString, UniCStringT ucStringToCompare, UniCBoolT* result)
{
    UC_BEGIN_TRY_BLOCK();
    NULLPTR_ARG_CHECK(ucString);
    NULLPTR_ARG_CHECK(ucStringToCompare);
    NULLPTR_ARG_CHECK(result);
    *result = UniCBoolSet(GET_STRING_REF(ucString) == GET_STRING_REF(ucStringToCompare));
    UC_END_TRY_BLOCK();
}

UC_API_SYMBOL_EXPORT
UniCErrorT UniCStringEncode(
    UniCStringT ucString,
    UniCEncodingT encoding,
    void* buffer,
    size_t bufferLength,
    UniCBoolT isNullTerminated,
    size_t* result
)
{
    UC_BEGIN_TRY_BLOCK();
    NULLPTR_ARG_CHECK(ucString);
    NULLPTR_ARG_CHECK(result);
    std::vector<std::uint8_t> vBuffer;
    *result = GET_STRING_REF(ucString).ConvertToEncodedString(
        GET_CORE_STRING_ENCODING(encoding),
        vBuffer,
        UniCBoolIsTrue(isNullTerminated)
    );
    if (buffer != NULLPTR) {
        std::size_t copySize = std::min(vBuffer.size(), bufferLength);
        std::memcpy(buffer, GET_FIRST_ELEMENT_ADDRESS(vBuffer), copySize);
    }
    UC_END_TRY_BLOCK();
}

UC_API_SYMBOL_EXPORT
UniCErrorT UniCStringEncodeToWCharString(
    UniCStringT ucString,
    wchar_t* buffer,
    size_t bufferLength,
    UniCBoolT isNullTerminated,
    size_t* result
)
{
    UC_BEGIN_TRY_BLOCK();
    NULLPTR_ARG_CHECK(ucString);
    NULLPTR_ARG_CHECK(result);
    std::wstring data = GET_STRING_REF(ucString).ConvertToStdWString();

    if (buffer != NULLPTR) {
        std::size_t copySize = std::min(data.size(), bufferLength);
        std::memcpy(buffer, GET_FIRST_ELEMENT_ADDRESS(data), copySize * sizeof (wchar_t));
        if (UniCBoolIsTrue(isNullTerminated)) {
            if (data.size() >= bufferLength) {
                buffer[bufferLength - 1] = L'\0';
            }
            else {
                buffer[copySize] = L'\0';
            }
        }
    }
    *result = data.size();
    UC_END_TRY_BLOCK();
}

#if defined(__cplusplus)
}
#endif /* defined(__cplusplus) */
