#if !defined(UNICSTRING_CORE_UNICODE_HPP)
#define UNICSTRING_CORE_UNICODE_HPP

#include <Core/Types.hpp>

namespace UniCString
{
    namespace Core
    {

class Unicode
{
public:
    Unicode();

    // Creates a Unicode specified by the given unsigned value representing the Unicode's code point.
    Unicode(std::uint32_t value);

    // Accesses the specified octet with the given index.
    // Index 0 represents the least significant octet.
    std::uint8_t& operator[](const std::size_t index);

    // Accesses the specified octet with the given index.
    // Index 0 represents the least significant octet.
    const std::uint8_t& operator[](const std::size_t index) const;

    // Gets the size of this Unicode based on the number of octects used to represent the Unicode.
    std::size_t GetSize() const;

    // Operator to convert this Unicode into an unsigned integer representation (which is the code point).
    operator std::uint32_t() const;

    friend bool operator==(const Unicode& lhs, const Unicode& rhs)
    {
        return (static_cast<std::uint32_t>(lhs) == static_cast<std::uint32_t>(rhs));
    }

    friend bool operator!=(const Unicode& lhs, const Unicode& rhs) { return !(lhs == rhs); }

private:
    // 24-bits to represent all Unicode encodings.
    // TODO: Optimize so that MSB 0's are discarded to save storage.
    std::uint8_t _octet0; // Least significant bits. Represents U+0000 to U+00FF.
    std::uint8_t _octet1; // Represents U+0100 to U+FFFF (will also use less significant bits).
    std::uint8_t _octet2; // Represets U+10000 to U+FFFFFF (will also use less significant bits).

    // The maximum number of octets a single Unicode instance can contain.
    static const std::size_t OCTET_COUNT;
};

typedef Unicode* PUnicode;

    } // namespace Core
} // namespace UniCString

#endif // !defined(UNICSTRING_CORE_UNICODE_HPP)
