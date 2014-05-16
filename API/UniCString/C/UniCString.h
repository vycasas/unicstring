/** @file **/
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
// Creates an empty UniCString instance.
// @param result The created UniCString instance.
// @returns The error code of this operation.
**/
UC_API_SYMBOL_EXPORT
UniCErrorT UniCStringCreate(UniCStringT* result);

/**
// Creates a new UniCString instance based from an existing one.
// @param source The existing UniCString instance.
// @param result The created UniCString instance.
// @returns The error code of this operation.
**/
UC_API_SYMBOL_EXPORT
UniCErrorT UniCStringCreateFromString(UniCStringT source, UniCStringT* result);

/**
// Creats a new UniCString instance from a single character.
// @param character The character to create a UniCString instance from.
// @param result The created UniCString instance.
// @returns The error code of this operation.
**/
UC_API_SYMBOL_EXPORT
UniCErrorT UniCStringCreateFromChar(const char character, UniCStringT* result);

/**
// Creates a new UniCString instance from a character string.
// @param charString The pointer to the beginning of the character string.
// @param charStringLenth The number of characters the string contains.
// @param encoding The encoding of the character string.
// @param result The created UniCString instance.
// @returns The error code of this operation.
**/
UC_API_SYMBOL_EXPORT
UniCErrorT UniCStringCreateFromCharString(
    const char* charString,
    const size_t charStringLength,
    UniCEncodingT encoding,
    UniCStringT* result
);

/**
// Creates a new UniCString instance from a wide character string.
// @param character The character to create a UniCString instance from.
// @param result The created UniCString instance.
// @returns The error code of this operation.
// @remarks The wchar_t type is compiler/platform defined. Encoding will depend in implementation. This function may
//      not work correctly on some platforms.
**/
UC_API_SYMBOL_EXPORT
UniCErrorT UniCStringCreateFromWChar(const wchar_t character, UniCStringT* result);

/**
// Creates a new UniCString instance from a wide character string.
// @param wcharString The pointer to the beginning of the wide character string.
// @param wcharStringLength The number of wide characters the string contains.
// @param result The created UniCString instance.
// @returns The error code of this operation.
// @remarks The wchar_t type is compiler/platform defined. Encoding will depend in implementation. This function may
//      not work correctly on some platforms.
**/
UC_API_SYMBOL_EXPORT
UniCErrorT UniCStringCreateFromWCharString(
    const wchar_t* wcharString,
    const size_t wcharStringLength,
    UniCStringT* result
);

/**
// Creates a new UniCString instance from a buffer.
// @param buffer The source buffer to create a new UniCString instance from.
// @param bufferLength The number of octets (8-bit data) the buffer contains.
// @param encoding The encoding the buffer uses.
// @param result The created UniCString instance.
// @returns The error code of this operation.
**/
UC_API_SYMBOL_EXPORT
UniCErrorT UniCStringCreateFromBuffer(
    const void* buffer,
    const size_t bufferLength,
    UniCEncodingT encoding,
    UniCStringT* result
);

/**
// Destroys a UniCString instance.
// @param ucString The UniCString instance to destroy.
**/
UC_API_SYMBOL_EXPORT
void UniCStringDestroy(UniCStringT ucString);

/**
// Gets the length (number of Unicode characters) a UniCString instance has.
// @param ucString The UniCString instance.
// @param result The number of Unicode characters.
// @returns The error code of this operation.
**/
UC_API_SYMBOL_EXPORT
UniCErrorT UniCStringGetLength(UniCStringT ucString, size_t* result);

/**
// Checks whether an existing UniCString instance is empty.
// @param ucString The UniCString instance to check.
// @param result This parameter is set to UniCTrue if ucString is empty.
// @returns The error code of this operation.
**/
UC_API_SYMBOL_EXPORT
UniCErrorT UniCStringIsEmpty(UniCStringT ucString, UniCBoolT* result);

/**
// Assigns an existing UniCString instance to another.
// @param ucString The UniCString instance.
// @param ucStringToAssign The UniCString instance to assign.
// @returns The error code of this operation.
**/
UC_API_SYMBOL_EXPORT
UniCErrorT UniCStringAssign(UniCStringT ucString, UniCStringT ucStringToAssign);

/**
// Appends an existing UniCString instance to another.
// @param ucString The UniCString instance.
// @param ucStringToCombine The UniCString instance to append to the source.
// @returns The error code of this operation.
**/
UC_API_SYMBOL_EXPORT
UniCErrorT UniCStringAppend(UniCStringT ucString, UniCStringT ucStringToAppend);

/**
// Combines two UniCString instances and creates a new instance containing the combined values.
// @param ucString The source UniCString instance.
// @param ucStringToCombine The UniCString instance to combine with.
// @param result The created UniCString instance.
// @returns The error code of this operation.
**/
UC_API_SYMBOL_EXPORT
UniCErrorT UniCStringCombine(UniCStringT ucString, UniCStringT ucStringToCombine, UniCStringT* result);

/**
// Compares two UniCString instances whether they are equal.
// @param ucString The UniCString to compare.
// @param ucStringToCompare The other UniCString to compare with.
// @param result This parameter is set to UniCTrue if both UniCString instances are equal.
// @returns The error code of this operation.
**/
UC_API_SYMBOL_EXPORT
UniCErrorT UniCStringIsEqual(UniCStringT ucString, UniCStringT ucStringToCompare, UniCBoolT* result);

/**
// Encodes a UniCString instance into the requested encoding.
// @param ucString The UniCString instance to encode.
// @param encoding The encoding scheme to use.
// @param buffer The output buffer to write encoded data to.
// @param bufferLength The size of buffer.
// @param isNullTerminated Whether to add the terminating NULL character at the end of the buffer.
// @param result The number of octets written to buffer.
// @returns The error code of this operation.
// @remarks The size of buffer required can be obtained by passing NULL as the buffer argument.
**/
UC_API_SYMBOL_EXPORT
UniCErrorT UniCStringEncode(
    UniCStringT ucString,
    UniCEncodingT encoding,
    void* buffer,
    size_t bufferLength,
    UniCBoolT isNullTerminated,
    size_t* result
);

/**
// Encodes a UniCString instance into an array of wide characters (wchar_t string).
// @param ucString The UniCString instance to encode.
// @param buffer The output buffer to write encoded data to.
// @param bufferLength The size of buffer.
// @param isNullTerminated Whether to add the terminating NULL character at the end of the buffer.
// @param result The number of wchar_t characters written to buffer.
// @returns The error code of this operation.
**/
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
