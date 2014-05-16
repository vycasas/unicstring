#if !defined(UNICSTRING_CORE_UTILS_HPP)
#define UNICSTRING_CORE_UTILS_HPP

#include <Core/Types.hpp>

namespace UniCString
{
    namespace Core
    {
        namespace Utils
        {

// Checks whether a specified bit field of a value is set.
template<typename T>
inline bool IsBitSet(T value, T bitIndex)
{
    if (bitIndex > ((sizeof (T) * 8)- 1)) {
        throw (Exception("Bit index out of range.", __FILE__, __FUNCTION__, __LINE__));
    }
    return (((value >> bitIndex) & 0x01) == 0x01);
}

// Obtains the endian mode of the system.
Endian GetSystemEndian(void);

        } // namespace Utils
    } // namespace Core
} // namespace UniCString

#endif // !defined(UNICSTRING_CORE_UTILS_HPP)
