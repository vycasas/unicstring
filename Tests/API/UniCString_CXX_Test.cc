#include <iostream>
#include <string>
#include <vector>

#include <UniCString/UniCString.h>

int main(void)
{
    using namespace std;
    using namespace UniCString;

    size_t result = 0;
    std::vector<unsigned char> data;

    try {
        String ustr;

        result = ustr.GetLength();
        if (result != 0) {
            cout << "Test Failed (" << __FILE__ << ":" << __LINE__ << "): " <<
                "Invalid String length, expected '0' was '" << result << "'." << endl;
            return (-2);
        }

        // UTF-8 input
        data.clear();
        // "₤"
        data.push_back(0xE2);
        data.push_back(0x82);
        data.push_back(0xA4);
        ustr = String(data, String::UTF8);

        result = ustr.GetLength();
        if (result != 1) {
            cout << "Test Failed (" << __FILE__ << ":" << __LINE__ << "): " <<
                "Invalid String length, expected '1' was '" << result << "'." << endl;
            return (-3);
        }

        // Encode to UTF-32
        data.clear();
        ustr.ConvertToEncodedString(String::UTF32BE, data);
        if (data.size() != 4) {
            cout << "Test Failed (" << __FILE__ << ":" << __LINE__ << "): " <<
                "Invalid encoded length, expected '4' was '" << result << "'." << endl;
            return (-4);
        }

        unsigned int utf32Char =
            (static_cast<unsigned int>(data[0]) << 0x18) | 
            (static_cast<unsigned int>(data[1]) << 0x10) | 
            (static_cast<unsigned int>(data[2]) << 0x08) | 
            (static_cast<unsigned int>(data[3]) << 0x00);
        if (utf32Char != 0x000020A4) {
            cout << "Test Failed (" << __FILE__ << ":" << __LINE__ << "): " <<
                "Invalid UTF-32 encoding, expected '0x20A4' was 'U+" << std::uppercase << std::hex <<
                utf32Char << "'." << endl;
            return (-5);
        }

        cout << "All tests passed." << endl;
    }
    catch (Exception& e) {
        cerr << "An Exception was caught: \"" << e << "\"." << endl;
        return (-1);
    }
    catch (exception& e) {
        cerr << "An std::exception was caught: \"" << e.what() << "\"." << endl;
        return (-1);
    }
    catch (...) {
        cerr << "An unknown error has occurred." << endl;
        return (-1);
    }

    return (0);
}
