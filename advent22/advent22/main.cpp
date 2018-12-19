#include <iostream>
#include <string>
#include <regex>
#include <cassert>

using namespace std;

struct Node
{
    int x;
    int y;
    int size;
    int used;
    int avail;
    int percentUsed;
};
int main()
{
    string line;
    getline(cin, line);
    getline(cin, line);
    vector<Node> nodes;

    while (getline(cin, line))
    {
        regex re("^/dev/grid/node-x(\\d+)-y(\\d+)\\s*(\\d+)T\\s*(\\d+)T\\s*(\\d+)T\\s*(\\d+)%$");
        smatch match;

        regex_search(line, match, re);
        assert(match.size() > 0);

        nodes.push_back({ atoi(match[1].str().c_str()),
                          atoi(match[2].str().c_str()),
                          atoi(match[3].str().c_str()),
                          atoi(match[4].str().c_str()),
                          atoi(match[5].str().c_str()),
                          atoi(match[6].str().c_str()) });

    }
    int sum = 0;
    for (int i = 0; i < nodes.size(); i++)
    {
        for (int j = 0; j < nodes.size(); j++)
        {
            if (nodes[i].used > 0 &&
                j != i &&
                nodes[i].used < nodes[j].avail)
            {
                cout << nodes[j].percentUsed << "%,";
                sum++;
            }
        }
    }
    cout << sum << endl;
    return 0;
}