#include "Utils.hpp"

using namespace std;
using namespace UniCString;
using namespace UniCString::Core;
using namespace UniCString::Core::Utils;

namespace
{
    static Endian g_SystemEndian = SystemEndian;
} // namespace

Endian Utils::GetSystemEndian(void)
{
    if (g_SystemEndian != -1)
        return (g_SystemEndian);

    uint16_t testInt = 0x11EE;
    ptruint8_t octetPtr = reinterpret_cast<ptruint8_t>(&testInt);
    g_SystemEndian = BigEndian;
    if (*octetPtr == 0xEE)
        g_SystemEndian = LittleEndian;

    return (g_SystemEndian);
}
