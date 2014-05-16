#include <iostream>
#include <vector>

#include <Core/Exception.hpp>
#include <Core/Codecs/UTF8.hpp>

int main(void)
{
    using namespace std;
    using namespace UniCString;
    using namespace UniCString::Core;
    using namespace UniCString::Core::Codecs;

    try {
        // testing variables
        size_t result = 0;
        uint32_t codePoint = 0;
        bool hasException = false;
        vector<Unicode> unicodeBuffer;
        vector<uint8_t> utf8Buffer;

        // decoding test

        // single octet UTF-8
        utf8Buffer.push_back(0x41); // 'A'
        utf8Buffer.push_back(0x62); // 'b'
        utf8Buffer.push_back(0x24); // '$'
        utf8Buffer.push_back(0x38); // '8'

        result = UTF8::Decode(unicodeBuffer, &(utf8Buffer[0]), utf8Buffer.size());
        if (result != 4) {
            cout << "Test Failed (" << __FILE__ << ":" << __LINE__ << "): " <<
                "Invalid number of characters decoded, expected '4' was '" << result << "'." << endl;
            return (-2);
        }

        codePoint = static_cast<uint32_t>(unicodeBuffer[2]);
        if (codePoint != 0x24) {
            cout << "Test Failed (" << __FILE__ << ":" << __LINE__ << "): " <<
                "Invalid code point value retrieved, expected 'U+0024' was 'U+" << std::uppercase << std::hex <<
                codePoint << "'." << endl;
            return (-3);
        }

        // multiple octet UTF-8: single character
        unicodeBuffer.clear();
        utf8Buffer.clear();

        // "₤" U+20A4
        utf8Buffer.push_back(0xE2);
        utf8Buffer.push_back(0x82);
        utf8Buffer.push_back(0xA4);

        result = UTF8::Decode(unicodeBuffer, &(utf8Buffer[0]), utf8Buffer.size());
        if (result != 1) {
            cout << "Test Failed (" << __FILE__ << ":" << __LINE__ << "): " <<
                "Invalid number of characters decoded, expected '1' was '" << result << "'." << endl;
            return (-4);
        }

        codePoint = static_cast<uint32_t>(unicodeBuffer[0]);
        if (codePoint != 0x20A4) {
            cout << "Test Failed (" << __FILE__ << ":" << __LINE__ << "): " <<
                "Invalid code point value retrieved, expected 'U+20A4' was 'U+" << std::uppercase << std::hex <<
                codePoint << "'." << endl;
            return (-5);
        }

        // multiple octet UTF-8: multiple characters
        unicodeBuffer.clear();
        utf8Buffer.clear();

        // "あ" U+3042
        utf8Buffer.push_back(0xE3);
        utf8Buffer.push_back(0x81);
        utf8Buffer.push_back(0x82);
        // Latin "a" U+0061
        utf8Buffer.push_back(0x61);
        // "⽔" U+2F54
        utf8Buffer.push_back(0xE2);
        utf8Buffer.push_back(0xBD);
        utf8Buffer.push_back(0x94);
        // Latin "ö" U+00F6
        utf8Buffer.push_back(0xC3);
        utf8Buffer.push_back(0xB6);

        result = UTF8::Decode(unicodeBuffer, &(utf8Buffer[0]), utf8Buffer.size());
        if (result != 4) {
            cout << "Test Failed (" << __FILE__ << ":" << __LINE__ << "): " <<
                "Invalid number of characters decoded, expected '4' was '" << result << "'." << endl;
            return (-6);
        }

        codePoint = static_cast<uint32_t>(unicodeBuffer[0]);
        if (codePoint != 0x3042) {
            cout << "Test Failed (" << __FILE__ << ":" << __LINE__ << "): " <<
                "Invalid code point value retrieved, expected 'U+3024' was 'U+" << std::uppercase << std::hex <<
                codePoint << "'." << endl;
            return (-7);
        }

        codePoint = static_cast<uint32_t>(unicodeBuffer[1]);
        if (codePoint != 0x61) {
            cout << "Test Failed (" << __FILE__ << ":" << __LINE__ << "): " <<
                "Invalid code point value retrieved, expected 'U+0061' was 'U+" << std::uppercase << std::hex <<
                codePoint << "'." << endl;
            return (-7);
        }

        codePoint = static_cast<uint32_t>(unicodeBuffer[2]);
        if (codePoint != 0x2F54) {
            cout << "Test Failed (" << __FILE__ << ":" << __LINE__ << "): " <<
                "Invalid code point value retrieved, expected 'U+2F54' was 'U+" << std::uppercase << std::hex <<
                codePoint << "'." << endl;
            return (-7);
        }

        codePoint = static_cast<uint32_t>(unicodeBuffer[3]);
        if (codePoint != 0xF6) {
            cout << "Test Failed (" << __FILE__ << ":" << __LINE__ << "): " <<
                "Invalid code point value retrieved, expected 'U+00F6' was 'U+" << std::uppercase << std::hex <<
                codePoint << "'." << endl;
            return (-7);
        }

        // invalid head sequence
        unicodeBuffer.clear();
        utf8Buffer.clear();
        utf8Buffer.push_back(0x8F);
        hasException = false;

        try {
            result = UTF8::Decode(unicodeBuffer, &(utf8Buffer[0]), utf8Buffer.size());
        }
        catch (Exception&) {
            hasException = true;
        }

        if (!hasException) {
            cout << "Test Failed (" << __FILE__ << ":" << __LINE__ << "): " <<
                "Successfully decoded UTF-8 with invalid head octet sequence." << endl;
            return (-8);
        }

        // insufficient sequence octets
        unicodeBuffer.clear();
        utf8Buffer.clear();
        // "周" U+2F83F
        utf8Buffer.push_back(0xF0);
        utf8Buffer.push_back(0xAF);
        utf8Buffer.push_back(0xA0);
        // utf8Buffer.push_back(0xBF); // final octet sequence missing
        hasException = false;

        try {
            result = UTF8::Decode(unicodeBuffer, &(utf8Buffer[0]), utf8Buffer.size());
        }
        catch (Exception&) {
            hasException = true;
        }

        if (!hasException) {
            cout << "Test Failed (" << __FILE__ << ":" << __LINE__ << "): " <<
                "Successfully decoded UTF-8 with missing trailing octet sequence." << endl;
            return (-9);
        }

        // invalid UTF-8 encoding
        unicodeBuffer.clear();
        utf8Buffer.clear();
        // "*" U+002A (encoded using 2 octets but only requires 1)
        utf8Buffer.push_back(0xC0);
        utf8Buffer.push_back(0xAA);
        hasException = false;

        try {
            result = UTF8::Decode(unicodeBuffer, &(utf8Buffer[0]), utf8Buffer.size());
        }
        catch (Exception&) {
            hasException = true;
        }

        if (!hasException) {
            cout << "Test Failed (" << __FILE__ << ":" << __LINE__ << "): " <<
                "Successfully decoded UTF-8 with invalid encoding scheme." << endl;
            return (-10);
        }

        // exceed possible UTF-8 encoding limit
        unicodeBuffer.clear();
        utf8Buffer.clear();
        // U+110000
        utf8Buffer.push_back(0xF4);
        utf8Buffer.push_back(0x80);
        utf8Buffer.push_back(0x84);
        utf8Buffer.push_back(0x80);
        hasException = false;

        try {
            result = UTF8::Decode(unicodeBuffer, &(utf8Buffer[0]), utf8Buffer.size());
        }
        catch (Exception&) {
            hasException = true;
        }

        if (!hasException) {
            cout << "Test Failed (" << __FILE__ << ":" << __LINE__ << "): " <<
                "Successfully decoded an invalid UTF-8 encoded character." << endl;
            return (-11);
        }
    
        // encoding test

        unicodeBuffer.clear();
        utf8Buffer.clear();

        // single character, single octet
        // "_" U+005F
        unicodeBuffer.push_back(Unicode(0x005F));

        result = UTF8::Encode(utf8Buffer, &(unicodeBuffer[0]), unicodeBuffer.size());
        if (result != 1) {
            cout << "Test Failed (" << __FILE__ << ":" << __LINE__ << "): " <<
                "Invalid number of characters encoded, expected '1' was '" << result << "'." << endl;
            return (-12);
        }

        codePoint = static_cast<uint32_t>(utf8Buffer[0]);
        if (codePoint != 0x005F) {
            cout << "Test Failed (" << __FILE__ << ":" << __LINE__ << "): " <<
                "Unicode was incorrectly encoded. Expected UTF-8 encoding is '0x005F', but was '0x" << std::uppercase <<
                std::hex << codePoint << "'." << endl;
            return (-13);
        }

        // single character, multiple octets
        unicodeBuffer.clear();
        utf8Buffer.clear();
        // "⓺" U+24FA
        unicodeBuffer.push_back(Unicode(0x24FA));

        result = UTF8::Encode(utf8Buffer, &(unicodeBuffer[0]), unicodeBuffer.size());
        if (result != 1) {
            cout << "Test Failed (" << __FILE__ << ":" << __LINE__ << "): " <<
                "Invalid number of characters encoded, expected '1' was '" << result << "'." << endl;
            return (-14);
        }

        result = utf8Buffer.size();
        if (result != 3) {
            cout << "Test Failed (" << __FILE__ << ":" << __LINE__ << "): " <<
                "Invalid number of UTF-8 octet sequence, expected '3' was '" << result << "'." << endl;
            return (-15);
        }

        codePoint = static_cast<uint32_t>(
            utf8Buffer[0] << 0x10 |
            utf8Buffer[1] << 0x08 |
            utf8Buffer[2] << 0x00
        );
        if (codePoint != 0xE293BA) {
            cout << "Test Failed (" << __FILE__ << ":" << __LINE__ << "): " <<
                "Unicode was incorrectly encoded. Expected UTF-8 encoding is '0xE293BA', but was '0x" <<
                std::uppercase << std::hex << codePoint << "'." << endl;
            return (-16);
        }

        // multiple characters
        unicodeBuffer.clear();
        utf8Buffer.clear();
        // "Ⓐ" U+24B6 UTF-8:0xE292B6
        unicodeBuffer.push_back(Unicode(0x24B6));
        // "~" U+007E UTF-8:0x7E
        unicodeBuffer.push_back(Unicode(0x007E));
        // "ɸ" U+0278 UTF-8:0xC9B8
        unicodeBuffer.push_back(Unicode(0x0278));

        result = UTF8::Encode(utf8Buffer, &(unicodeBuffer[0]), unicodeBuffer.size());
        if (result != 3) {
            cout << "Test Failed (" << __FILE__ << ":" << __LINE__ << "): " <<
                "Invalid number of characters encoded, expected '3' was '" << result << "'." << endl;
            return (-17);
        }

        result = utf8Buffer.size();
        if (result != 6) {
            cout << "Test Failed (" << __FILE__ << ":" << __LINE__ << "): " <<
                "Invalid total number of encoded UTF-8 octet sequence, expected '6' was '" << result << "'." << endl;
            return (-18);
        }

        codePoint = static_cast<uint32_t>(
            utf8Buffer[0] << 0x10 |
            utf8Buffer[1] << 0x08 |
            utf8Buffer[2] << 0x00
        );
        if (codePoint != 0xE292B6) {
            cout << "Test Failed (" << __FILE__ << ":" << __LINE__ << "): " <<
                "Unicode was incorrectly encoded. Expected UTF-8 encoding is '0xE292B6', but was '0x" <<
                std::uppercase << std::hex << codePoint << "'." << endl;
            return (-19);
        }

        codePoint = utf8Buffer[3];
        if (codePoint != 0x7E) {
            cout << "Test Failed (" << __FILE__ << ":" << __LINE__ << "): " <<
                "Unicode was incorrectly encoded. Expected UTF-8 encoding is '0x7E', but was '0x" <<
                std::uppercase << std::hex << codePoint << "'." << endl;
            return (-19);
        }

        codePoint = static_cast<uint32_t>(
            utf8Buffer[4] << 0x08 |
            utf8Buffer[5] << 0x00
        );
        if (codePoint != 0xC9B8) {
            cout << "Test Failed (" << __FILE__ << ":" << __LINE__ << "): " <<
                "Unicode was incorrectly encoded. Expected UTF-8 encoding is '0xC9B8', but was '0x" <<
                std::uppercase << std::hex << codePoint << "'." << endl;
            return (-19);
        }

        // invalid/unallowed code point for UTF-8 encoding
        unicodeBuffer.clear();
        utf8Buffer.clear();
        unicodeBuffer.push_back(Unicode(0x110000));
        hasException = false;

        try {
            result = UTF8::Encode(utf8Buffer, &(unicodeBuffer[0]), unicodeBuffer.size());
        }
        catch (Exception&) {
            hasException = true;
        }

        if (!hasException) {
            cout << "Test Failed (" << __FILE__ << ":" << __LINE__ << "): " <<
                "Successfully encoded an non-allowed UTF-8 Unicode character." << endl;
            return (-20);
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
