#include <iostream>
#include <string>

using namespace std;

int main()
{
    string input = "^.....^.^^^^^.^..^^.^.......^^..^^^..^^^^..^.^^.^.^....^^...^^.^^.^...^^.^^^^..^^.....^.^...^.^.^^.^";
    int inputLength = input.size();
    int rows = 400000;

    char* traps = new char[rows * inputLength * sizeof(char)];
    memcpy_s(traps, inputLength, input.c_str(), inputLength);

    // already got the first row
    for (int i = 1; i < rows; i++)
    {
        for (int j = 0; j < inputLength; j++)
        {
            bool l = (j == 0) ? 0 : traps[(i - 1) * inputLength + (j - 1)] == '^';
            bool c = traps[(i - 1) * inputLength + j] == '^';
            bool r = (j == inputLength-1) ? 0 : traps[(i - 1) * inputLength + (j + 1)] == '^';

            // Its left and center tiles are traps, but its right tile is not.
            // Its center and right tiles are traps, but its left tile is not.
            // Only its left tile is a trap.
            // Only its right tile is a trap.
            if ((l && c && !r) ||
                !l && c && r ||
                !l && !c && r || 
                l && !c &&!r)
            {
                traps[i * inputLength + j] = '^';
            }
            else
            {
                traps[i * inputLength + j] = '.';
            }
        }
    }

    int sum = 0;
    for (int i = 0; i < inputLength * rows; i++)
    {
        if (traps[i] == '.') sum++;
    }

    cout << "sum: " << sum;
    return 0;
}