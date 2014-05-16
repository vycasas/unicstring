#if !defined(UNICSTRING_CORE_CODECS_CODECBASE_HPP)
#define UNICSTRING_CORE_CODECS_CODECBASE_HPP

namespace UniCString
{
    namespace Core
    {
        namespace Codecs
        {

// Base class for encoding/decoding options
class CodecOptions
{
public:
    CodecOptions(void) : _ignoreCodingErrors(false) { }

    bool IgnoreCodingErrors(void) const { return (this->_ignoreCodingErrors); }

    void SetIgnoreCodingErrors(const bool ignoreCodingErrors)
    {
        this->_ignoreCodingErrors = ignoreCodingErrors;
        return;
    }

    virtual void Reset(void)
    {
        this->_ignoreCodingErrors = false;
        return;
    }

protected:
    bool _ignoreCodingErrors;
};

        } // namespace Codecs
    } // namespace Core
} // namespace UniCString

#endif // !defined(UNICSTRING_CORE_CODECS_CODECBASE_HPP)
