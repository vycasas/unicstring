#if !defined(UNICSTRING_CORE_CODECS_UTF8_HPP)
#define UNICSTRING_CORE_CODECS_UTF8_HPP

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

class UTF8Options : public CodecOptions
{
public:
    UTF8Options(void) : CodecOptions(), _addBOM(false) { }

    bool AddBOM(void) const { return (this->_addBOM); }

    void SetAddBOM(const bool addBOM)
    {
        this->_addBOM = addBOM;
        return;
    }

    virtual void Reset(void)
    {
        CodecOptions::Reset();
        this->_addBOM = false;
        return;
    }

private:
    bool _addBOM;
};

class UTF8
{
public:
    static std::size_t Decode(
        std::vector<Unicode>& outputBuffer,
        const void* inputBuffer,
        const std::size_t inputBufferLength,
        const UTF8Options& options = UTF8Options()
    );

    static std::size_t Encode(
        std::vector<std::uint8_t>& outputBuffer,
        const Unicode* inputBuffer,
        const std::size_t inputBufferLength,
        const UTF8Options& options = UTF8Options()
    );

private:
    UTF8();
    UTF8(const UTF8&);
    UTF8& operator=(const UTF8&);

    static const std::uint8_t DEFAULT_BOM[3];
};

        } // namespace Codecs
    } // namespace Core
} // namespace UniCString

#endif // !defined(UNICSTRING_CORE_CODECS_UTF8_HPP)
