#include "String.hpp"

#include <cstring>

#include <Core/Exception.hpp>
#include <Core/Codecs/UTF8.hpp>
#include <Core/Codecs/UTF16.hpp>
#include <Core/Codecs/UTF32.hpp>

using namespace std;
using namespace UniCString;
using namespace UniCString::Core;
using namespace UniCString::Core::Codecs;

String::String(void)
{
    return;
}

String::String(const String& source)
{
    size_t sourceSize = source._codes.size();

    if (sourceSize > 0) {
        this->_codes.resize(sourceSize);
        memcpy(GET_FIRST_ELEMENT_ADDRESS(this->_codes), GET_FIRST_ELEMENT_ADDRESS(source._codes), sourceSize);
    }

    return;
}

#if defined(CXX11_OR_LATER_SUPPORT)

String::String(const std::u16string& source)
{
    this->Initialize(
        reinterpret_cast<const uint8_t*>(GET_FIRST_ELEMENT_ADDRESS(source)),
        source.size() * sizeof (char16_t),
        UTF16
    );
    return;
}

String::String(const std::u32string& source)
{
    this->Initialize(
        reinterpret_cast<const uint8_t*>(GET_FIRST_ELEMENT_ADDRESS(source)),
        source.size() * sizeof (char32_t),
        UTF32
    );
    return;
}

#endif // defined(CXX11_OR_LATER_SUPPORT)

String::~String(void)
{
    return;
}

size_t String::GetLength(void) const
{
    return (this->_codes.size());
}

size_t String::ConvertToEncodedString(
    Encoding encoding,
    vector<uint8_t>& outputBuffer,
    const bool isNullTerminated
) const
{
    switch (encoding) {
        case (UTF8): {
            UTF8::Encode(outputBuffer, GET_FIRST_ELEMENT_ADDRESS(this->_codes), this->_codes.size());

            if (isNullTerminated) { outputBuffer.push_back(0x00); }
            break;
        }

        case (UTF16):
        case (UTF16BE):
        case (UTF16LE): {
            UTF16Options options;
            if (encoding != UTF16)
                options.SetEndianMode((encoding == UTF16BE) ? BigEndian : LittleEndian);

            UTF16::Encode(outputBuffer, GET_FIRST_ELEMENT_ADDRESS(this->_codes), this->_codes.size(), options);

            if (isNullTerminated) {
                outputBuffer.resize(outputBuffer.size() + 2);
                memset(&(outputBuffer[outputBuffer.size() - 2]), 0x00, 2);
            }
            break;
        }

        case (UTF32):
        case (UTF32BE):
        case (UTF32LE): {
            UTF32Options options;
            if (encoding != UTF32)
                options.SetEndianMode((encoding == UTF32BE) ? BigEndian : LittleEndian);

            UTF32::Encode(outputBuffer, GET_FIRST_ELEMENT_ADDRESS(this->_codes), this->_codes.size(), options);

            if (isNullTerminated) {
                outputBuffer.resize(outputBuffer.size() + 4);
                memset(&(outputBuffer[outputBuffer.size() - 4]), 0x00, 4);
            }
            break;
        }

        default: {
            THROW_EXCEPTION("Unsupported or unknown encoding requested.");
            break;
        }
    }

    return (outputBuffer.size());
}

string String::ConvertToStdString(Encoding encoding) const
{
    vector<uint8_t> tempBuffer;
    this->ConvertToEncodedString(encoding, tempBuffer);
    string result(reinterpret_cast<const char*>(GET_FIRST_ELEMENT_ADDRESS(tempBuffer)), tempBuffer.size());
    return (result);
}

wstring String::ConvertToStdWString(void) const
{
    // note: this will not work on all platforms as wchar_t's data representation is not standard defined
    size_t wcharSize = sizeof (wchar_t);
    Encoding encoding = UTF32;
 
    if (wcharSize == 2) {
        encoding = UTF16;
    }
    else if (wcharSize == 4) {
        encoding = UTF32;
    }
    else {
        THROW_EXCEPTION("Unsupported wchar implementation.");
    }

    vector<uint8_t> tempBuffer;
    this->ConvertToEncodedString(encoding, tempBuffer);
    wstring result(
        reinterpret_cast<const wchar_t*>(GET_FIRST_ELEMENT_ADDRESS(tempBuffer)),
        (tempBuffer.size() / wcharSize)
    );
    return (result);
}

bool String::IsEmpty(const String& str)
{
    return (str._codes.size() == 0);
}

String& String::operator=(const String& other)
{
    this->_codes.clear();

    if (other._codes.size() > 0) {
        this->_codes.insert(this->_codes.end(), other._codes.begin(), other._codes.end());
    }

    return (*this);
}

String& String::operator+=(const String& other)
{
    if (other._codes.size() > 0) {
        this->_codes.insert(this->_codes.end(), other._codes.begin(), other._codes.end());
    }

    return (*this);
}

String Core::operator+(const String& lhs, const String& rhs)
{
    String result(lhs);
    result += rhs;
    return (result);
}

bool Core::operator==(const String& lhs, const String& rhs)
{
    bool result = (lhs._codes.size() == rhs._codes.size());

    if (result) {
        size_t counter = 0;
        for (counter = 0; counter < lhs._codes.size(); counter++) {
            if (lhs._codes[counter] != rhs._codes[counter]) {
                return (false);
            }
        }
    }

    return (result);
}

void String::Initialize(const uint8_t* source, const std::size_t sourceLength, Encoding encoding)
{
    if (sourceLength != 0) {    
        switch (encoding) {
            case (UTF8): {
                UTF8::Decode(this->_codes, source, sourceLength);
                break;
            }

            case (UTF16):
            case (UTF16BE):
            case (UTF16LE): {
                UTF16Options options;
                if (encoding != UTF16)
                    options.SetEndianMode((encoding == UTF16BE) ? BigEndian : LittleEndian);

                UTF16::Decode(this->_codes, source, sourceLength, options);
                break;
            }

            case (UTF32):
            case (UTF32BE):
            case (UTF32LE): {
                UTF32Options options;
                if (encoding != UTF32)
                    options.SetEndianMode((encoding == UTF32BE) ? BigEndian : LittleEndian);

                UTF32::Decode(this->_codes, source, sourceLength, options);
                break;
            }

            default: {
                THROW_EXCEPTION("Unsupported or unknown encoding specified.");
                break;
            }
        }
    }
    return;
}

void String::Initialize(const wchar_t* source, const std::size_t sourceLength)
{
    // note: this will not work on all platforms as wchar_t's data representation is not standard defined
    size_t wcharSize = sizeof (wchar_t);
    Encoding encoding = UTF32;
 
    if (wcharSize == 2) {
        encoding = UTF16;
    }
    else if (wcharSize == 4) {
        encoding = UTF32;
    }
    else {
        THROW_EXCEPTION("Unsupported wchar implementation.");
    }

    this->Initialize(
        reinterpret_cast<const uint8_t*>(source),
        sourceLength * wcharSize,
        encoding
    );
    return;
}
