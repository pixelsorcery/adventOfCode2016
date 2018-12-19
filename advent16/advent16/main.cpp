#include <iostream>
#include <algorithm>
#include <string>

using namespace std;

int main()
{
    string input = "01111001100111011";
    long long length = 35651584;
    string result = input;
    // dragon curve expansion
    while (result.size() < length)
    {
        string a = result;
        string b = result;
        reverse(b.begin(), b.end());
        replace(b.begin(), b.end(), '0', '2');
        replace(b.begin(), b.end(), '1', '0');
        replace(b.begin(), b.end(), '2', '1');
        result = a + "0" + b;
    }

    // checksum
    string cs = result.substr(0, length);
    //string cs = "110010110100";
    do
    {
        string temp = "";
        const char* ptr = cs.c_str();
        for (long long i = 0; i < cs.size(); i += 2)
        {
            if (ptr[i] == ptr[i + 1])
            {
                temp += "1";
            }
            else
            {
                temp += "0";
            }
        }
        cs = temp;
        cout << "size: " << cs.size() << endl;;
    } while (0 == cs.size() % 2);

    cout << "checksum: " << cs << endl;

    return 0;
}