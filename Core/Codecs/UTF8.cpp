#include "UTF8.hpp"

#include <algorithm>
#include <limits>
#include <sstream>

#include <Core/Common.hpp>
#include <Core/Exception.hpp>
#include <Core/Utils.hpp>

using namespace std;
using namespace UniCString;
using namespace UniCString::Core;
using namespace UniCString::Core::Codecs;
using namespace UniCString::Core::Utils;

size_t UTF8::Decode(
    vector<Unicode>& outputBuffer,
    const void* inputBuffer,
    const size_t inputBufferLength,
    const UTF8Options&
)
{
    if ((inputBuffer == NULLPTR) || (inputBufferLength == 0)) {
        return (0);
    }

    size_t result = 0; // number of actual characters decoded
    size_t counter = 0; // number octets advanced from inputBuffer
    uintptr_t bufferPtr = reinterpret_cast<uintptr_t>(inputBuffer);

    outputBuffer.clear();
    outputBuffer.resize(0);

    // check if inputBuffer begins with BOM.
    if (inputBufferLength > 3) { // TODO: should this be ">= 3" ?
        ptruint8_t octetPtr = reinterpret_cast<ptruint8_t>(bufferPtr);
        if (
            octetPtr[0] == UTF8::DEFAULT_BOM[0] &&
            octetPtr[1] == UTF8::DEFAULT_BOM[1] &&
            octetPtr[2] == UTF8::DEFAULT_BOM[2]
        ) {
            // advance the counter to the first sequence
            counter += 3;
        }
    }

    do {
        uint8_t octet = *(reinterpret_cast<ptruint8_t>(bufferPtr + counter));
        uint8_t index = 0x07;

        // check the bit at index 7
        if (IsBitSet<uint8_t>(octet, index)) {
            // decode the head sequence

            // number of sequences for this Unicode code point
            size_t numSequences = 0;
            size_t totalSequences; // used for post decoding checks

            while ((index >= 0) && (IsBitSet<uint8_t>(octet, index))) {
                numSequences++;
                index--;
            }

            // the minimum must be 2 including the head sequence octet, while the maximum (as per RFC 3629) is 4
            if (numSequences < 2 || numSequences > 4) {
                ostringstream oss;
                oss << "Invalid head sequence found while decoding UTF-8. Head sequence value was: 0x" <<
                    std::uppercase << std::hex << static_cast<uint32_t>(octet) << std::dec << ".";
                THROW_EXCEPTION(oss.str());
            }

            totalSequences = numSequences;

            // we need to make sure that we have enough octets to process from inputBuffer
            if ((counter + (numSequences - 1)) > inputBufferLength) {
                THROW_EXCEPTION("Source array does not contain enough data to decode the next UTF-8 character.");
            }

            // get the Unicode code point
            uint32_t codePoint = 0x00;
            size_t shiftAmount = 0;

            // process the head sequence
            index--;    // index is now pointing to the first valid bit of the
                        // head sequence octet which maps to the actual Unicode code point

            octet = octet & static_cast<uint8_t>(0xFF >> (7 - index));
            codePoint |= static_cast<uint32_t>(octet) << (((numSequences - 1) * 8) - ((numSequences - 1) * 2));

            numSequences--; // remove the head sequence octet from being processed below
            counter++; // advance to the next sequence octet

            // process the trailing sequence(s)
            while (numSequences > 0) {
                // get the value of the next sequence octet
                octet = *(reinterpret_cast<ptruint8_t>(bufferPtr + counter));

                // verify if this octet has msb of b10
                // test if bit at index 7 is set and bit at index 6 is not set
                if (!(IsBitSet<uint8_t>(octet, 7) && !IsBitSet<uint8_t>(octet, 6))) {
                    ostringstream oss;
                    oss << "Invalid trailing sequence found while decoding UTF-8. Octet value was: 0x" <<
                        std::uppercase << std::hex << static_cast<uint32_t>(octet) << std::dec << ".";
                    THROW_EXCEPTION(oss.str());
                }

                octet = octet & static_cast<uint8_t>(0xFF >> 2); // remove leading bits
                codePoint |= static_cast<uint32_t>(octet) << (((numSequences - 1) * 8) - ((numSequences - 1) * 2));

                numSequences--;
                counter++;
            }

            // verify the decoded code point whether it was validly encoded as UTF-8

            // make sure that codePoint was encoded with the right number of exact octets with the table below:
            // 2 octets: U+0080 - U+07FF
            // 3 octets: U+0800 - U+FFFF
            // 4 octets: U+10000 - U+1FFFFF
            // it is important to error out on cases where a code point only required fewer octets, but was encoded
            // with more than it needs (e.g. U+0236 is encoded using a 4 octet sequence but it only needs 2 octets)
            bool isEncodedCorrectly = false;
            if ((codePoint >= 0x0080) && (codePoint <= 0x07FF)) {
                isEncodedCorrectly = (totalSequences == 2);
            }
            else if (codePoint >= 0x0800 && codePoint <= 0xFFFF) {
                isEncodedCorrectly = (totalSequences == 3);
            }
            else if ((codePoint >= 0x10000) && (codePoint <= 0x1FFFF)) {
                isEncodedCorrectly = (totalSequences == 4);
            }

            if (!isEncodedCorrectly) {
                ostringstream oss;
                oss << "Improper UTF-8 encoding scheme detected. Code point: U+" << std::uppercase << std::hex <<
                    codePoint << std::dec << " was encoded using " << totalSequences << " octet sequence(s).";
                THROW_EXCEPTION(oss.str());
            }

            // make sure codePoint is not within UTF-16 surrogates (as per RFC 3629)
            if (codePoint >= 0xD800 && codePoint <= 0xDFFF) {
                ostringstream oss;
                oss << "Invalid code point encoded with UTF-8 while decoding. Encountered: 0x" << std::uppercase <<
                    std::hex << codePoint << std::dec << ".";
                THROW_EXCEPTION(oss.str());
            }

            // make sure codePoint does not go beyond U+10FFFF (as per RFC 3629)
            if (codePoint > 0x10FFFF) {
                ostringstream oss;
                oss << "Invalid code point encoded with UTF-8 while decoding. Encountered: 0x" << std::uppercase <<
                    std::hex << codePoint << std::dec << ".";
                THROW_EXCEPTION(oss.str());
            }

            // finally, all checks passed, add the code point as a Unicode
            Unicode unicode(codePoint);
            outputBuffer.push_back(unicode);
            result++;
        }
        else {
            // single octet Unicode (ASCII compatible)
            octet = octet & ((uint8_t) 0x7F);
            Unicode unicode;
            unicode[0] = octet;
            outputBuffer.push_back(unicode);
            result++;
            counter++;
        }
    }
    while (counter < inputBufferLength);

    return (result);
}

size_t UTF8::Encode(
    vector<uint8_t>& outputBuffer,
    const Unicode* inputBuffer,
    const size_t inputBufferLength,
    const UTF8Options& options
)
{
    if ((inputBuffer == NULLPTR) || (inputBufferLength == 0)) {
        return (0);
    }

    outputBuffer.clear();
    outputBuffer.resize(0);

    size_t result = 0;
    size_t counter = 0;

    if (options.AddBOM()) {
        outputBuffer.insert(outputBuffer.end(), UTF8::DEFAULT_BOM, UTF8::DEFAULT_BOM + 3);
    }

    for (counter = 0; counter < inputBufferLength; counter++) {
        const Unicode& unicode = inputBuffer[counter];
        uint32_t codePoint = static_cast<uint32_t>(unicode);

        if (codePoint < 0x0080) {
            // single octet required
            outputBuffer.push_back(static_cast<uint8_t>(codePoint & 0x7F));
            result++;
        }
        else {
            size_t numSequencesRequired = 0;
            uint8_t headSequence = 0x00;

            // find out how many octet sequences are required for encoding as well as the starting bits for the head
            // sequence
            if (codePoint < 0x0800) { numSequencesRequired = 2; headSequence = 0xC0; }
            else if (codePoint < 0x10000) { numSequencesRequired = 3; headSequence = 0xE0; }
            else if (codePoint < 0x110000) { numSequencesRequired = 4; headSequence = 0xF0; }
            
            if (codePoint >= 0x110000) {
                // exceeded the allowed code point that can be encoded using UTF-8.
                if (!options.IgnoreCodingErrors()) {
                    THROW_EXCEPTION("Invalid Unicode codePoint for UTF-8 encoding.");
                }
            }
            else {
                bool isHeadSequence = true;

                do {
                    uint8_t octet = static_cast<uint8_t>((codePoint >> ((numSequencesRequired - 1) * 6)) & 0x3F);

                    if (isHeadSequence) {
                        // this is the head octet sequence
                        octet = headSequence | octet;
                        isHeadSequence = false;
                    }
                    else { octet = octet | 0x80; }

                    outputBuffer.push_back(octet);

                    numSequencesRequired--;
                }
                while (numSequencesRequired > 0);

                result++;
            }
        }
    }

    if ((result == 0) && options.AddBOM()) {
        // remove the BOM
        outputBuffer.clear();
    }

    return (result);
}

const uint8_t UTF8::DEFAULT_BOM[3] = 
{
    0xEF, 0xBB, 0xBF
};
