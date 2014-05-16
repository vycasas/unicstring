#if !defined(UNICSTRING_C_UNICSTRING_H)
#define UNICSTRING_C_UNICSTRING_H

#include <stddef.h>

#include <UniCString/C/UniCError.h>
#include <UniCString/C/UniCTypes.h>

#if defined(__cplusplus)
extern "C"
{
#endif /* defined(__cplusplus) */

/**
/// Creates an empty UniCString
**/
UC_API_SYMBOL_EXPORT
UniCErrorT UniCStringCreate(UniCStringT* result);

UC_API_SYMBOL_EXPORT
UniCErrorT UniCStringCreateFromString(UniCStringT source, UniCStringT* result);

UC_API_SYMBOL_EXPORT
UniCErrorT UniCStringCreateFromChar(const char character, UniCStringT* result);

UC_API_SYMBOL_EXPORT
UniCErrorT UniCStringCreateFromCharString(
    const char* charString,
    const size_t charStringLength,
    UniCEncodingT encoding,
    UniCStringT* result
);

UC_API_SYMBOL_EXPORT
UniCErrorT UniCStringCreateFromWChar(const wchar_t character, UniCStringT* result);

UC_API_SYMBOL_EXPORT
UniCErrorT UniCStringCreateFromWCharString(
    const wchar_t* wcharString,
    const size_t wcharStringLength,
    UniCStringT* result
);

UC_API_SYMBOL_EXPORT
UniCErrorT UniCStringCreateFromBuffer(
    const void* buffer,
    const size_t bufferLength,
    UniCEncodingT encoding,
    UniCStringT* result
);

UC_API_SYMBOL_EXPORT
void UniCStringDestroy(UniCStringT ucString);

UC_API_SYMBOL_EXPORT
UniCErrorT UniCStringGetLength(UniCStringT ucString, size_t* result);

UC_API_SYMBOL_EXPORT
UniCErrorT UniCStringIsEmpty(UniCStringT ucString, UniCBoolT* result);

UC_API_SYMBOL_EXPORT
UniCErrorT UniCStringAssign(UniCStringT ucString, UniCStringT ucStringToAssign);

UC_API_SYMBOL_EXPORT
UniCErrorT UniCStringAppend(UniCStringT ucString, UniCStringT ucStringToAppend);

UC_API_SYMBOL_EXPORT
UniCErrorT UniCStringCombine(UniCStringT ucString, UniCStringT ucStringToCombine, UniCStringT* result);

UC_API_SYMBOL_EXPORT
UniCErrorT UniCStringIsEqual(UniCStringT ucString, UniCStringT ucStringToCompare, UniCBoolT* result);

UC_API_SYMBOL_EXPORT
UniCErrorT UniCStringEncode(
    UniCStringT ucString,
    UniCEncodingT encoding,
    void* buffer,
    size_t bufferLength,
    UniCBoolT isNullTerminated,
    size_t* result
);

UC_API_SYMBOL_EXPORT
UniCErrorT UniCStringEncodeToWCharString(
    UniCStringT ucString,
    wchar_t* buffer,
    size_t bufferLength,
    UniCBoolT isNullTerminated,
    size_t* result
);

#if defined(__cplusplus)
}
#endif /* defined(__cplusplus) */

#endif /* !defined(UNICSTRING_C_UNICSTRING_H) */
