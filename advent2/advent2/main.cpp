#include <algorithm>
#include <iostream>
#include <string>
#include <cassert>

using namespace std;

int validLocations[] = { 2, 6, 7, 8, 10, 11, 12, 13, 14, 16, 17, 18, 22 };

bool isValid(int x, int y)
{
    int l = (y * 5) + x;
    
    for (int i = 0; i < sizeof(validLocations); i++)
    {
        if (validLocations[i] == l)
        {
            return true;
        }
    }
    return false;
}

int number(int x, int y)
{
    int l = (y * 5) + x;
    assert(l < 25);
    for (int i = 0; i < sizeof(validLocations); i++)
    {
        if (validLocations[i] == l)
        {
            return i;
        }
    }
    assert(!"invalid location");
    return -1;
}

int main()
{
    string line;
    const char* ptr;
    int xpos = 0;
    int ypos = 2;
    cout << "code is: ";
    while (getline(cin, line))
    {
        ptr = line.c_str();

        while (*ptr != '\0')
        {
            switch (*ptr)
            {
            case 'D':
                ypos = isValid(xpos, ypos + 1) ? ypos + 1 : ypos;
                break;
            case 'U':
                ypos = isValid(xpos, ypos - 1) ? ypos - 1 : ypos;
                break;
            case 'R':
                xpos = isValid(xpos + 1, ypos) ? xpos + 1 : xpos;
                break;
            case 'L':
                xpos = isValid(xpos - 1, ypos) ? xpos - 1 : xpos;
                break;
            default:
                assert(0);
            }
            ptr++;
        }
        cout << std::hex << number(xpos, ypos) + 1;
    }
    cout << endl;
    return 0;
}