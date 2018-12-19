#include <iostream>
#include <string>
#include <vector>
#include <cassert>
#include <unordered_map>
#include <queue>
#include <memory>
#include <climits>
#include <algorithm>

using namespace std;

#define WIDTH 183
#define HEIGHT 36
#define NUM_VALS 8

//#define WIDTH 11
//#define HEIGHT 5
//#define NUM_VALS 5

struct Node
{
    int x;
    int y;
    int steps;
};

bool isValid(char* map, int x, int y)
{
    if (map[y * WIDTH + x] == '#')
    {
        //cout << map[y * WIDTH + x] << endl;
        return false;
    }
    //cout << "pushing " << x << " " << y << endl;
    return true;
}

int main()
{
    char map[37 * 183];
    char originalMap[37 * 183];
    char c;
    int x = 0;
    int y = 0;

    int distances[NUM_VALS][NUM_VALS];

    vector<Node> numNodes;

    while (cin >> c)
    {
        map[(y * WIDTH) + x] = c;
        originalMap[(y * WIDTH) + x] = c;
        //cout << c;
        if (c >= '0' && c <= '9')
        {
            Node num{ x, y, 0 };
            numNodes.push_back(num);
        }
        if (x != 0 && x % 183 == 0)
        {
            y++;
            x = 0;
        }
        x++;
    }

    // get distances to all the nodes
    for (auto numNode : numNodes)
    {
        memcpy(map, originalMap, WIDTH * HEIGHT * sizeof(char));
        char num = map[numNode.y * WIDTH + numNode.x];
        queue<Node> q = {};
        q.push(numNode);
        int visited = 0;

        while (q.size() > 0)
        {
            Node n = q.front();
            q.pop();

            if (map[n.y * WIDTH + n.x] == '#')
            {
                continue;
            }

            if (map[n.y * WIDTH + n.x] >= '0' &&
                map[n.y * WIDTH + n.x] <= '9')
            {
                //cout << map[n.y * WIDTH + n.x] << endl;
                visited++;
                cout << num << "-" << map[n.y * WIDTH + n.x] << " : " << n.steps << endl;
                distances[num - '0'][map[n.y * WIDTH + n.x] - '0'] = n.steps;
                if (visited == NUM_VALS)
                {   
                    break;
                }
            }

            map[n.y * WIDTH + n.x] = '#';

            if (isValid(map, n.x + 1, n.y))
            {
                //cout << n.steps + 1 << endl;
                Node nn{ n.x + 1, n.y, n.steps + 1 };
                q.push(nn);
            }

            if (isValid(map, n.x - 1, n.y))
            {
                //cout << n.steps + 1 << endl;
                Node nn{ n.x - 1, n.y, n.steps + 1 };
                q.push(nn);
            }

            if (isValid(map, n.x, n.y + 1))
            {
                //cout << n.steps + 1 << endl;
                Node nn{ n.x, n.y + 1, n.steps + 1 };
                q.push(nn);
            }

            if (isValid(map, n.x, n.y - 1))
            {
                //cout << n.steps + 1 << endl;
                Node nn{ n.x, n.y - 1, n.steps + 1 };
                q.push(nn);
            }
        }
    }

    char permutations[] = { '0', '1', '2', '3', '4', '5', '6','7', '0' };
    //char permutations[] = { '0', '1', '2', '3', '4' };
    char solution[NUM_VALS+1];
    solution[0] = 0;
    int smallestDist = INT_MAX;

    // tsp
    while (next_permutation(permutations+1, permutations + NUM_VALS))
    {
        int sum = 0;
        for (int i = 1; i < NUM_VALS + 1; i++)
        {
            int distance = distances[permutations[i - 1] - '0'][permutations[i] - '0'];
            if (distance == 0)
            {
                goto endwhile;
            }
            sum += distance;
        }

        if (sum < smallestDist)
        {
            for (int i = 0; i < NUM_VALS+1; i++)
            {
                cout << permutations[i] << ",";
            }

            cout << endl;
            smallestDist = sum;
        }
    endwhile:
        ;

    }

    cout << smallestDist << endl;

    //for (int i = 1; i < 8; i++)
    //{
    //    if (distances[1][i] > 0)
    //    {
    //        solution[1] = distances[1][i];
    //    }

    //    for (int j = 1; j < 8; j++)
    //    {
    //        if (j != i && distances[2][j] > 0)
    //        {
    //            solution[2] = distances[2][j];
    //        }
    //        for (int k = 1; k < 8; k++)
    //        {
    //            if (k != i && k != j && distances[3][j] > 0)
    //            {
    //                solution[3] = distances[3][k];
    //            }
    //            for (int l = 1; l < 8; l++)
    //            {
    //                if (l != i && l != j && l != k && distances[4][l] > 0)
    //                {
    //                    solution[4] = distances[4][l];
    //                }
    //                for (int m = 1; m < 8; m++)
    //                {
    //                    if (m != i && m != j && m != k && m != l && distances[5][m] > 0)
    //                    {
    //                        solution[5] = distances[5][m];
    //                    }
    //                    for (int n = 1; n < 8; n++)
    //                    {
    //                        if (n != i && n != j && n != k && n != l && n != m && distances[6][n] > 0)
    //                        {
    //                            solution[6] = distances[6][n];
    //                        }
    //                        for (int o = 1; o < 8; o++)
    //                        {
    //                            if (o != i && o != j && o != k && o != l && o != m && o != n && distances[7][o] > 0)
    //                            {
    //                                solution[7] = distances[7][o];
    //                            }
    //                        }
    //                    }
    //                }
    //            }
    //        }
    //    }
    //}

    return 0;
}