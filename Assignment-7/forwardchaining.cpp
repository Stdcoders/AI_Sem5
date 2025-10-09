#include <iostream>
#include <vector>
#include <string>
#include <map>
using namespace std;

struct Rule {
    vector<string> premises; // conditions
    string conclusion;       // result
};

bool allPremisesTrue(const vector<string>& premises, map<string, bool>& facts) {
    for (auto& p : premises) {
        if (facts[p] == false) return false;
    }
    return true;
}

int main() {
    
    vector<Rule> rules = {
        {{"A", "B"}, "C"},
        {{"C", "D"}, "E"},
        {{"E"}, "F"}
    };

    // Known facts
    map<string, bool> facts;
    facts["A"] = true;
    facts["B"] = true;
    facts["D"] = true;
    facts["C"] = false;
    facts["E"] = false;
    facts["F"] = false;

    cout << "Initial known facts: A, B, D" << endl;

    bool newFactAdded;
    do {
        newFactAdded = false;
        for (auto& rule : rules) {
            if (allPremisesTrue(rule.premises, facts) && facts[rule.conclusion] == false) {
                facts[rule.conclusion] = true;
                cout << "Derived new fact: " << rule.conclusion << endl;
                newFactAdded = true;
            }
        }
    } while (newFactAdded); // Repeat until no new facts can be inferred

    cout << "\nFinal facts:\n";
    for (auto& f : facts) {
        if (f.second)
            cout << f.first << " = TRUE" << endl;
    }

    return 0;
}
