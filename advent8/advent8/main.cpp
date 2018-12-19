#include <iostream>
#include <string>
#include <cassert>

#define FOR(x, size) for (int x = 0; x < size; x++)
using namespace std;

static constexpr int WIDTH  = 50;
static constexpr int HEIGHT = 6;

char screen[WIDTH * HEIGHT];
char temp[WIDTH];

int main()
{
    string cmd;
    string junk;
    char c;

    while (cin >> cmd)
    {
        if (cmd == "rect")
        {
            int x = 0;
            int y = 0;
            char junk;
            cin >> x;
            cin >> junk;
            assert(junk == 'x');
            cin >> y;

            FOR(h, y) 
            {
                FOR(w, x) 
                {
                    screen[(h * WIDTH) + w] = 1;
                }
            }
        }
        else if (cmd == "rotate")
        { 
            int position;
            int amt;

            cin >> cmd;
            assert(cmd == "column" || cmd == "row");

            cin >> c;
            cin >> c;
            cin >> position;
            cin >> junk;
            assert(junk == "by");
            cin >> amt;

            if (cmd == "row")
            {
                char* ptr = &screen[WIDTH * position];
                FOR(i, WIDTH)
                {
                    int newPos = (i + amt) % WIDTH;
                    temp[newPos] = ptr[i];
                }
                memcpy_s(&screen[WIDTH * position], WIDTH, temp, WIDTH);
            }
            else
            {
                // find pointer to column
                char *ptr = &screen[position];
                FOR(i, HEIGHT)
                {
                    int newPos = (i + amt) % HEIGHT;
                    temp[newPos] = screen[(WIDTH * i) + position];
                }
                FOR(i, HEIGHT)
                {
                    screen[(WIDTH * i) + position] = temp[i];
                }
            }
        }
    }

    int sum = 0;
    FOR(i, WIDTH * HEIGHT)
    {
        sum += screen[i];
    }
    cout << "lights on is: " << sum << endl;
    return 0;
}