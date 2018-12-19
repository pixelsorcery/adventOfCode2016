#include <iostream>
#include <vector>
#include <iterator>

using namespace std;

//#define NUM_ELVES 3012210
//#define NUM_ELVES 3012210
int main()
{

    //int NUM_ELVES = 3012210;
    int NUM_ELVES = 1;
    int input = NUM_ELVES;

#if PART1
    vector<bool> elves(NUM_ELVES, 1);
#else

    //vector<int> elves(NUM_ELVES, 1);

    for (int k = 0; k < 300; k++)
    {
        NUM_ELVES++;
        vector<int> elves(NUM_ELVES, 1);
        for (int i = 0; i < NUM_ELVES; i++)
        {
            elves[i] = i + 1;
        }
#endif

        bool looped = false;
        int idx = 0;
        while (!looped)
        {
#if PART1
            while (elves[idx] == false) idx = (idx + 1) % NUM_ELVES;
            int next = (idx + 1) % NUM_ELVES;
            while (elves[next] == false) next = (next + 1) % NUM_ELVES;

            if (next == idx)
            {
                looped = true;
                break;
            }
            else
            {
                elves[next] = false;
            }
            idx = next;
#else
            //while (elves[idx] == false) idx = (idx + 1) % NUM_ELVES;
            //int next = (idx + elves.size()/2) % NUM_ELVES;
            //while (elves[next] == false) next = (next + 1) % NUM_ELVES;

            //cout << elves[idx] << " steals from " << elves[next] << endl;

            //if (next == idx)
            //{
            //    looped = true;
            //    break;
            //}
            //else
            //{
            //    elves[next] = false;
            //}
            //idx = next;

            int next = (idx + (elves.size() / 2)) % elves.size();

            //cout << elves[idx] << " steals from " << elves[next] << endl;

            auto it = elves.begin() + next;
            elves.erase(it);

            if (elves.size() == 1)
            {
                looped = true;
                break;
            }
            if (next < idx && idx != elves.size())
            {
                ; // do nothing
            }
            else if (idx == elves.size())
            {
                idx = 0;
            }
            else
            {
                idx = idx + 1;
            }
#endif
        }
        cout << "input: " << NUM_ELVES << " index: " << elves[0] << endl;
    }

    //int i =    1594323;
    //int j = 0;
    //while (i < 3012210)
    //{
    //    if (j <= 1594323)
    //    {
    //        i ++;
    //        j+=2;
    //    }
    //    else
    //    {
    //        i++;
    //        j++;
    //    }
    //    //cout << "input: " << i << " index: " << j << endl;
    //}
    //cout << "input: " << i << " index: " << j << endl;
    //cout << i;
    return 0;
    // not 31682
    // not 917209
    // not 2215049
}