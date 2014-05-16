#include "UTF16.hpp"

#include <algorithm>
#include <sstream>

#include <Core/Common.hpp>
#include <Core/Exception.hpp>
#include <Core/Utils.hpp>

using namespace std;
using namespace UniCString;
using namespace UniCString::Core;
using namespace UniCString::Core::Codecs;
using namespace UniCString::Core::Utils;

size_t UTF16::Decode(
    vector<Unicode>& outputBuffer,
    const void* inputBuffer,
    const size_t inputBufferLength,
    const UTF16Options& options
)
{
    if ((inputBuffer == NULLPTR) || (inputBufferLength < 2)) {
        return (0);
    }

    if ((inputBufferLength % 2) != 0) {
        THROW_EXCEPTION("Un-even number of input octets for decoding UTF-16.");
    }

    outputBuffer.clear();
    outputBuffer.resize(0);

    size_t result = 0;
    bool swapOctets = false;

    uintptr_t bufferPtr = reinterpret_cast<uintptr_t>(inputBuffer);
    size_t counter = 0;

    ptruint8_t octetPtr = reinterpret_cast<ptruint8_t>(bufferPtr);

    // check if BOM is present
    if ((octetPtr[0] == UTF16::DEFAULT_BOM[0]) && (octetPtr[1] == UTF16::DEFAULT_BOM[1])) {
        // normal octet order
        swapOctets = false;
        counter += 2;
    }
    else if ((octetPtr[0] == UTF16::DEFAULT_BOM[1]) && (octetPtr[1] == UTF16::DEFAULT_BOM[0])) {
        // reversed octet order
        swapOctets = true;
        counter += 2;
    }
    else {
        // BOM not encountered, check if caller requested to reverse octet order
        if (options.EndianMode() == SystemEndian) { swapOctets = GetSystemEndian() == LittleEndian; }
        else { swapOctets = options.EndianMode() == LittleEndian; }
    }

    do {
        octetPtr = reinterpret_cast<ptruint8_t>(bufferPtr + counter);
        size_t index0 = swapOctets ? 1 : 0, index1 = swapOctets ? 0 : 1;
        uint16_t codeUnit = (static_cast<uint16_t>(octetPtr[index0]) << 0x08) | octetPtr[index1];

        if ((codeUnit >= 0xD800) && (codeUnit <= 0xDBFF)) {
            // part of surrogate pair, get the next codeUnit
            if ((counter + 2) > inputBufferLength) {
                THROW_EXCEPTION("Source array does not contain enough data to decode the next UTF-16 character.");
            }

            size_t index2 = swapOctets ? 3 : 2, index3 = swapOctets ? 2 : 3;
            uint16_t codeUnitB = (static_cast<uint16_t>(octetPtr[index2]) << 0x08) | octetPtr[index3];

            if ((codeUnitB >= 0xDC00) && (codeUnitB <= 0xDFFF)) {
                // get the code point from the surrogate pair
                uint32_t codePoint = (static_cast<uint32_t>(codeUnit - 0xD800) << 10) |
                    static_cast<uint32_t>(codeUnitB - 0xDC00);
                
                // add the subtracted 0x10000 from encoding
                codePoint = codePoint + 0x10000;
                Unicode unicode(codePoint);
                outputBuffer.push_back(unicode);
                result++;
                counter += 4;
            }
            else {
                ostringstream oss;
                oss << "Trail surrogate does not exist for the head surrogate: '0x" << std::uppercase << std::hex <<
                    codeUnit << "'.";
                THROW_EXCEPTION(oss.str());
            }
        }
        else if (codeUnit >= 0xDC00 && codeUnit <= 0xDFFF) {
            // invalid encoding starting with a trail surrogate
            ostringstream oss;
            oss << "Invalid code unit starting with a trail surrogate. Encountered trail surrogate: '0x" <<
                std::uppercase << std::hex << codeUnit << "'.";
            THROW_EXCEPTION(oss.str());
        }
        else {
            // as is encoding
            Unicode unicode(static_cast<uint32_t>(codeUnit));
            outputBuffer.push_back(unicode);
            result++;
            counter += 2;
        }
    }
    while (counter < inputBufferLength);

    return (result);
}

size_t UTF16::Encode(
    vector<uint8_t>& outputBuffer,
    const Unicode* inputBuffer,
    const size_t inputBufferLength,
    const UTF16Options& options
)
{
    if ((inputBuffer == NULLPTR) || (inputBufferLength == 0)) {
        return (0);
    }

    outputBuffer.clear();
    outputBuffer.resize(0);

    size_t result = 0;
    size_t counter = 0;

    // assume big endian first, later before function returns, swap octet ordering as necessary

    if (options.AddBOM()) {
        outputBuffer.insert(outputBuffer.end(), UTF16::DEFAULT_BOM, UTF16::DEFAULT_BOM + 2);
    }

    for (counter = 0; counter < inputBufferLength; counter++) {
        const Unicode& unicode = inputBuffer[counter];
        uint32_t codePoint = static_cast<uint32_t>(unicode);

        if (codePoint <= 0xFFFF) {
            if ((codePoint >= 0xD800) && (codePoint <= 0xDFFF)) {
                if (!options.IgnoreCodingErrors()) THROW_EXCEPTION("Invalid Unicode codePoint for UTF-16 encoding.");
            }

            // single code unit encoding
            uint8_t codePointOctets[2] = {
                unicode[1],
                unicode[0] // index 0 is the least significant octet
            };
            outputBuffer.insert(outputBuffer.end(), codePointOctets, codePointOctets + 2);
            result++;
        }
        else {
            if (codePoint > 0x10FFFF) {
                if (!options.IgnoreCodingErrors()) THROW_EXCEPTION("Invalid Unicode codePoint for UTF-16 encoding.");
            }

            // surrogate pair encoding
            uint32_t encodeValue = codePoint - 0x10000;

            uint16_t headSurrogate = 0xD800 | (static_cast<uint16_t>(encodeValue >> 0x0A) & 0x03FF);
            uint16_t trailSurrogate = 0xDC00 | (static_cast<uint16_t>(encodeValue >> 0x00) & 0x03FF);

            uint8_t surrogatePairOctets[4] ={
                static_cast<uint8_t>((headSurrogate >> 0x08) & 0xFF),
                static_cast<uint8_t>((headSurrogate >> 0x00) & 0xFF),
                static_cast<uint8_t>((trailSurrogate >> 0x08) & 0xFF),
                static_cast<uint8_t>((trailSurrogate >> 0x00) & 0xFF)
            };
            outputBuffer.insert(outputBuffer.end(), surrogatePairOctets, surrogatePairOctets + 4);
            result++;
        }
    }

    if ((result == 0) && options.AddBOM()) {
        // remove the BOM
        outputBuffer.clear();
    }
    else {
        bool swapOctets = false;
        if (options.EndianMode() == SystemEndian) {
            swapOctets = GetSystemEndian() == LittleEndian;
        }
        else {
            swapOctets = options.EndianMode() == LittleEndian;
        }

        // check the requested endian order
        if (swapOctets) {
            for (counter = 0; counter < outputBuffer.size(); counter += 2) {
                outputBuffer[counter + 0] ^= outputBuffer[counter + 1];
                outputBuffer[counter + 1] ^= outputBuffer[counter + 0];
                outputBuffer[counter + 0] ^= outputBuffer[counter + 1];
            }
        }
    }

    return (result);   
}

const uint8_t UTF16::DEFAULT_BOM[2] =
{
    0xFE, 0xFF
};
