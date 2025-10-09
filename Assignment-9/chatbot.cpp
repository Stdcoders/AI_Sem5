#include <iostream>
#include <string>
#include <vector>
#include <map>
#include <algorithm>
using namespace std;

struct Rule
{
    vector<string> conditions;
    string conclusion;
};

string toLower(string s)
{
    transform(s.begin(), s.end(), s.begin(), ::tolower);
    return s;
}

bool allTrue(vector<string> cond, map<string, bool> &facts)
{
    for (auto &c : cond)
        if (!facts[c])
            return false;
    return true;
}

string forwardChain(vector<Rule> &rules, map<string, bool> &facts)
{
    bool newFactAdded;
    string lastConclusion = "";

    do
    {
        newFactAdded = false;
        for (auto &rule : rules)
        {
            if (allTrue(rule.conditions, facts) && !facts[rule.conclusion])
            {
                facts[rule.conclusion] = true;
                lastConclusion = rule.conclusion;
                newFactAdded = true;
            }
        }
    } while (newFactAdded);

    return lastConclusion;
}

int main()
{
    cout << "=========================================\n";
    cout << "🤖  AI-Powered Health Chatbot\n";
    cout << "=========================================\n";
    cout << "This bot can help identify possible health advice.\n";
    cout << "Type symptoms like: fever, cough, tired, sore throat.\n";
    cout << "Type 'bye' to exit.\n\n";

    vector<Rule> rules = {
        {{"fever", "cough"}, "flu"},
        {{"tired", "fever"}, "infection"},
        {{"sore throat", "cough"}, "cold"},
        {{"flu"}, "rest"},
        {{"infection"}, "doctor"},
        {{"cold"}, "hydration"}};

    map<string, bool> facts;

    while (true)
    {
        cout << "\nYou: ";
        string input;
        getline(cin, input);
        input = toLower(input);

        if (input == "bye" || input == "exit")
        {
            cout << "Chatbot: Take care! Stay healthy 😊\n";
            break;
        }

        facts[input] = true;

        string result = forwardChain(rules, facts);

        if (result == "flu")
            cout << "Chatbot: It seems like you might have flu. Take some rest and stay hydrated.\n";
        else if (result == "infection")
            cout << "Chatbot: You might have an infection. It's better to consult a doctor.\n";
        else if (result == "cold")
            cout << "Chatbot: Sounds like a common cold. Drink warm fluids and rest.\n";
        else if (result == "doctor")
            cout << "Chatbot: I recommend you to visit a doctor soon.\n";
        else if (result == "rest")
            cout << "Chatbot: You should take adequate rest.\n";
        else if (result == "hydration")
            cout << "Chatbot: Keep yourself hydrated. It helps in faster recovery.\n";
        else
            cout << "Chatbot: Okay, noted your symptom. Please tell me more.\n";
    }

    return 0;
}
