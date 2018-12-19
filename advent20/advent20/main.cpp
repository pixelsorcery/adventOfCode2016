#include <iostream>
#include <vector>
#include <algorithm>
#include <string>

using namespace std;

struct range
{
    long long  a;
    long long  b;
};
int main()
{
    long long a;
    long long b;
    char junk;
    string line;
    vector<range> ranges;
    char* cline;
    vector<bool> banned(UINT_MAX, 0);
    
    while (cin >> a)
    {
        cin >> junk;
        cin >> b;
        ranges.push_back(range{ a, b });
    }

    for (long long i = 0; i < ranges.size(); i++)
    {
        for (long long j = ranges[i].a; j <= ranges[i].b; j++)
        {
            banned[j] = 1;
        }
    }

    int result;
    unsigned int allowed = 0;
    for (unsigned int i = 0; i < UINT_MAX; i++)
    {
        if (banned[i] == 0)
        {
            //result = i;
            allowed++;
        }
    }

    cout << allowed << endl;
    return 0;
}