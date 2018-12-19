#include <iostream>
#include <string>
#include <vector>
#include <regex>
#include <cassert>

using namespace std;

vector<string> lines;

inline bool isReg(char val)
{
    return val >= 'a' && val <= 'd';
}

int main()
{
    string line;
    string output;
    int inputVal = 0;
#if PART1
    int registers[4] = { 0,0,0,0 };
#endif
    int registers[4] = { 0,0,1,0 };
    while (getline(cin, line))
    {
        lines.push_back(line);
    }

    unsigned int ip = 0;
    regex re("^[a-z]+\\s([[a-d0-9]+)\\s([-a-d0-9]+)$");
    smatch match;
    int idx = 0;

    while (ip < lines.size())
    {
        // process lines
        switch (lines[ip].c_str()[0])
        {
        case 'c':
            regex_search(lines[ip], match, re);
            assert(match.size() > 0);
            if (isReg(lines[ip].c_str()[4]))
            {
                int dest = lines[ip].c_str()[6] - 'a';
                int src = lines[ip].c_str()[4] - 'a';
                registers[lines[ip].c_str()[6] - 'a'] = registers[lines[ip].c_str()[4] - 'a'];
            }
            else
            {
                int val = atoi(match[1].str().c_str());
                int reg = match[2].str().c_str()[0] - 'a';
                registers[reg] = val;
            }
            ip++;
            break;
        case 'i':
            idx = lines[ip].c_str()[4] - 'a';
            registers[idx]++;
            ip++;
            break;
        case 'd':
            idx = lines[ip].c_str()[4] - 'a';
            registers[idx]--;
            ip++;
            break;
        case 'j':
            regex_search(lines[ip], match, re);
            assert(match.size() > 0);
            if (isReg(match[1].str().c_str()[0]))
            {
                idx = match[1].str().c_str()[0] - 'a';
                if (registers[idx] > 0)
                {
                    int val = atoi(&match[2].str().c_str()[0]);
                    ip += val;
                }
                else
                {
                    ip++;
                }
            }
            else
            {
                int val = atoi(match[1].str().c_str());

                if (val > 0)
                {
                    int val = atoi(match[2].str().c_str());
                    ip += val;
                }
                else
                {
                    ip++;
                }
                
            }
            break;
        case 'o':
            output += to_string(registers[lines[ip].c_str()[4] - 'a']);

            if (output.size() == 6)
            {
                cout << output << endl;
                if (output == "010101")
                {
                    output.clear();
                    //notFound = false;
                    cout << "answer: " << inputVal << endl;
                    //goto endSearch;
                }
                else
                {
                    output.clear();
                    inputVal++;
                    registers[0] = inputVal;
                    ip = 0;
                    //goto endSearch;
                }
            }
            ip++;
            break;
        default:
            assert(0);
            break;
        }
    }

    cout << "register a is: " << registers[0] << endl;

    return 0;
} 