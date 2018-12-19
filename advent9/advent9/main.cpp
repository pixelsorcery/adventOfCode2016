#include <iostream>
#include <string>
#include <cassert>

using namespace std;

unsigned long long process(string str)
{
    unsigned long long count = 0;

    const char* ptr = str.c_str();
    int i = 0;
    while (*ptr != '\0')
    {
        if (*ptr >= 'A' && *ptr <= 'Z')
        {
            count++;
            ptr++; i++;
        }
        else if (*ptr == '(')
        {
            unsigned long long num = 0;
            unsigned long long  len = 0;
            ptr++; i++;
            len = *ptr - '0';
            ptr++; i++;
            while (*ptr >= '0' && *ptr <= '9')
            {
                len *= 10;
                len += *ptr - '0';
                ptr++; i++;
            }
            ptr++; i++;
            num = *ptr - '0';
            *ptr++; i++;
            while (*ptr >= '0' && *ptr <= '9')
            {
                num *= 10;
                num += *ptr - '0';
                ptr++; i++;
            }
            ptr++; i++;

            count += num * process(str.substr(i, len));
            ptr += len;
            i += len;
        }
        else
        {
            assert(0);
        }
        //ptr++;
        //i++;
    }

    return count;
}


int main()
{
    string input;
    string output = "";
    getline(cin, input);
    
    const char* ptr = input.c_str();
    int numChars = 0;
    int long long length;

#if PART1
    while (*ptr != '\0')
    {
        if (*ptr >= 'A' && *ptr <= 'Z')
        {
            output += *ptr;
        }
        if (*ptr == '(')
        {
            int a = 0;
            int b = 0;
            ptr++;
            // read in numbers
            a = *ptr - '0';
            ptr++;
            while (*ptr >= '0' && *ptr <= '9')
            {
                a *= 10;
                a += *ptr - '0';
                ptr++;
            }
            ptr++;
            b = *ptr - '0';
            ptr++;
            while (*ptr >= '0' && *ptr <= '9')
            {
                b *= 10;
                b += *ptr - '0';
                ptr++;
            }
            ptr++;

            for (int i = 0; i < b; i++)
            {
                for (int j = 0; j < a; j++)
                {
                    output += ptr[j];
                }
            }
            ptr += a - 1;
        }
        ptr++;
    }

    cout << "total: " << output.length() << endl;
#else
    unsigned long long count = process(input);
    cout << "total: " << count << endl;
#endif
    return 0;
}