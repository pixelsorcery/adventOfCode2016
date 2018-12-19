#include <iostream>

using namespace std;

const int allPositions[] = { 13, 17, 19, 7, 5, 3, 11 };
const int startLoc[] = { 10, 15, 17, 1, 0, 1, 0 };

int main()
{
    int time = 0;
    int positions[7];
    memcpy_s(positions, sizeof(positions), startLoc, sizeof(positions));

    while (positions[0] != positions[1] ||
           positions[0] != positions[2] ||
           positions[0] != positions[3] ||
           positions[0] != positions[4] ||
           positions[0] != positions[5] ||
           positions[0] != positions[6])
    {
        time++;
        for (int i = 0; i < 7; i++)
        {
            positions[i] = (startLoc[i] + time + i) % allPositions[i];
        }
    }

    cout << "all positions match at " << time-1 << endl;
    return 0;
}