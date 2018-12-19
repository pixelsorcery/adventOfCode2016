#include <iostream>
#include <string>
#include <cassert>
#include <unordered_map>

using namespace std;

unordered_map<string, int> visited;

enum DIR
{
    NORTH    = 0,
    EAST     = 1,
    SOUTH    = 2,
    WEST     = 3,
    NUM_DIRS = 4
};

int main()
{
    string str;
    char dir;
    char junk;
    int dist;
    int x = 0;
    int y = 0;
    DIR current = NORTH;
    while (cin >> dir)
    {
        cin >> dist;
        cin >> junk;
        assert(junk == ',');

        switch (dir)
        {
        case 'R':
            current = static_cast<DIR>((current + 1) % NUM_DIRS);
            break;
        case 'L':
            current = ((current - 1) < 0) ? WEST : static_cast<DIR>((current - 1));
            break;
        default:
            assert(0);
            break;
        }

        switch (current)
        {
        case NORTH:
            for (int i = 0; i < dist; i++)
            {
                y += 1;
                string l = to_string(x) + "_" + to_string(y);
                visited[l]++;
                if (visited[l] > 1)
                {
                    goto end;
                }
            }

            break;
        case SOUTH:
            for (int i = 0; i < dist; i++)
            {
                y -= 1;
                string l = to_string(x) + "_" + to_string(y);
                visited[l]++;
                if (visited[l] > 1)
                {
                    goto end;
                }
            }
            break;
        case EAST:
            for (int i = 0; i < dist; i++)
            {
                x += 1;
                string l = to_string(x) + "_" + to_string(y);
                visited[l]++;
                if (visited[l] > 1)
                {
                    goto end;
                }
            }
            break;
        case WEST:
            for (int i = 0; i < dist; i++)
            {
                x -= 1;
                string l = to_string(x) + "_" + to_string(y);
                visited[l]++;
                if (visited[l] > 1)
                {
                    goto end;
                }
            }
            break;
        default:
            assert(0);
            break;
        }
    }
end:
    int total_distance = abs(x) + abs(y);

    cout << "block: " << total_distance << endl;
    return 0;
}