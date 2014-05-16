/** @file **/
#if !defined(UNICSTRING_C_UNICERROR_H)
#define UNICSTRING_C_UNICERROR_H

#include <stddef.h>

#include <UniCString/C/UniCTypes.h>

#if defined(__cplusplus)
extern "C"
{
#endif /* defined(__cplusplus) */

/**
// Checks whether the return code is an error.
// @param ucError The handle to the error.
// @returns UniCTrue if the return code is an error.
**/
UC_API_SYMBOL_EXPORT
UniCBoolT UniCIsError(UniCErrorT ucError);

/**
// Gets the message describing the error.
// @param ucError The handle to the error.
// @returns The message describing the error.
**/
UC_API_SYMBOL_EXPORT
const char* UniCErrorGetMessage(UniCErrorT ucError);

/**
// Gets the file name where the error happened.
// @param ucError The handle to the error.
// @return The file name where the error happened.
**/
UC_API_SYMBOL_EXPORT
const char* UniCErrorGetFileName(UniCErrorT ucError);

/**
// Gets the name of the function which caused the error.
// @param ucError The handle to the error.
// @returns The name of the function which caused the error.
**/
UC_API_SYMBOL_EXPORT
const char* UniCErrorGetFunctionName(UniCErrorT ucError);

/**
// Gets the line number in the file where the error happened.
// @param ucError The handle to the error.
// @returns The line number in the file where the error happened.
**/
UC_API_SYMBOL_EXPORT
size_t UniCErrorGetLineNumber(UniCErrorT ucError);

/**
// Gets the full message describing the error.
// @param ucError The handle to the error.
// @returns The full message describing the error.
**/
UC_API_SYMBOL_EXPORT
const char* UniCErrorGetFullMessage(UniCErrorT ucError);

/**
// Destroys the error instance.
// @param ucError The handle to the error.
**/
UC_API_SYMBOL_EXPORT
void UniCErrorDestroy(UniCErrorT ucError);

#if defined(__cplusplus)
}
#endif /* defined(__cplusplus) */

#endif /* !defined(UNICSTRING_C_UNICERROR_H) */
