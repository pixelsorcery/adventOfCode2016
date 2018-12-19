#include <iostream>
#include <string>
#include <queue>

using namespace std;

static constexpr int favNum = 1350;
//static constexpr int favNum = 10;

int numBits(int input)
{
    int bits = 0;
    while (input > 0)
    {
        if (input & 1)
        {
            bits++;
        }

        input = input >> 1;
    }

    return bits;
}

struct Point
{
    int x;
    int y;
};

struct Node
{
    Point p;
    int d;
};

bool isValid(char* maze, int x, int y)
{
    bool valid = true;

    if (x < 0 || 
        y < 0 ||
        x > favNum || 
        y > favNum)
    {
        valid = false;
    }
    else if (maze[y * favNum + x] == 1)
    {
        valid = false;
    }
    else if (maze[y * favNum + x] == 2)
    {
        valid = false;
    }
    else
    {
        valid = true;
    }

    return valid;
}

int bfs(char* maze, int x, int y)
{
    queue<Node> q;
    int depth = 0; 

    Node in{{x, y}, 0 };
    q.push(in);

    int popped = 0;

    while (q.size() > 0)
    {
        Node front = q.front();
#if PART1
        if (front.p.x == 31 &&
            front.p.y == 39)
        {
            return front.d;
        }
#else
        if (front.d >= 50)
        {
            break;
        }
#endif
        else
        {
            x = front.p.x;
            y = front.p.y;
            depth = front.d;
            q.pop();
            popped++;
        }

        if (isValid(maze, x+1, y))
        {
            q.push(Node{ { x + 1, y }, depth + 1 });
            maze[y * favNum + x + 1] = 2;
        }
        if (isValid(maze, x, y+1))
        {
            q.push(Node{ { x, y + 1 }, depth + 1 });
            maze[(y+1) * favNum + x] = 2;
        }
        if (isValid(maze, x-1, y))
        {
            q.push(Node{ { x - 1, y }, depth + 1 });
            maze[y * favNum + x - 1] = 2;
        }
        if (isValid(maze, x, y-1))
        {
            q.push(Node{ { x, y - 1 }, depth + 1 });
            maze[(y-1) * favNum + x] = 2;
        }
    }

#if PART1
    return depth;
#else
    return popped;
#endif
}

int main()
{
    char* maze = new char[favNum * favNum];

    // generate maze, 1 is wall, 0 is empty
    for (int y = 0; y < favNum; y++)
    {
        for (int x = 0; x < favNum; x++)
        {
            int value = x*x + 3 * x + 2 * x*y + y + y*y;
            value += favNum;
            maze[(y * favNum) + x] = numBits(value) % 2;
        }
    }
    // find path
    const int depth = bfs(maze, 1, 1);
    cout << "depth is: " << depth << endl;

    return 0;
}