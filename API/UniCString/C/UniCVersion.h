/** @file **/
#if !defined(UNICSTRING_C_UNICVERSION_H)
#define UNICSTRING_C_UNICVERSION_H

#if defined(__cplusplus)
extern "C"
{
#endif /* defined(__cplusplus) */

/**
// Gets the version year of this library.
// @returns The version year of this library.
**/
UC_API_SYMBOL_EXPORT
size_t UniCVersionGetYear(void);

/**
// Gets the version month of this library.
// @returns The version month of this library.
**/
UC_API_SYMBOL_EXPORT
size_t UniCVersionGetMonth(void);

/**
// Gets the version day of this library.
// @returns The version day of this library.
**/
UC_API_SYMBOL_EXPORT
size_t UniCVersionGetDay(void);

/**
// Gets the build version of this library.
// @returns The build version of this library.
**/
UC_API_SYMBOL_EXPORT
size_t UniCVersionGetBuild(void);

/**
// Gets the version string of this library.
// @returns The version string of this library.
**/
UC_API_SYMBOL_EXPORT
const char* UniCVersionGetString(void);

#if defined(__cplusplus)
}
#endif /* defined(__cplusplus) */

#endif /* !defined(UNICSTRING_C_UNICVERSION_H) */
