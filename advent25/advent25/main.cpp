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
#define PART1 0
int main()
{
    string line;
    int offset;

    string output = "";

#if PART1
    int registers[4] = { 7,0,0,0 };
#else
    int registers[4] = { 0,0,0,0 };
#endif
    while (getline(cin, line))
    {
        lines.push_back(line);
    }

    unsigned int ip = 0;
    regex re("^[a-z]+\\s([-a-d0-9]+)\\s([-a-d0-9]+)$");
    smatch match;
    int idx = 0;
    bool notFound = true;
    int inputVal = 0;
    while (notFound)
    {
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
                else if (isReg(match[2].str().c_str()[0]))
                {
                    int val = atoi(match[1].str().c_str());
                    int reg = match[2].str().c_str()[0] - 'a';
                    registers[reg] = val;
                }
                ip++;
                break;
            case 'n':
                ip++;
                break;
            case 'a':
                registers[lines[ip].c_str()[4] - 'a'] += registers[lines[ip].c_str()[6] - 'a'];
                registers[lines[ip].c_str()[6] - 'a'] = 0;
                ip++;
                break;
            case 'm':
                registers[lines[ip].c_str()[4] - 'a'] += registers[lines[ip].c_str()[6] - 'a'];
                registers[lines[ip].c_str()[4] - 'a'] *= registers[lines[ip].c_str()[8] - 'a'];
                registers[lines[ip].c_str()[6] - 'a'] = 0;
                registers[lines[ip].c_str()[8] - 'a'] = 0;
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
                    if (registers[idx] != 0)
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

                    if (val != 0)
                    {
                        int val = 0;
                        if (isReg(match[2].str().c_str()[0]))
                        {
                            val = registers[lines[ip].c_str()[6] - 'a'];
                        }
                        else
                        {
                            val = atoi(match[2].str().c_str());
                        }
                        ip += val;
                    }
                    else
                    {
                        ip++;
                    }

                }
                break;
            case 't':
                if (isReg(lines[ip].c_str()[4]))
                {
                    offset = registers[lines[ip].c_str()[4] - 'a'];
                }
                else
                {
                    offset = atoi(match[1].str().c_str());
                }

                if (ip + offset > lines.size())
                {
                    ip++;
                    break;
                }
                if (lines[ip + offset].c_str()[0] == 'i')
                {
                    lines[ip + offset].replace(0, 3, "dec");
                }
                else if (lines[ip + offset].c_str()[0] == 'd')
                {
                    lines[ip + offset].replace(0, 3, "inc");
                }
                else if (lines[ip + offset].c_str()[0] == 'c')
                {
                    lines[ip + offset].replace(0, 3, "jnz");
                }
                else if (lines[ip + offset].c_str()[0] == 'j')
                {
                    lines[ip + offset].replace(0, 3, "cpy");
                }
                else if (lines[ip + offset].c_str()[0] == 't')
                {
                    lines[ip + offset].replace(0, 3, "inc");
                }
                ip++;
                break;
            case 'o':
                output += to_string(registers[lines[ip].c_str()[4] - 'a']);

                if (output.size() == 10)
                {
                    cout << output << endl;
                    if (output == "0101010101")
                    {
                        output.clear();
                        notFound = false;
                        cout << "answer: " << inputVal << endl;
                        goto endSearch;
                    }
                    else
                    {
                        output.clear();
                        goto endSearch;
                    }
                }
                ip++;
                break;
            default:
                assert(0);
                break;
            }
        }

endSearch:
        inputVal++;
        registers[0] = inputVal;
        ip = 0;
        ;
    }

    //cout << "register a is: " << registers[0] << endl;

    return 0;
}