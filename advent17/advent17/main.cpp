#include <iostream>
#include <queue>
#include "md5.h"

using namespace std;

struct Point
{
    int x;
    int y;
};

struct Node
{
    Point p;
    int d;
    string path;
};

bool isValid(int x, int y)
{
    if (x < 0 ||
        y < 0 ||
        x > 3 ||
        y > 3)
    {
        return false;
    }

    return true;
}

int main()
{
    const std::string chrs("0123456789abcdef");
    //string input = "ioramepc";
    string input = "ioramepc";
    queue<Node> q;
    Node start{ {0, 0}, 0, ""};
    q.push(start);

    while (q.size() > 0)
    {
        Node n = q.front();
        q.pop();
        
        if (n.p.x == 3 && n.p.y == 3)
        {
            cout << "distance: " << n.d << endl;
            cout << "path: " << n.path.c_str() << endl;
            cout << "path length: " << n.path.size() << endl;
            continue;
        }

        string hash = md5(input + n.path);
        // u d l r
        // enqueue available paths
        if (chrs.find(hash.at(0)) > 0xa)
        {
            int x = n.p.x;
            int y = n.p.y;
            y = y - 1;
            if (isValid(x, y))
            {
                string path = n.path + "U";
                q.push(Node{ {x, y}, n.d + 1, path });
            }
        }
        if (chrs.find(hash.at(1)) > 0xa)
        {
            int x = n.p.x;
            int y = n.p.y;
            y = y + 1;
            if (isValid(x, y))
            {
                string path = n.path + "D";
                q.push(Node{ { x, y}, n.d + 1, path });
            }
        }
        if (chrs.find(hash.at(2)) > 0xa)
        {
            int x = n.p.x;
            int y = n.p.y;
            x = x - 1;
            if (isValid(x, y))
            {
                string path = n.path + "L";
                q.push(Node{ { x, y }, n.d + 1, path });
            }
        }
        if (chrs.find(hash.at(3)) > 0xa)
        {
            int x = n.p.x;
            int y = n.p.y;
            x = x + 1;
            if (isValid(x, y))
            {
                string path = n.path + "R";
                q.push(Node{ { x, y }, n.d + 1, path });
            }
        }
    }

    return 0;
}