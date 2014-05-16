#if !defined(UNICSTRING_CORE_COMMON_HPP)
#define UNICSTRING_CORE_COMMON_HPP

#include <Config.h>

#if (__cplusplus > 199711L)

#define GET_FIRST_ELEMENT_ADDRESS(collection) collection.data()
#define NULLPTR nullptr
#define NO_EXCEPTION noexcept

#else // (__cplusplus > 199711L)

#define GET_FIRST_ELEMENT_ADDRESS(collection) &(collection[0])
#define NULLPTR NULL
#define NO_EXCEPTION

#endif // (__cplusplus > 199711L)

#endif // !defined(UNICSTRING_CORE_COMMON_HPP)
