/** @file **/
#if !defined(UNICSTRING_C_UNICTYPES_H)
#define UNICSTRING_C_UNICTYPES_H

#if defined(__cplusplus)
extern "C"
{
#endif /* defined(__cplusplus) */

/**
// Return type for all C API. This indicates the error code.
**/
typedef struct _UniCErrorT* UniCErrorT;

/**
// Represents a boolean type.
**/
typedef unsigned char UniCBoolT;

/**
// Represents a UniCString instance.
**/
typedef struct _UniCStringT* UniCStringT;

/**
// Encoding definitions.
**/
typedef enum _UniCEncodingT
{
    UniCUTF8 = 0,       /**< UTF-8 Encoding. **/
    UniCUTF16 = 1,      /**< UTF-16 System Endian Encoding. **/
    UniCUTF16BE = 2,    /**< UTF-16 Big Endian Encoding. **/
    UniCUTF16LE = 3,    /**< UTF-16 Little Endian Encoding. **/
    UniCUTF32 = 4,      /**< UTF-32 System Endian Encoding. **/
    UniCUTF32BE = 5,    /**< UTF-32 Big Endian Encoding. **/
    UniCUTF32LE = 6     /**< UTF-32 Little Endian Encoding. **/
}
UniCEncodingT;

/* UCBoolT values */
#define UniCTrue 1
#define UniCFalse 0

/* UCBoolT operations */
#define UniCBoolIsTrue(bValue) (bValue == UniCTrue)
#define UniCBoolSet(bValue) (bValue ? UniCTrue : UniCFalse)

/* Symbol visibility */
#if defined(__clang__) || defined(__GNUC__)
#define UC_API_SYMBOL_EXPORT __attribute__((__visibility__("default")))
#elif defined(_WIN32)
#define UC_API_SYMBOL_EXPORT __declspec(dllexport)
#else /* defined(__clang) */
#define UC_API_SYMBOL_EXPORT
#endif /* defined(__clang__) */

#if defined(__cplusplus)
}
#endif /* defined(__cplusplus) */

#endif /* UNICSTRING_C_UNICTYPES_H */
