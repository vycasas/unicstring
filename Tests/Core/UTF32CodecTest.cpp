#include <iostream>
#include <vector>

#include <Core/Exception.hpp>
#include <Core/Codecs/UTF32.hpp>

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
        vector<uint8_t> utf32Buffer;
        UTF32Options options;

        // decoding test

        // big endian w/o BOM
        unicodeBuffer.clear();
        utf32Buffer.clear();
        options.Reset();
        // "あ" U+3042
        utf32Buffer.push_back(0x00);
        utf32Buffer.push_back(0x00);
        utf32Buffer.push_back(0x30);
        utf32Buffer.push_back(0x42);
        options.SetEndianMode(BigEndian);

        result = UTF32::Decode(unicodeBuffer, &(utf32Buffer[0]), utf32Buffer.size(), options);
        if (result != 1) {
            cout << "Test Failed (" << __FILE__ << ":" << __LINE__ << "): " <<
                "Invalid number of characters decoded, expected '1' was '" << result << "'." << endl;
            return (-2);
        }

        codePoint = static_cast<uint32_t>(unicodeBuffer[0]);
        if (codePoint != 0x3042) {
            cout << "Test Failed (" << __FILE__ << ":" << __LINE__ << "): " <<
                "Invalid code point value retrieved, expected 'U+3042' was 'U+" << std::uppercase << std::hex <<
                codePoint << "'." << endl;
            return (-3);
        }

        // little endian w/o BOM
        unicodeBuffer.clear();
        utf32Buffer.clear();
        options.Reset();
        // "₤" U+20A4
        utf32Buffer.push_back(0xA4);
        utf32Buffer.push_back(0x20);
        utf32Buffer.push_back(0x00);
        utf32Buffer.push_back(0x00);
        options.SetEndianMode(LittleEndian);

        result = UTF32::Decode(unicodeBuffer, &(utf32Buffer[0]), utf32Buffer.size(), options);
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

        // little endian w/ BOM
        unicodeBuffer.clear();
        utf32Buffer.clear();
        options.Reset();
        // BOM U+FEFF
        utf32Buffer.push_back(0xFF);
        utf32Buffer.push_back(0xFE);
        utf32Buffer.push_back(0x00);
        utf32Buffer.push_back(0x00);

        // "₤" U+20A4
        utf32Buffer.push_back(0xA4);
        utf32Buffer.push_back(0x20);
        utf32Buffer.push_back(0x00);
        utf32Buffer.push_back(0x00);

        result = UTF32::Decode(unicodeBuffer, &(utf32Buffer[0]), utf32Buffer.size());
        if (result != 1) {
            cout << "Test Failed (" << __FILE__ << ":" << __LINE__ << "): " <<
                "Invalid number of characters decoded, expected '1' was '" << result << "'." << endl;
            return (-6);
        }

        codePoint = static_cast<uint32_t>(unicodeBuffer[0]);
        if (codePoint != 0x20A4) {
            cout << "Test Failed (" << __FILE__ << ":" << __LINE__ << "): " <<
                "Invalid code point value retrieved, expected 'U+20A4' was 'U+" << std::uppercase << std::hex <<
                codePoint << "'." << endl;
            return (-7);
        }

        // encoding test
        uint32_t codeUnit = 0x00;

        // little endian
        unicodeBuffer.clear();
        utf32Buffer.clear();
        options.Reset();
        // "_" U+005F
        unicodeBuffer.push_back(Unicode(0x0000005F));

        result = UTF32::Encode(utf32Buffer, &(unicodeBuffer[0]), unicodeBuffer.size());
        if (result != 1) {
            cout << "Test Failed (" << __FILE__ << ":" << __LINE__ << "): " <<
                "Invalid number of characters encoded, expected '1' was '" << result << "'." << endl;
            return (-13);
        }

        codeUnit =
            (static_cast<uint32_t>(utf32Buffer[0]) << 0x00) |
            (static_cast<uint32_t>(utf32Buffer[1]) << 0x08) |
            (static_cast<uint32_t>(utf32Buffer[2]) << 0x10) |
            (static_cast<uint32_t>(utf32Buffer[3]) << 0x18);

        if (codeUnit != 0x005F) {
            cout << "Test Failed (" << __FILE__ << ":" << __LINE__ << "): " <<
                "Unicode was incorrectly encoded. Expected UTF-16 encoding is '0x005F', but was '0x" <<
                std::uppercase << std::hex << codeUnit << "'." << endl;
            return (-14);
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
