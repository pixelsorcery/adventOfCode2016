#include <iostream>
#include <string>
#include <cassert>
#include <vector>

using namespace std;

int main()
{
    string in;
    int numTLS = 0;

    while (getline(cin, in))
    {
        const char *ptr = in.c_str();

        bool seq = false;
        bool hyperSeq = false;
        bool insideHyper = false;
        vector<string> supernet;
        vector<string> hypernet;

        supernet.clear();
        hypernet.clear();

#if PART1
        for (unsigned int i = 0; i < in.length() - 3; i++)
        {
            if (ptr[i] == '[')
            {
                insideHyper = true;
                i++;
            }

            if (ptr[i] == ']')
            {
                insideHyper = false;
                i++;
            }

            if (ptr[i]   == ptr[i+3] &&
                ptr[i+1] == ptr[i+2] &&
                ptr[i]   != ptr[i+1])
            {
                if (insideHyper == true)
                {
                    hyperSeq = true;
                }
                else
                {
                    seq = true;
                }
            }
        }

        if (seq == true && hyperSeq == false)
        {
            numTLS++;
        }
    }
#else
        for (unsigned int i = 0; i < in.length() - 2; i++)
        {
            if (ptr[i] == '[')
            {
                insideHyper = true;
                i++;
            }

            if (ptr[i] == ']')
            {
                insideHyper = false;
                i++;
            }

            if (ptr[i] == ptr[i+2] &&
                ptr[i] != ptr[i+1])
            {
                if (insideHyper)
                {
                    // add string to hyper
                    hypernet.push_back(in.substr(i, i + 2));
                }
                else
                {
                    // add string to super
                    supernet.push_back(in.substr(i, i + 2));
                }
            }
        }
#if PART1
        if (seq == true && hyperSeq == false)
        {
            numTLS++;
        }
#else
        for (unsigned int i = 0; i < supernet.size(); i++)
        {
            for (unsigned int j = 0; j < hypernet.size(); j++)
            {
                if (supernet[i].c_str()[0] == hypernet[j].c_str()[1] &&
                    supernet[i].c_str()[1] == hypernet[j].c_str()[0])
                {
                    numTLS++;
                    goto endLoops;
                }
            }
        }
    endLoops:;
#endif
    }
#endif

    cout << "num sequences: " << numTLS << endl;

    return 0;
}