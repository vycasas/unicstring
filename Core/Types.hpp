#if !defined(UNICSTRING_CORE_TYPES_HPP)
#define UNICSTRING_CORE_TYPES_HPP

#include <Config.h>

#include <cstddef> // for size_t types

#if HAVE_STDINT_H
#include <cstdint>
#else // HAVE_STDINT_H
namespace std
{
    typedef unsigned char uint8_t;
    typedef unsigned short uint16_t;
    typedef unsigned int uint32_t;
    typedef unsigned long long uint64_t;
    typedef std::size_t uintptr_t;

    typedef signed char int8_t;
    typedef signed short int16_t;
    typedef signed int int32_t;
    typedef signed long long int64_t;
    typedef std::ssize_t intptr_t;
} // namespace std
#endif // HAVE_STDINT_H

namespace UniCString
{
    // declare pointer types
    typedef std::int8_t* ptrint8_t;
    typedef std::int16_t* ptrint16_t;
    typedef std::int32_t* ptrint32_t;
    typedef std::int64_t* ptrint64_t;
    typedef std::uint8_t* ptruint8_t;
    typedef std::uint16_t* ptruint16_t;
    typedef std::uint32_t* ptruint32_t;
    typedef std::uint64_t* ptruint64_t;

    typedef enum _Endian
    {
        BigEndian = 0x00,
        LittleEndian = 0x01,
        SystemEndian = -1
    }
    Endian, * PEndian;

} // namepsace UniCString

#endif // !defined(UNICSTRING_CORE_TYPES_HPP)
