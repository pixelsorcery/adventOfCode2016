#include <iostream>
#include <vector>
#include <string>
#include <unordered_map>
#include <cassert>
#include <algorithm>
#include <fstream>

using namespace std;

typedef unsigned long long uint64;
typedef long long int64;
typedef unsigned int unit;

int main()
{
    string in;
    string input = "abcdefgh";

    ifstream inFile;
    inFile.open("input.txt");
    string original;

    string output = "fbgdceah";

    while (input != output)
    {
        std::next_permutation(input.begin(), input.end());
        original = input;
        while (inFile >> in)
        {
            if (in == "through")
            {
                int a = 4;
            }
            if (in == "rotate")
            {
                inFile >> in;
                if (in == "based")
                {   // based on position of letter e
                    inFile >> in;
                    inFile >> in;
                    inFile >> in;
                    inFile >> in;
                    inFile >> in;
                    size_t idx1 = input.find(in);
                    //Once the index is determined, rotate the string to the right one time
                    //plus a number of times equal to that index,
                    string s = "";
                    int rotateAmount = 1;
                    rotateAmount += idx1;
                    //plus one additional time if the index was at least 4.
                    rotateAmount += idx1 >= 4 ? 1 : 0;
                    for (int i = 0; i < input.size(); i++)
                    {
                        s += input.at(((input.size() + input.size() - rotateAmount) + i) % input.size());
                    }
                    input = s;
                    //size_t idx2 = input.find(in);
                    //rotateAmount = idx2;
                    //rotateAmount += idx1 >= 4 ? 1 : 0;
                    //s = "";

                    //for (int i = 0; i < input.size(); i++)
                    //{
                    //    s += input.at(((input.size() - rotateAmount) + i) % input.size());
                    //}
                    //input = s;
                }
                else if (in == "left")
                {
                    //rotate left 7 steps
                    int steps;
                    inFile >> steps;
                    inFile >> in;
                    string s = "";
                    int rotateAmt = steps;
                    for (int i = 0; i < input.size(); i++)
                    {
                        s += input.at((rotateAmt + rotateAmt + i - steps) % input.size());
                    }
                    input = s;
                }
                else if (in == "right")
                {
                    //rotate right 7 steps
                    int steps;
                    inFile >> steps;
                    inFile >> in;
                    string s = "";
                    int rotateAmt = steps;
                    for (int i = 0; i < input.size(); i++)
                    {
                        s += input.at(((input.size() - rotateAmt) + i) % input.size());
                    }
                    input = s;
                }
            }
            else if (in == "swap")
            {
                // swap letter h with letter f
                inFile >> in;
                if (in == "letter")
                {
                    string a;
                    inFile >> a;
                    inFile >> in;
                    inFile >> in;
                    string b;
                    inFile >> b;
                    int aidx = input.find(a);
                    int bidx = input.find(b);
                    swap(input[aidx], input[bidx]);
                }
                //swap position 6 with position 4
                else
                {
                    int a;
                    inFile >> a;
                    inFile >> in;
                    inFile >> in;
                    int b;
                    inFile >> b;
                    int aidx = input.find(a);
                    int bidx = input.find(b);
                    swap(input[a], input[b]);
                }
            }
            else if (in == "reverse")
            {
                //reverse positions 0 through 7
                int a;
                int b;
                inFile >> in;
                inFile >> a;
                inFile >> in;
                inFile >> b;
                string tmp = input.substr(a, (b + 1) - a);
                reverse(tmp.begin(), tmp.end());
                string result = "";
                for (int i = 0; i < a; i++)
                {
                    result += input.at(i);
                }
                result += tmp;

                for (int i = b + 1; i < input.size(); i++)
                {
                    result += input.at(i);
                }

                input = result;
            }
            else if (in == "move")
            {
                // move position X to position Y means that the letter 
                // which is at index X should be removed from the string, 
                // then inserted such that it ends up at index Y.
                //move position 1 to position 5
                inFile >> in;
                int p1, p2;
                inFile >> p1;
                inFile >> in;
                inFile >> in;
                inFile >> p2;
                string str = "";
                str += input.at(p1);
                input.erase(input.begin() + p1);
                input.insert(p2, str);
            }
            else
            {
                assert(0);
            }
        }
        inFile.clear();
        inFile.seekg(0, ios::beg);
    }
    inFile.close();
    cout << input << endl;
    cout << original << endl;
    return 0;
}