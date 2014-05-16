#include "Unicode.hpp"

#include <Core/Exception.hpp>

using namespace std;
using namespace UniCString;
using namespace UniCString::Core;

const size_t Unicode::OCTET_COUNT = 0x03;

Unicode::Unicode() :
    _octet0(0x00),
    _octet1(0x00),
    _octet2(0x00)
{
    return;
}

Unicode::Unicode(uint32_t value)
{
    this->_octet0 = static_cast<uint8_t>((value & 0x000000FF) >> 0x00);
    this->_octet1 = static_cast<uint8_t>((value & 0x0000FF00) >> 0x08);
    this->_octet2 = static_cast<uint8_t>((value & 0x00FF0000) >> 0x10);
    return;
}

uint8_t& Unicode::operator[](const size_t index)
{
    switch (index) {
        case 0: { return (this->_octet0); }
        case 1: { return (this->_octet1); }
        case 2: { return (this->_octet2); }
        default: {
            THROW_EXCEPTION("Index out of range when accessing an octet.");
            break;
        }
    }
}

const uint8_t& Unicode::operator[](const size_t index) const
{
    // ran into an infinite loop bug (due to ambiguity) w/ this code
    // return (static_cast<const uint8_t&>((*this)[index]));

    switch (index) {
        case 0: { return (static_cast<const uint8_t&>(this->_octet0)); }
        case 1: { return (static_cast<const uint8_t&>(this->_octet1)); }
        case 2: { return (static_cast<const uint8_t&>(this->_octet2)); }
        default: {
            THROW_EXCEPTION("Index out of range when accessing an octet.");
            break;
        }
    }
}

size_t Unicode::GetSize() const
{
    size_t result = 1;
    if (this->_octet2 > 0x00) { result = 3; }
    else if (this->_octet1 > 0x00) { result = 2; }
    return (result);
}

Unicode::operator uint32_t() const
{
    uint32_t result = 0x00;
    result =
        this->_octet0 << 0x00 |
        this->_octet1 << 0x08 |
        this->_octet2 << 0x10;
    return (result);
}
