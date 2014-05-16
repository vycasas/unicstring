#include "UTF32.hpp"

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

size_t UTF32::Decode(
    vector<Unicode>& outputBuffer,
    const void* inputBuffer,
    const size_t inputBufferLength,
    const UTF32Options& options
)
{
    if ((inputBuffer == NULLPTR) || (inputBufferLength < 4)) {
        return (0);
    }

    if ((inputBufferLength % 4) != 0) {
        THROW_EXCEPTION("Un-even number of input octets for decoding UTF-32.");
    }

    outputBuffer.clear();
    outputBuffer.resize(0);

    size_t result = 0;
    bool swapOctets = false;

    uintptr_t bufferPtr = reinterpret_cast<uintptr_t>(inputBuffer);
    size_t counter = 0;

    ptruint8_t octetPtr = reinterpret_cast<ptruint8_t>(bufferPtr);

    // check if BOM is present
    if ((octetPtr[0] == 0x00) && (octetPtr[1] == 0x00) && (octetPtr[2] == 0xFE) && (octetPtr[3] == 0xFF)) {
        // normal octet order
        swapOctets = false;
        counter += 4;
    }
    else if ((octetPtr[0] == 0xFF) && (octetPtr[1] == 0xFE) && (octetPtr[2] == 0x00) && (octetPtr[3] == 0x00)) {
        // reversed octet order
        swapOctets = true;
        counter += 4;
    }
    else {
        // BOM not encountered, check if caller requested to reverse octet order
        if (options.EndianMode() == SystemEndian) { swapOctets = GetSystemEndian() == LittleEndian; }
        else { swapOctets = options.EndianMode() == LittleEndian; }
    }

    do {
        octetPtr = reinterpret_cast<ptruint8_t>(bufferPtr + counter);
        size_t index0 = swapOctets ? 3 : 0;
        size_t index1 = swapOctets ? 2 : 1;
        size_t index2 = swapOctets ? 1 : 2;
        size_t index3 = swapOctets ? 0 : 3;

        uint32_t codePoint =
            (static_cast<uint32_t>(octetPtr[index0]) << 0x18) |
            (static_cast<uint32_t>(octetPtr[index1]) << 0x10) |
            (static_cast<uint32_t>(octetPtr[index2]) << 0x08) |
            (static_cast<uint32_t>(octetPtr[index3]) << 0x00);

        if (codePoint > 0x10FFFF) {
            if (options.IgnoreCodingErrors()) {
                ostringstream oss;
                oss << "Invalid code point encoded with UTF-32 while decoding. Encountered: 0x" << std::uppercase <<
                    std::hex << codePoint << std::dec << ".";
                THROW_EXCEPTION(oss.str());
            }
        }

        Unicode unicode(codePoint);
        outputBuffer.push_back(unicode);
        result++;
        counter += 4;
    }
    while (counter < inputBufferLength);

    return (result);
}

size_t UTF32::Encode(
    vector<uint8_t>& outputBuffer,
    const Unicode* inputBuffer,
    const size_t inputBufferLength,
    const UTF32Options& options
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
        outputBuffer.resize(4);
        copy(UTF32::DEFAULT_BOM, UTF32::DEFAULT_BOM + 4, GET_FIRST_ELEMENT_ADDRESS(outputBuffer));
    }

    for (counter = 0; counter < inputBufferLength; counter++) {
        const Unicode& unicode = inputBuffer[counter];
        uint32_t codePoint = static_cast<uint32_t>(unicode);
        uint8_t codePointOctets[4] = {
            static_cast<uint8_t>((codePoint >> 0x18) & 0xFF),
            static_cast<uint8_t>((codePoint >> 0x10) & 0xFF),
            static_cast<uint8_t>((codePoint >> 0x08) & 0xFF),
            static_cast<uint8_t>((codePoint >> 0x00) & 0xFF)
        };

        outputBuffer.insert(outputBuffer.end(), codePointOctets, codePointOctets + 4);
        result++;
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
            for (counter = 0; counter < outputBuffer.size(); counter += 4) {
                // swap index 0 and index 3
                outputBuffer[counter + 0] ^= outputBuffer[counter + 3];
                outputBuffer[counter + 3] ^= outputBuffer[counter + 0];
                outputBuffer[counter + 0] ^= outputBuffer[counter + 3];

                // swap index 1 and index 2
                outputBuffer[counter + 1] ^= outputBuffer[counter + 2];
                outputBuffer[counter + 2] ^= outputBuffer[counter + 1];
                outputBuffer[counter + 1] ^= outputBuffer[counter + 2];
            }
        }
    }

    return (result);   
}

const uint8_t UTF32::DEFAULT_BOM[4] =
{
    0x00, 0x00, 0xFE, 0xFF
};
