#include <iostream>
#include <string>

using namespace std;

static constexpr int LENGTH = 8;
static constexpr int LETTERS = 26;

#define PART1 0

int main()
{
    string in = "";
    char answer[LENGTH];
    char array[LENGTH][LETTERS];

    memset(array, 0, LETTERS * LENGTH * sizeof(char));

    while (getline(cin, in))
    {
        for (int i = 0; i < LENGTH; i++)
        {
            array[i][in.c_str()[i] - 'a']++;
        }
    }

    // for each char
#if PART1
    for (int i = 0; i < LENGTH; i++)
    {   
        int maxOccurrences = 0;
        char letter = 0;

        for (int j = 0; j < LETTERS; j++)
        {
            if (array[i][j] > maxOccurrences)
            {
                letter = j + 'a';
                maxOccurrences = array[i][j];
            }
        }
        answer[i] = letter;
    }
#else
    for (int i = 0; i < LENGTH; i++)
    {
        int maxOccurrences = INT_MAX;
        char letter = 0;

        for (int j = 0; j < LETTERS; j++)
        {
            if (array[i][j] < maxOccurrences)
            {
                letter = j + 'a';
                maxOccurrences = array[i][j];
            }
        }
        answer[i] = letter;
    }
#endif

    cout << "message is: " << answer << endl;
    return 0;
}