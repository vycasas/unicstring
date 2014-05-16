#if !defined(UNICSTRING_CORE_EXCEPTION_HPP)
#define UNICSTRING_CORE_EXCEPTION_HPP

#include <iostream>
#include <string>

#include <Core/Common.hpp>
#include <Core/Types.hpp>

namespace UniCString
{
    namespace Core
    {

// An extended version of the std::exception class which stores additional exception message useful for debugging.
class Exception : public std::exception
{
public:
    Exception(
        const std::string& message = std::string(),
        const std::string& file = std::string(),
        const std::string& function = std::string(),
        const std::size_t& line = 0x00
    );

    Exception(const Exception& e);

    virtual ~Exception(void);

    virtual const char* what(void) const NO_EXCEPTION;

    std::string GetMessage(void) const { return (this->_message); }
    std::string GetFileName(void) const { return (this->_file); }
    std::string GetFunctionName(void) const { return (this->_function); }
    std::size_t GetLineNumber(void) const { return (this->_line); }
    std::string GetFullMessage(void) const { return (this->_fullMessage); }

private:
    // The exception message.
    std::string _message;

    // The file name where the exception occurred.
    std::string _file;

    // The name of the function which threw the exception.
    std::string _function;

    // The line number in the file where the exception was thrown.
    std::size_t _line;

    // The full message stores all the information and the string that will be returned by the what() function.
    std::string _fullMessage;

    // Helper function to easily print out this exception to an output stream.
    friend std::ostream& operator<<(std::ostream& outStream, const Exception& ex);
};

    } // namespace Core
} // namespace UniCString

#define THROW_EXCEPTION(message) throw (UniCString::Core::Exception(message, __FILE__, __FUNCTION__, __LINE__))

#endif // !defined(UNICSTRING_CORE_EXCEPTION_HPP)
