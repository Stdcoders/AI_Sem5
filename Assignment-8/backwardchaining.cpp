#include <iostream>
#include <vector>
#include <string>
#include <map>
using namespace std;

struct Rule
{
    vector<string> premises; 
    string conclusion;       
};

bool backwardChaining(string goal, vector<Rule> &rules, map<string, bool> &facts)
{
    if (facts[goal])
    {
        return true;
    }

    for (auto &rule : rules)
    {
        if (rule.conclusion == goal)
        {
            bool allTrue = true;

            for (auto &premise : rule.premises)
            {
                if (!backwardChaining(premise, rules, facts))
                {
                    allTrue = false;
                    break;
                }
            }

            if (allTrue)
            {
                facts[goal] = true;
                cout << "Inferred: " << goal << " (using rule: ";
                for (auto &p : rule.premises)
                    cout << p << " ";
                cout << "-> " << goal << ")" << endl;
                return true;
            }
        }
    }
    return false;
}

int main()
{
    vector<Rule> rules = {
        {{"A", "B"}, "C"},
        {{"C", "D"}, "E"},
        {{"E"}, "F"}};

    map<string, bool> facts;
    facts["A"] = true;
    facts["B"] = true;
    facts["D"] = true;
    facts["C"] = false;
    facts["E"] = false;
    facts["F"] = false;

    string goal = "F"; 
    cout << "Goal: " << goal << endl;

    if (backwardChaining(goal, rules, facts))
    {
        cout << "\n✅ Goal " << goal << " can be proved!\n";
    }
    else
    {
        cout << "\n❌ Goal " << goal << " cannot be proved.\n";
    }

    cout << "\nFinal facts:\n";
    for (auto &f : facts)
    {
        if (f.second)
            cout << f.first << " = TRUE" << endl;
    }

    return 0;
}
