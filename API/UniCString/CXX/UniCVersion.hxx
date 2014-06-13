/// @file
#if !defined(UNICSTRING_CXX_UNICVERSION_HXX)
#define UNICSTRING_CXX_UNICVERSION_HXX

#include <string>

namespace UniCString
{
    namespace Version
    {
        ///
        /// Gets the version year of this library.
        /// @returns The version year of this library.
        ///
        size_t GetVersionYear(void)
        {
            return (UniCVersionGetYear());
        }

        ///
        /// Gets the version month of this library.
        /// @returns The version month of this library.
        ///
        size_t GetVersionMonth(void)
        {
            return (UniCVersionGetMonth());
        }

        ///
        /// Gets the version day of this library.
        /// @returns The version day of this library.
        ///
        size_t GetVersionDay(void)
        {
            return (UniCVersionGetDay());
        }

        ///
        /// Gets the build version of this library.
        /// @returns The build version of this library.
        ///
        size_t GetVersionBuild(void)
        {
            return (UniCVersionGetBuild());
        }

        ///
        /// Gets the version string of this library.
        /// @returns The version string of this library.
        ///
        std::string GetVersionString(void)
        {
            return (std::string(UniCVersionGetString()));
        }
    } // namespace Version
} // namespace UniCString

#endif // !defined(UNICSTRING_CXX_UNICVERSION_HXX)
