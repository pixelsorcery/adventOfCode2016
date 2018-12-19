#include <iostream>
#include <string>
#include <unordered_map>
#include <vector>
#include <algorithm>

using namespace std;

constexpr int checksumSize = 5;

int main()
{
    string line;
    const char* ptr;
    long long int sum = 0;
    char rotatedString[256];

    while (getline(cin, line))
    {
        unordered_map<char, int> letters;
        vector<char> letterVec;
        char checksum[checksumSize];
        int id = 0;
        int numChars = 0;

        ptr = line.c_str();

        while (*ptr != '\0')
        {
            // get letters into map
            if (*ptr >= 'a' && *ptr <= 'z')
            {
                letters[*ptr]++;
                letterVec.push_back(*ptr);
            }

            if (*ptr >= 'a' && *ptr <= 'z' || *ptr == '-')
            {
                numChars++;
            }

            // get the id
            if (*ptr >= '0' && *ptr <= '9')
            {
                id = (*ptr - '0') * 100;
                ptr++;
                id += (*ptr - '0') * 10;
                ptr++;
                id += (*ptr - '0');
            }

            // get checksum
            if (*ptr == '[')
            {
                ptr++;
                for (int i = 0; i < checksumSize; i++)
                {
                    checksum[i] = *ptr;
                    ptr++;
                }
            }

            ptr++;
        }

        // sort vec by value in map
        sort(letterVec.begin(), letterVec.end(), [&letters](char& a, char& b) 
            {if (letters[a] != letters[b]) return letters[a] > letters[b]; else return a < b; });

        char calculatedCS[5] = { -1, -1, -1, -1, -1 };
        auto iter = letterVec.begin();
        for (int i = 0; i < checksumSize; i++)
        {
            calculatedCS[i] = *iter;
            while (i < 4 && calculatedCS[i] == *iter)
            {
                iter++;
            }
        }
        if (strncmp(checksum, calculatedCS, checksumSize) == 0)
        {
            sum += id;

            // rotate
            ptr = line.c_str();

            for (int i = 0; i < numChars; i++)
            {
                if (*ptr == '-')
                {
                    rotatedString[i] = ' ';
                }
                else
                {
                    rotatedString[i] = ((((*ptr - 'a') + id) % 26) + 'a');
                }
                
                ptr++;
            }

            if (strncmp(rotatedString, "north", 5) == 0)
            {
                cout << rotatedString << " id is: " << id << endl;
            }
        }
    }

    cout << "sum is: " << sum << endl;
    return 0;
}