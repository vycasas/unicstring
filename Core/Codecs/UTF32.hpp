#if !defined(UNICSTRING_CORE_CODECS_UTF32_HPP)
#define UNICSTRING_CORE_CODECS_UTF32_HPP

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

class UTF32Options : public CodecOptions
{
public:
    UTF32Options(void) : CodecOptions(), _addBOM(false), _endianMode(SystemEndian) { }

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

class UTF32
{
public:
    static std::size_t Decode(
        std::vector<Unicode>& outputBuffer,
        const void* inputBuffer,
        const std::size_t inputBufferLength,
        const UTF32Options& options = UTF32Options()
    );

    static std::size_t Encode(
        std::vector<std::uint8_t>& outputBuffer,
        const Unicode* inputBuffer,
        const std::size_t inputBufferLength,
        const UTF32Options& options = UTF32Options()
    );

private:
    UTF32();
    UTF32(const UTF32&);
    UTF32& operator=(const UTF32&);

    static const std::uint8_t DEFAULT_BOM[4];
};

        } // namespace Codecs
    } // namespace Core
} // namespace UniCString

#endif // !defined(UNICSTRING_CORE_CODECS_UTF32_HPP)
