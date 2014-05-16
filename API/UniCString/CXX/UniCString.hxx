/// @file
#if !defined(UNICSTRING_CXX_UNISTRING_HXX)
#define UNICSTRING_CXX_UNISTRING_HXX

#include <string>
#include <vector>

#include <UniCString/C/UniCString.h>
#include <UniCString/C/UniCTypes.h>

namespace UniCString
{
    ///
    /// Represents a string of characters. Each character is identified by its Unicode code point. This class provides
    /// various utilies to perform string operations such as creation, appending, encoding, and decoding.
    ///
    class String
    {
    public:
        ///
        /// The various Unicode encoding supported by the String class.
        ///
        typedef enum _Encoding
        {
            UTF8 = UniCUTF8,        ///< UTF-8 Encoding.
            UTF16 = UniCUTF16,      ///< UTF-16 System Encoding.
            UTF16BE = UniCUTF16BE,  ///< UTF-16 Big Endian Encoding.
            UTF16LE = UniCUTF16LE,  ///< UTF-16 Little Endian Encoding.
            UTF32 = UniCUTF32,      ///< UTF-32 System Endian Encoding.
            UTF32BE = UniCUTF32BE,  ///< UTF-32 Big Endian Encoding.
            UTF32LE = UniCUTF32LE   ///< UTF-32 Little Endian Encoding.
        }
        Encoding;

        ///
        /// Creates an empty String instance.
        ///
        String(void);

        ///
        /// Creates a new String instance from an existing String.
        /// @param other The other String instance to create a copy of.
        ///
        String(const String& other);

        ///
        /// Creates a new String instance from a single character.
        /// @param character The character to create a new String instance from.
        ///
        String(const char character);

        ///
        /// Creates a new String instance from a single character.
        /// @param character The character to create a new String instance from.
        ///
        String(const wchar_t character);

        ///
        /// Creates a new String instance from an existing std::string instance.
        /// @param source The std::string to create a new String instance from.
        /// @param encoding The encoding of the source parameter.
        ///
        String(const std::string& source, Encoding encoding = String::UTF8);

        ///
        /// Creates a new String instance from an existing std::wstring instance.
        /// @param source The std::wstring to create a new String instance from.
        /// @remarks The encoding of the source parameter depends on the platform's definition of wchar_t. This
        ///     constructor may not work correctly on all platforms.
        ///
        String(const std::wstring& source);

        ///
        /// Creates a new String instance from a buffer with a specified encoding.
        /// @param source The buffer to create a new String instance from.
        /// @param encoding The encoding of the source parameter.
        ///
        String(const std::vector<unsigned char>& source, Encoding encoding = String::UTF8);

        ///
        /// Destroys this String instance.
        ///
        virtual ~String(void);

        ///
        /// A utility function to check whether a String is an empty String (contains no Unicode characters), or not.
        /// @param str The String to check.
        /// @returns True if the String does not contain any Unicode characters.
        ///
        static bool IsEmpty(const String& str);

        ///
        /// Gets the number of Unicode characters (represented by its Unicode code point) this String contains.
        /// @returns The number of Unicode characters in this String.
        ///
        std::size_t GetLength(void) const;

        ///
        /// Converts this String into the specified encoding.
        /// @param encoding The encoding to convert this String into.
        /// @param outputBuffer The buffer where to write the encoded String.
        /// @param isNullTerminated Whether to add a NULL character at the end of the encoded buffer.
        /// @returns The size of outputBuffer.
        ///
        std::size_t ConvertToEncodedString(
            Encoding encoding,
            std::vector<unsigned char>& outputBuffer,
            const bool isNullTerminated = false
        ) const;

        ///
        /// Converts this String into std::string with the specified encoding.
        /// @param encoding The encoding to convert this String into.
        /// @returns The converted String.
        ///
        std::string ConvertToStdString(Encoding encoding = String::UTF8) const;

        ///
        /// Converts this String into system defined std::wstring.
        /// @returns The converted String.
        /// @remarks The encoding of the std::wstring depends on the compiler/platform implementation. This function may
        ///     not work correctly on all platforms.
        ///
        std::wstring ConvertToStdWString(void) const;

        ///
        /// Assigns another String to this String.
        /// @param The source String instance to assign to this String.
        /// @returns This String instance with updated value.
        ///
        String& operator=(const String& other);

        ///
        /// Appends another String to this String.
        /// @param The source String instance to append to this String.
        /// @returns This String instance with updated value.
        ///
        String& operator+=(const String& other);

        ///
        /// Combines both Strings and creates a new instance.
        /// @param lhs The first String to combine.
        /// @param rhs The second String to combine.
        /// @returns A new String instance with the combined value.
        ///
        friend String operator+(const String& lhs, const String& rhs);

        ///
        /// Compares whether both Strings are equal with each other.
        /// @param lhs The first String to compare.
        /// @param rhs The second String to compare.
        /// @returns True if both Strings have the same amount of Unicode characters and the other of the Unicode
        ///     characters are the same.
        ///
        friend bool operator==(const String& lhs, const String& rhs);

        ///
        /// Compares whether both Strings are not equal with each other.
        /// @param lhs The first String to compare.
        /// @param rhs The second String to compare.
        /// @returns True if both Strings does not have the same amount of Unicode characters or the other of the
        ///     Unicode characters are the different.
        ///
        friend bool operator!=(const String& lhs, const String& rhs);

        ///
        /// Prints the contents of this String to the output stream.
        /// @param outStream The output stream sink to print the String at.
        /// @param str The String to print.
        /// @returns The output stream where the String was printed.
        ///
        friend std::ostream& operator<<(std::ostream& outStream, const String& str);

        ///
        /// Prints the contents of this String to the output stream.
        /// @param outStream The output stream sink to print the String at.
        /// @param str The String to print.
        /// @returns The output stream where the String was printed.
        ///
        friend std::wostream& operator<<(std::wostream& outStream, const String& str);

    private:
        UniCStringT _impl;
    };
} // namespace UniCString

#include "UniCString.detail"

#endif // !defined(UNICSTRING_CXX_UNISTRING_HXX)
