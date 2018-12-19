#include <iostream>
#include <string>
#include <vector>
#include <cassert>

using namespace std;

struct Bot
{
    Bot() 
        :
        isOutput(0),
        isInput(0),
        isBot(0),
        processed(0),
        val(-1),
        highParent(-1),
        lowParent(-1),
        highDest(-1),
        lowDest(-1),
        val1(-1),
        val2(-1),
        output1(-1),
        output2(-1)
    {};

    bool isOutput;
    bool isInput;
    bool isBot;
    bool processed;
    int val;
    int highParent;
    int lowParent;
    int highDest;
    int lowDest;
    int val1; // low
    int val2; // high i guess? eventually?
    int output1;
    int output2;
};

struct Value
{
    int dst;
    int val;
};

int output[200];

vector<Bot*> bots;
vector<Value> values;
vector<Value> outputs;

Bot* getBot(int val)
{
    for (auto itr = bots.begin(); itr != bots.end(); itr++)
    {
        if ((*itr)->val == val)
        {
            return *itr;
        }
    }

    // should this happen?
    assert(0);
    Bot* b = new Bot();
    b->val = val;
    return b;
}

void giveValue(int val, int dst)
{
    Bot* pBot = getBot(dst);
    if (pBot->val1 == -1)
    {
        pBot->val1 = val;
    }
    else
    {
        pBot->val2 = val;
    }
}

void propagateValues(int val, int currentBot)
{
    Bot* pBot = getBot(currentBot);
    if (pBot->processed == true)
    {
        return;
    }
    if (pBot->val1 == -1)
    {
        pBot->val1 = val;
    }
    else
    {
        pBot->val2 = val;
    }

    if (pBot->val1 != -1 && 
        pBot->val2 != -1)
    {
        pBot->processed = true;
        if (pBot->val1 > pBot->val2)
        {
            int temp = pBot->val1;
            pBot->val1 = pBot->val2;
            pBot->val2 = temp;
        }

        if (pBot->lowDest != -1)
        {
            propagateValues(pBot->val1, pBot->lowDest);
        }
        else if (pBot->output1 != -1)
        {
            output[pBot->output1] = pBot->val1;
        }

        if (pBot->highDest != -1)
        {
            propagateValues(pBot->val2, pBot->highDest);
        }

        else if (pBot->output2 != -1)
        {
            output[pBot->output2] = pBot->val2;
        }
    }
}

int main()
{
    string cmd;
    string junk;

    while (cin >> cmd)
    {
        if (cmd == "bot")
        {
            //bot 154 gives low to bot 145 and high to bot 179
            int botSrc;
            int lowDestBot = 0;
            int highDestBot = 0;
            bool isHighOutput = false;
            bool isLowOutput = false;
            cin >> botSrc;
            cin >> junk; cin >> junk; cin >> junk;
            string dest;
            cin >> dest;
            if (dest == "bot")
            {
                cin >> lowDestBot;
            }
            else
            {
                cin >> lowDestBot;
                isLowOutput = true;
            }

            cin >> junk;  cin >> junk; assert(junk == "high");  cin >> junk;

            cin >> dest;

            if (dest == "bot")
            {
                cin >> highDestBot;
            }
            else
            {
                cin >> highDestBot;
                isHighOutput = true;
            }

            // find the bot
            Bot* bSrc = nullptr;
            Bot* bDstLow = nullptr;
            Bot* bDstHigh = nullptr;

            for (auto itr = bots.begin(); itr != bots.end(); itr++)
            {
                if ((*itr)->val == botSrc)
                {
                    bSrc = *itr;
                    break;
                }
            }

            if (bSrc == nullptr)
            {
                bSrc = new Bot();
                bots.push_back(bSrc);
            }

            bSrc->val = botSrc;

            if (isHighOutput != true)
            {
                bSrc->highDest = highDestBot;
            }
            else
            {
                bSrc->output2 = highDestBot;
            }

            if (isLowOutput != true)
            {
                bSrc->lowDest = lowDestBot;
            }
            else
            {
                bSrc->output1 = lowDestBot;
            }


            if (isLowOutput != true)
            {
                for (auto itr = bots.begin(); itr != bots.end(); itr++)
                {
                    if ((*itr)->val == lowDestBot)
                    {
                        bDstLow = *itr;
                        break;
                    }
                }

                if (bDstLow == nullptr)
                {
                    bDstLow = new Bot();
                    bots.push_back(bDstLow);
                    bDstLow->val = lowDestBot;
                }

                bDstLow->lowParent = bSrc->val;
            }

            if (isHighOutput != true)
            {
                for (auto itr = bots.begin(); itr != bots.end(); itr++)
                {
                    if ((*itr)->val == highDestBot)
                    {
                        bDstHigh = *itr;
                        break;
                    }
                }

                if (bDstHigh == nullptr)
                {
                    bDstHigh = new Bot();
                    bots.push_back(bDstHigh);
                    bDstHigh->val = highDestBot;
                }

                bDstHigh->highParent = bSrc->val;
            }
        }
        else
        {
            assert(cmd == "value");
            int value = 0;
            int botNum;
            cin >> value;
            cin >> junk; // goes
            cin >> junk; // to 
            cin >> junk; // bot
            cin >> botNum;

            Value val;
            val.dst = botNum;
            val.val = value;

            values.push_back(val);
        }
    }

    // give values to bots
    for (size_t i = 0; i < values.size(); i++)
    {
        Bot* pBot = getBot(values[i].dst);

        if (pBot->val1 == -1)
        {
            pBot->val1 = values[i].val;
        }
        else
        {
            assert(pBot->val2 == -1);
            pBot->val2 = values[i].val;
        }
    }

    for (size_t i = 0; i < bots.size(); i++)
    {
        //cout << "bot: " << bots[i]->val << " val1: " << bots[i]->val1 << " val2: " << bots[i]->val2 << endl;
        if (bots[i]->val1 != -1 && bots[i]->val2 != -1 && bots[i]->processed == false)
        {
            bots[i]->processed = true;
            cout << bots[i]->val << endl;
            
            if (bots[i]->val1 > bots[i]->val2)
            {
                int temp = bots[i]->val1;
                bots[i]->val1 = bots[i]->val2;
                bots[i]->val2 = temp;
            }

            if (bots[i]->lowDest != -1)
            {
                propagateValues(bots[i]->val1, bots[i]->lowDest);
            }

            if (bots[i]->highDest != -1)
            {
                propagateValues(bots[i]->val2, bots[i]->highDest);
            }
        }
    }

    for (size_t i = 0; i < bots.size(); i++)
    {
        cout << "bot: " << bots[i]->val << " val1: " << bots[i]->val1 << " val2: " << bots[i]->val2 << endl;
        if (bots[i]->val1 == 17 && bots[i]->val2 == 61)
        {
            cout << "answer bot is: " << bots[i]->val << endl;
            break;
        }
        if (bots[i]->val1 != -1 && bots[i]->val2 != -1 && bots[i]->processed == false)
        {
            bots[i]->processed = true;
            cout << bots[i]->val << endl;
        }
    }

    cout << "output: ";

    for (int i = 0; i < 3; i++)
    {
        cout << output[i] << ", ";
    }

    return 0;
}
