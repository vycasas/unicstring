#if !defined(UNICSTRING_CXX_UNICEXCEPTION_HXX)
#define UNICSTRING_CXX_UNICEXCEPTION_HXX

#include <cstddef>
#include <exception>

#include <UniCString/C/UniCTypes.h>

namespace UniCString
{
    ///
    /// Exception class for handling and obtaining detailed information from errors.
    ///
    class Exception : std::exception
    {
    public:
        ///
        /// Creates a new Exception instance with the given implementation.
        /// @param impl The implementation detail.
        /// @remarks Users normally does not need to call this function explicitly.
        /// 
        Exception(UniCErrorT impl) : _impl(impl) { }

        ///
        /// Destroys this Exception instance. 
        /// 
        virtual ~Exception(void);

        ///
        /// Gets the message describing the error.
        /// @returns The message describing the error.
        /// 
        const char* GetMessage(void) const;

        ///
        /// Gets the file name where the error happened.
        /// @returns The file name where the error happened.
        /// 
        const char* GetFileName(void) const;

        ///
        /// Gets the name of the function which caused the error.
        /// @returns The name of the function which caused the error.
        /// 
        const char* GetFunctionName(void) const;

        ///
        /// Gets the line number in the file where the error happened.
        /// @returns The line number in the file where the error happened.
        /// 
        std::size_t GetLineNumber(void) const;

        ///
        /// Gets the full message describing the error.
        /// @returns The full message describing the error.
        /// 
        const char* GetFullMessage(void) const;

        ///
        /// Gets the full message describing the error.
        /// @returns The full message describing the error.
        /// 
#if (__cplusplus <= 199711L)
        virtual const char* what(void) const
#else // (__cplusplus <= 199711L)
        virtual const char* what(void) const noexcept
#endif // (__cplusplus <= 199711L)
        {
            return (this->GetFullMessage());
        }

        // Allows easy printing of this exception to an output stream.
        friend std::ostream& operator<<(std::ostream& outStream, const Exception& ex)
        {
            return (outStream << ex.GetFullMessage());
        }

    private:
        UniCErrorT _impl;
    };
} // namespace UniCString

#include "UniCException.detail"

#endif // UNICSTRING_CXX_UNICEXCEPTION_HXX
