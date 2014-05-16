#include "Exception.hpp"

#include <sstream>

using namespace std;
using namespace UniCString;
using namespace UniCString::Core;

Exception::Exception(const std::string& message, const std::string& file, const std::string& function, const std::size_t& line) :
    std::exception(),
    _message(message),
    _file(file),
    _function(function),
    _line(line)
{
    stringstream iss;
    iss << this->_message << "(" << this->_file << "@" << this->_function << ":" << this->_line << ").";
    _fullMessage = iss.str();
    return;
}

Exception::Exception(const Exception& e) :
    std::exception(),
    _message(e._message),
    _file(e._file),
    _function(e._function),
    _line(e._line)
{
    stringstream iss;
    iss << this->_message << "(" << this->_file << "@" << this->_function << ":" << this->_line << ").";
    _fullMessage = iss.str();
    return;
}

Exception::~Exception(void)
{
    return;
}

const char* Exception::what(void) const NO_EXCEPTION
{
    return (this->_fullMessage.c_str());
}

ostream& Core::operator<<(ostream& outStream, const Exception& ex)
{
    return (outStream << ex.what());
}
