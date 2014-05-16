#include <iostream>
#include <vector>

#include <Core/Exception.hpp>
#include <Core/Codecs/UTF16.hpp>

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
        vector<uint8_t> utf16Buffer;
        UTF16Options options;

        // decoding test

        // single code unit UTF-16 characters

        // big endian w/o BOM
        unicodeBuffer.clear();
        utf16Buffer.clear();
        options.Reset();
        // "あ" U+3042
        utf16Buffer.push_back(0x30);
        utf16Buffer.push_back(0x42);
        options.SetEndianMode(BigEndian);

        result = UTF16::Decode(unicodeBuffer, &(utf16Buffer[0]), utf16Buffer.size(), options);
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
        utf16Buffer.clear();
        options.Reset();
        // "₤" U+20A4
        utf16Buffer.push_back(0xA4);
        utf16Buffer.push_back(0x20);
        options.SetEndianMode(LittleEndian);

        result = UTF16::Decode(unicodeBuffer, &(utf16Buffer[0]), utf16Buffer.size(), options);
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
        utf16Buffer.clear();
        // BOM U+FEFF
        utf16Buffer.push_back(0xFF);
        utf16Buffer.push_back(0xFE);
        // "₤" U+20A4
        utf16Buffer.push_back(0xA4);
        utf16Buffer.push_back(0x20);

        result = UTF16::Decode(unicodeBuffer, &(utf16Buffer[0]), utf16Buffer.size());
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

        // double code unit UTF-16 characters (surrogate pair)

        // little endian w/o BOM
        unicodeBuffer.clear();
        utf16Buffer.clear();
        options.Reset();
        // "𧋊" U+272CA
        utf16Buffer.push_back(0x5C);
        utf16Buffer.push_back(0xD8);
        utf16Buffer.push_back(0xCA);
        utf16Buffer.push_back(0xDE);
        options.SetEndianMode(LittleEndian);

        result = UTF16::Decode(unicodeBuffer, &(utf16Buffer[0]), utf16Buffer.size(), options);
        if (result != 1) {
            cout << "Test Failed (" << __FILE__ << ":" << __LINE__ << "): " <<
                "Invalid number of characters decoded, expected '1' was '" << result << "'." << endl;
            return (-8);
        }

        codePoint = static_cast<uint32_t>(unicodeBuffer[0]);
        if (codePoint != 0x272CA) {
            cout << "Test Failed (" << __FILE__ << ":" << __LINE__ << "): " <<
                "Invalid code point value retrieved, expected 'U+272CA' was 'U+" << std::uppercase << std::hex <<
                codePoint << "'." << endl;
            return (-9);
        }

        // multiple code units

        // big endian w/ BOM
        unicodeBuffer.clear();
        utf16Buffer.clear();
        options.Reset();
        utf16Buffer.push_back(0xFE);
        utf16Buffer.push_back(0xFF);
        // "Ⓐ" U+24B6
        utf16Buffer.push_back(0x24);
        utf16Buffer.push_back(0xB6);
        // "𝛯" U+1D6EF
        utf16Buffer.push_back(0xD8);
        utf16Buffer.push_back(0x35);
        utf16Buffer.push_back(0xDE);
        utf16Buffer.push_back(0xEF);
        // "₤" U+20A4
        utf16Buffer.push_back(0x20);
        utf16Buffer.push_back(0xA4);
        options.SetEndianMode(LittleEndian);

        // specify the byte order on decode to see if the BOM will take precedence
        result = UTF16::Decode(unicodeBuffer, &(utf16Buffer[0]), utf16Buffer.size(), options);
        if (result != 3) {
            cout << "Test Failed (" << __FILE__ << ":" << __LINE__ << "): " <<
                "Invalid number of characters decoded, expected '3' was '" << result << "'." << endl;
            return (-10);
        }

        codePoint = static_cast<uint32_t>(unicodeBuffer[0]);
        if (codePoint != 0x24B6) {
            cout << "Test Failed (" << __FILE__ << ":" << __LINE__ << "): " <<
                "Invalid code point value retrieved, expected 'U+24B6' was 'U+" << std::uppercase << std::hex <<
                codePoint << "'." << endl;
            return (-11);
        }

        codePoint = static_cast<uint32_t>(unicodeBuffer[1]);
        if (codePoint != 0x1D6EF) {
            cout << "Test Failed (" << __FILE__ << ":" << __LINE__ << "): " <<
                "Invalid code point value retrieved, expected 'U+1D6EF' was 'U+" << std::uppercase << std::hex <<
                codePoint << "'." << endl;
            return (-11);
        }

        codePoint = static_cast<uint32_t>(unicodeBuffer[2]);
        if (codePoint != 0x20A4) {
            cout << "Test Failed (" << __FILE__ << ":" << __LINE__ << "): " <<
                "Invalid code point value retrieved, expected 'U+20A4' was 'U+" << std::uppercase << std::hex <<
                codePoint << "'." << endl;
            return (-11);
        }

        // test for missing trail surrogate
        unicodeBuffer.clear();
        utf16Buffer.clear();
        options.Reset();
        utf16Buffer.push_back(0xD8);
        utf16Buffer.push_back(0x35);
        options.SetEndianMode(BigEndian);

        hasException = false;

        try {
            result = UTF16::Decode(unicodeBuffer, &(utf16Buffer[0]), utf16Buffer.size(), options);
        }
        catch (Exception&) {
            hasException = true;
        }

        if (!hasException) {
            cout << "Test Failed (" << __FILE__ << ":" << __LINE__ << "): " <<
                "Successfully decoded a UTF-16 surrogate pair with missing trail." << endl;
            return (-12);
        }

        // encoding test
        uint16_t codeUnit = 0x00;

        // single code unit for little endian
        unicodeBuffer.clear();
        utf16Buffer.clear();
        // "_" U+005F
        unicodeBuffer.push_back(Unicode(0x005F));

        result = UTF16::Encode(utf16Buffer, &(unicodeBuffer[0]), unicodeBuffer.size());
        if (result != 1) {
            cout << "Test Failed (" << __FILE__ << ":" << __LINE__ << "): " <<
                "Invalid number of characters encoded, expected '1' was '" << result << "'." << endl;
            return (-13);
        }

        codeUnit = static_cast<uint16_t>(utf16Buffer[0]) | (static_cast<uint16_t>(utf16Buffer[1]) << 0x08);
        if (codeUnit != 0x005F) {
            cout << "Test Failed (" << __FILE__ << ":" << __LINE__ << "): " <<
                "Unicode was incorrectly encoded. Expected UTF-16 encoding is '0x005F', but was '0x" <<
                std::uppercase << std::hex << codeUnit << "'." << endl;
            return (-14);
        }

        // surrogate pair code unit for big endian with BOM
        unicodeBuffer.clear();
        utf16Buffer.clear();
        options.Reset();
        // "周" U+2F83F UTF-16: 0xD87EDC3F
        unicodeBuffer.push_back(Unicode(0x2F83F));
        options.SetAddBOM(true);
        options.SetEndianMode(BigEndian);

        result = UTF16::Encode(utf16Buffer, &(unicodeBuffer[0]), unicodeBuffer.size(), options);
        if (result != 1) {
            cout << "Test Failed (" << __FILE__ << ":" << __LINE__ << "): " <<
                "Invalid number of characters encoded, expected '1' was '" << result << "'." << endl;
            return (-15);
        }

        result = utf16Buffer.size(); // must be 6 because of BOM (2) + surrogate pair (4)
        if (result != 6) {
            cout << "Test Failed (" << __FILE__ << ":" << __LINE__ << "): " <<
                "Invalid number of octets in encoding, expected '6' was '" << result << "'." << endl;
            return (-16);
        }

        if ((utf16Buffer[0] != 0xFE) && (utf16Buffer[1] != 0xFF)) {
            cout << "Test Failed (" << __FILE__ << ":" << __LINE__ << "): " << "Missing BOM in the encoding." << endl;
            return (-17);
        }

        codePoint =
            (utf16Buffer[2] << 0x18) |
            (utf16Buffer[3] << 0x10) |
            (utf16Buffer[4] << 0x08) |
            (utf16Buffer[5] << 0x00);

        if (codePoint != 0xD87EDC3F) {
            cout << "Test Failed (" << __FILE__ << ":" << __LINE__ << "): " <<
                "Unicode was incorrectly encoded. Expected UTF-16 encoding is '0xD87EDC3F', but was '0x" <<
                std::uppercase << std::hex << codePoint << "'." << endl;
            return (-18);
        }

        // invalid/unallowed code point for UTF-16 encoding
        unicodeBuffer.clear();
        utf16Buffer.clear();
        unicodeBuffer.push_back(Unicode(0x110000));
        hasException = false;

        try {
            result = UTF16::Encode(utf16Buffer, &(unicodeBuffer[0]), unicodeBuffer.size());
        }
        catch (Exception&) {
            hasException = true;
        }

        if (!hasException) {
            cout << "Test Failed (" << __FILE__ << ":" << __LINE__ << "): " <<
                "Successfully encoded an non-allowed UTF-16 Unicode character." << endl;
            return (-19);
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
