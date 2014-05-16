#include <cstring>
#include <iostream>
#include <string>
#include <vector>

#include <Core/Exception.hpp>
#include <Core/String.hpp>

int main(void)
{
    using namespace std;
    using namespace UniCString;
    using namespace UniCString::Core;

    // testing variables
    String testString;
    size_t result = 0;
    string stdString;
    wstring stdWString;

    try {
        result = testString.GetLength();
        if (result != 0) {
            cout << "Test Failed (" << __FILE__ << ":" << __LINE__ << "): " <<
                "Empty string returns a length of " << result << "." << endl;
            return (-2);
        }

        // create a string from char type
        testString = String("SampleString");
        result = testString.GetLength();
        if (result != 12) {
            cout << "Test Failed (" << __FILE__ << ":" << __LINE__ << "): " <<
                "Invalid String length. Expected 12 was '" << result << "'." << endl;
            return (-3);
        }

        // create a string from wchar_t type
        testString = String(L"SampleString");
        result = testString.GetLength();
        if (result != 12) {
            cout << "Test Failed (" << __FILE__ << ":" << __LINE__ << "): " <<
                "Invalid String length. Expected 12 was '" << result << "'." << endl;
            return (-4);
        }

        // test conversion
        testString = String(L"SampleString");
        stdString = testString.ConvertToStdString();
        if (stdString.size() != 12) {
            cout << "Test Failed (" << __FILE__ << ":" << __LINE__ << "): " <<
                "Converted string has invalid length. Expected 12 was '" << result << "'." << endl;
            return (-5);
        }

        // test concatenation (including implicit promotion)
        testString += String(L"あう");
        result = testString.GetLength();
        if (result != 14) {
            cout << "Test Failed (" << __FILE__ << ":" << __LINE__ << "): " <<
                "Invalid String length. Expected 14 was '" << result << "'." << endl;
            return (-6);
        }

        // test comparison
        testString = String(L"⽔");
        if (testString != String(L"⽔")) {
            cout << "Test Failed (" << __FILE__ << ":" << __LINE__ << "): " <<
                "String comparison failed on similar Strings." << endl;
            return (-7);
        }

        cout << "All tests passed." << endl;
    }
    catch (Exception& e) {
        cerr << "An Exception was caught: \"" << e << "\"." << endl;
        return (-1);
    }
    catch (exception& e) {
        cerr << "An std::exception was caught: \"" << e.what() << "\"." << endl;
        return (-1);
    }
    catch (...) {
        cerr << "An unknown error has occurred." << endl;
        return (-1);
    }

    return (0);
}
