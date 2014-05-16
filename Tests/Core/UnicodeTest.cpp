#include <iostream>

#include <Core/Unicode.hpp>

int main(void)
{
    using namespace std;
    using namespace UniCString;
    using namespace UniCString::Core;

    // create unicode
    Unicode unicode;
    size_t result = 0;

    result = unicode.GetSize();
    if (result != 1) {
        cout << "Test Failed (" << __FILE__ << ":" << __LINE__ << "): " <<
            "Invalid Unicode size, expected '1' was '" << result << "'." <<
            endl;
        return (-1);
    }

    unicode[1] = 0x80;
    result = unicode.GetSize();
    if (result != 2) {
        cout << "Test Failed (" << __FILE__ << ":" << __LINE__ << "): " <<
            "Invalid Unicode size, expected '2' was '" << result << "'." <<
            endl;
        return (-2);

    }

    unicode[2] = 0x40;
    unicode[1] = 0x00;
    unicode[0] = 0xC0;
    result = ((unicode[2] << 16) | (unicode[1] << 8) | unicode[0]);
    if (result != 0x004000C0) {
        cout << "Test Failed (" << __FILE__ << ":" << __LINE__ << "): " <<
            "Invalid Unicode value, expected '0x4000C0' was '0x" << std::hex << result << "'." <<
            endl;
        return (-3);
    }

    uint32_t uintValue = static_cast<uint32_t>(unicode);
    if (result != uintValue) {
        cout << "Test Failed (" << __FILE__ << ":" << __LINE__ << "): " <<
            "Invalid uint value, expected '0x" << std::hex << result << "' was '0x" << std::hex << uintValue << "'." <<
            endl;
        return (-4);
    }

    Unicode unicodeB(0x0099FF88);
    uint8_t octet1 = unicodeB[1];
    if (octet1 != 0xFF) {
        cout << "Test Failed (" << __FILE__ << ":" << __LINE__ << "): " <<
            "Invalid octet 1 value, expected '0xFF' was '0x" << std::hex << unicodeB[0] << "'." <<
            endl;
        return (-5);
    }

    result = 0;
    try {
        unicodeB[10];
    }
    catch (std::exception&) {
        result = 1;
    }

    if (result != 1) {
        cout << "Test Failed (" << __FILE__ << ":" << __LINE__ << "): " <<
            "Exception was expected but not caught." <<
            endl;
        return (-6);
    }

    cout << "All tests passed." << endl;
    return (0);
}
