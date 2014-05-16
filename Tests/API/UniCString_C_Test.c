#include <stddef.h>
#include <stdio.h>

#include <UniCString/UniCString.h>

int main(void)
{
    UniCStringT ustr;
    UniCErrorT error;
    size_t result;
    unsigned char utf8String[5] = {
        0xE3, 0x81, 0x82, /* "あ" */
        0xC3, 0xB6 /* "ö" */
    };
    unsigned char utf16String[4] = { 0x00, 0x00, 0x00, 0x00 };

    error = UniCStringCreateFromBuffer(utf8String, 5, UniCUTF8, &ustr);
    if (UniCBoolIsTrue(UniCIsError(error))) {
        fprintf(stdout, "Test Failed (%s:%d): %s\n", __FILE__, __LINE__, UniCErrorGetFullMessage(error));
        return (-1);
    }

    error = UniCStringGetLength(ustr, &result);
    if (UniCBoolIsTrue(UniCIsError(error))) {
        fprintf(stdout, "Test Failed (%s:%d): %s\n", __FILE__, __LINE__, UniCErrorGetFullMessage(error));
        return (-2);
    }
    if (result != 2) {
        fprintf(
            stdout,
            "Test Failed (%s:%d): Incorrect String length. Expected '2', but was '%lu'\n",
            __FILE__, __LINE__, result
        );
        return (-2);
    }

    error = UniCStringEncode(ustr, UniCUTF16BE, utf16String, 4, UniCFalse, &result);
    if (UniCBoolIsTrue(UniCIsError(error))) {
        fprintf(stdout, "Test Failed (%s:%d): %s\n", __FILE__, __LINE__, UniCErrorGetFullMessage(error));
        return (-3);
    }
    if ((utf16String[0] != 0x30) || (utf16String[1] != 0x42)) {
        fprintf(
            stdout,
            "Test Failed (%s:%d): Invalid UTF-16 encoding. Expected '0x3042', but was '0x%04X'\n",
            __FILE__, __LINE__, ((utf16String[0] << 0x08) | (utf16String[1] << 0x00))
        );
        return (-3);
    }

    UniCStringDestroy(ustr);

    fprintf(stdout, "All tests passed.\n");

    return (0);
}
