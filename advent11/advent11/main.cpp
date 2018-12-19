#include <iostream>
#include <string>
#include <unordered_map>

using namespace std;

static constexpr int NUM_ITEMS = 14;
static constexpr int MAX_FLOOR = 3;

unordered_map<string, int> memo;

int lowestRecursions = 10000;

#define PRINT_MOVES 0

string stringify(char* items)
{
    string str = "";
    for (int i = 0; i < NUM_ITEMS; i++)
    {
        str += std::to_string(items[i]) + "_";
    }
    return str;
}

bool validate(char* items)
{
    // check if chip will blow up
    for (int i = 1; i < NUM_ITEMS; i += 2)
    {
        // check if a chip (odd) will blow up
        if (items[i - 1] != items[i])
        {
            // if no parent generator
            for (int j = 0; j < NUM_ITEMS; j += 2)
            {
                if (items[j] == items[i] && // if there's another generator here
                    items[j] != items[j + 1]) // not powering it's chip
                {
                    return false;
                }
            }
        }
    }
    return true;
}

void processMove(char* items, char floor, int depth)
{
    // if we already were at this point at an earlier depth, return
    if (memo[stringify(items)] > 0 &&
        memo[stringify(items)] <= depth)
    {
        return;
    }

    // add state to memo
    memo[stringify(items)] = depth;

    //cout << depth << endl;

    bool done = true;
    // check if every item is on top
    for (int i = 0; i < NUM_ITEMS; i++)
    {
        if (items[i] != MAX_FLOOR)
        {
            done = false;
            break;
        }
    }

    if (true == done)
    {
        if (depth < lowestRecursions)
        {
            lowestRecursions = depth;
        }
        cout << "Max recursions: " << depth << endl;
        return;
    }

    // go up

    if (depth + 1 <= lowestRecursions)
    {
        for (int i = 0; i < NUM_ITEMS; i++)
        {
            for (int j = 0; j < NUM_ITEMS; j++)
            {
                // skip max floor
                if (items[i] == MAX_FLOOR || items[j] == MAX_FLOOR) continue;
                if (items[i] != floor || items[j] != floor) continue;
                if (i == j) continue;

                char* items2 = (char *)malloc(sizeof(char) * NUM_ITEMS);
                memcpy_s(items2, NUM_ITEMS, items, NUM_ITEMS);

              /*  if (i == j)
                {
                    items2[i]++;
                }
                else
                {*/
                    items2[i]++;
                    items2[j]++;
                //}

                if (validate(items2))
                {
                    if (depth == 0)
                    {
                        cout << "i is " << i << " j is " << j << endl;
                    }
#if PRINT_MOVES
                    cout << "depth: " << depth << "|" << (int)floor << "|" <<stringify(items2) << endl;
#endif
                    processMove(items2, floor + 1, depth + 1);
                }
                free(items2);
            }
        }
    }

    // go up 1
//    if (depth + 1 <= lowestRecursions)
//    {
//        for (int i = 0; i < NUM_ITEMS; i++)
//        {
//            if (items[i] == MAX_FLOOR) continue;
//            if (items[i] != floor) continue;
//
//            char* items2 = (char *)malloc(sizeof(char) * NUM_ITEMS);
//            memcpy_s(items2, NUM_ITEMS, items, NUM_ITEMS);
//
//            items2[i]++;
//
//            if (validate(items2))
//            {
//#if PRINT_MOVES
//                cout << "depth: " << depth << "|" << (int)floor << "|" << stringify(items2) << endl;
//#endif
//                processMove(items2, floor + 1, depth + 1);
//            }
//            free(items2);
//        }
//    }

    //go down (1 item only)
    if (floor > 0)
    {
        bool odd = false;
        bool even = false;
        for (int i = 0; i < NUM_ITEMS; i++)
        {
            if (items[i] != floor) continue;

            char* items2 = (char *)malloc(sizeof(char) * NUM_ITEMS);
            memcpy_s(items2, NUM_ITEMS, items, NUM_ITEMS);

            items2[i]--;

            if (memo[stringify(items2)] > 0 &&
                memo[stringify(items2)] <= depth)
            {
                continue;
            }

            if (validate(items2) &&
                ((i % 2 == 0 && even == false) ||
                (i % 2 == 1 && odd == false)))

            {
#if PRINT_MOVES
                cout << "depth: " << depth << "|" << (int)floor << "|" <<stringify(items2) << endl;
#endif
                if (i % 2 == 0) even = true;
                if (i % 2 == 1) odd = true;

                processMove(items2, floor - 1, depth + 1);
            }
            free(items2);
        }
    }
}

int main()
{
    //char items[NUM_ITEMS] = { 0,0,0,0,1,2,1,1,1,1 };
    //char items[NUM_ITEMS] = { 1, 0, 2, 0 };
    char items[NUM_ITEMS] = { 0,0,0,0,1,2,1,1,1,1,0,0,0,0 };
    processMove(items, 0, 0);
    return 0;
}