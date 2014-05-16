#if !defined(UNICSTRING_CORE_STRING_HPP)
#define UNICSTRING_CORE_STRING_HPP

#include <limits>
#include <string>
#include <vector>
#include <ostream>

#include <Core/Common.hpp>
#include <Core/Types.hpp>
#include <Core/Unicode.hpp>

namespace UniCString
{
    namespace Core
    {

// The core String class represents a string of characters
class String
{
public:
    typedef enum _Encoding
    {
        UTF8 = 0,
        UTF16 = 1,
        UTF16BE = 2,
        UTF16LE = 3,
        UTF32 = 4,
        UTF32BE = 5,
        UTF32LE = 6
    }
    Encoding, * PEncoding;

    // ================
    // Constructors
    String(void);
    String(const String& source);

    String(const char character, Encoding)
    {
        this->Initialize(reinterpret_cast<const std::uint8_t*>(&character), 1, UTF8);
        return;
    }

    String(const std::string& source, Encoding encoding = String::UTF8)
    {
        this->Initialize(
            reinterpret_cast<const std::uint8_t*>(GET_FIRST_ELEMENT_ADDRESS(source)),
            source.size(),
            encoding
        );
        return;
    }

    // wchar_t is implementation detail.
    // The compiler may or may not be using Unicode encoding for wchar_t implementations.
    String(const wchar_t character)
    {
        this->Initialize(&character, 1);
        return;
    }

    String(const std::wstring& source)
    {
        this->Initialize(source.c_str(), source.size());
        return;
    }

    String(const void* source, const std::size_t sourceLength, Encoding encoding = String::UTF8)
    {
        this->Initialize(reinterpret_cast<const std::uint8_t*>(source), sourceLength, encoding);
        return;
    }

    String(const std::vector<std::uint8_t>& source, Encoding encoding = String::UTF8)
    {
        this->Initialize(GET_FIRST_ELEMENT_ADDRESS(source), source.size(), encoding);
        return;
    }

#if (__cplusplus > 199711L)
    String(const std::u16string& source);
    String(const std::u32string& source);
#endif // (__cplusplus > 199711L)

    // ================
    // Destructor
    virtual ~String(void);

    // ================
    // Properties

    // returns the number of Unicode codepoints
    std::size_t GetLength(void) const;

    // ================
    // String modifications

    // ================
    // Conversion operations

    std::size_t ConvertToEncodedString(
        Encoding encoding,
        std::vector<std::uint8_t>& outputBuffer,
        const bool isNullTerminated = false
    ) const;

    std::string ConvertToStdString(Encoding encoding = UTF8) const;

    // see notes about wchar_t above
    std::wstring ConvertToStdWString(void) const;

#if defined(CXX11_OR_LATER_SUPPORT)
    std::u16string ConvertToStdU16String(void) const;
    std::u32string ConvertToStdU32String(void) const;
#endif // defined(CXX11_OR_LATER_SUPPORT)

    // ================
    // Utilities

    static bool IsEmpty(const String& str);

    // ================
    // Overloaded functions
    String& operator=(const String& other);
    String& operator+=(const String& other);

    // ================
    // Friend functions
    friend String operator+(const String& lhs, const String& rhs);
    friend bool operator==(const String& lhs, const String& rhs);
    friend bool operator!=(const String& lhs, const String& rhs) { return (!(lhs == rhs)); }

    friend std::ostream& operator<<(std::ostream& outStream, const String& str)
    {
        return (outStream << str.ConvertToStdString());
    }

    friend std::wostream& operator<<(std::wostream& outStream, const String& str)
    {
        return (outStream << str.ConvertToStdWString());
    }

private:
    std::vector<Unicode> _codes;

    void Initialize(const std::uint8_t* source, const std::size_t sourceLength, Encoding encoding);
    void Initialize(const wchar_t* source, const std::size_t sourceLength);
}; // class String

    } // namespace Core
} // namespace UniCString

#endif // !defined(UNICSTRING_CORE_STRING_HPP)
