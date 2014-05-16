#if !defined(UNICSTRING_CORE_CODECS_UTF16_HPP)
#define UNICSTRING_CORE_CODECS_UTF16_HPP

#include <vector>

#include <Core/Types.hpp>
#include <Core/Unicode.hpp>
#include <Core/Codecs/CodecBase.hpp>

namespace UniCString
{
    namespace Core
    {
        namespace Codecs
        {

class UTF16Options : public CodecOptions
{
public:
    UTF16Options(void) : CodecOptions(), _addBOM(false), _endianMode(SystemEndian) { }

    bool AddBOM(void) const { return (this->_addBOM); }

    void SetAddBOM(const bool addBOM)
    {
        this->_addBOM = addBOM;
        return;
    }

    Endian EndianMode(void) const { return (this->_endianMode); }

    void SetEndianMode(Endian endianMode)
    {
        this->_endianMode = endianMode;
        return;
    }

    virtual void Reset(void)
    {
        CodecOptions::Reset();
        this->_addBOM = false;
        this->_endianMode = SystemEndian;
        return;
    }

private:
    bool _addBOM;
    Endian _endianMode;
};

class UTF16
{
public:
    static std::size_t Decode(
        std::vector<Unicode>& outputBuffer,
        const void* inputBuffer,
        const std::size_t inputBufferLength,
        const UTF16Options& options = UTF16Options()
    );

    static std::size_t Encode(
        std::vector<std::uint8_t>& outputBuffer,
        const Unicode* inputBuffer,
        const std::size_t inputBufferLength,
        const UTF16Options& options = UTF16Options()
    );

private:
    UTF16();
    UTF16(const UTF16&);
    UTF16& operator=(const UTF16&);

    static const std::uint8_t DEFAULT_BOM[2];
};

        } // namespace Codecs
    } // namespace Core
} // namespace UniCString

#endif // !defined(UNICSTRING_CORE_CODECS_UTF16_HPP)
