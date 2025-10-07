// family_kb.cpp
#include <bits/stdc++.h>
using namespace std;

struct KB
{
    unordered_map<string, vector<string>> childrenOf; // parent -> children
    unordered_map<string, string> fatherOf;           // child -> father
    unordered_map<string, string> motherOf;           // child -> mother

    void add_father(const string &dad, const string &child)
    {
        fatherOf[child] = dad;
        childrenOf[dad].push_back(child);
    }
    void add_mother(const string &mom, const string &child)
    {
        motherOf[child] = mom;
        childrenOf[mom].push_back(child);
    }

    bool is_parent(const string &p, const string &c) const
    {
        auto it = childrenOf.find(p);
        if (it == childrenOf.end())
            return false;
        return find(it->second.begin(), it->second.end(), c) != it->second.end();
    }

    vector<string> parents_of(const string &x) const
    {
        vector<string> ps;
        if (fatherOf.count(x))
            ps.push_back(fatherOf.at(x));
        if (motherOf.count(x))
            ps.push_back(motherOf.at(x));
        return ps;
    }

    vector<string> siblings_of(const string &x) const
    {
        vector<string> sibs;
        auto ps = parents_of(x);
        unordered_set<string> s;
        for (auto &p : ps)
        {
            auto it = childrenOf.find(p);
            if (it == childrenOf.end())
                continue;
            for (auto &c : it->second)
                if (c != x)
                    s.insert(c);
        }
        return vector<string>(s.begin(), s.end());
    }

    vector<string> grandparents_of(const string &x) const
    {
        vector<string> gps;
        for (auto &p : parents_of(x))
        {
            auto pps = parents_of(p);
            gps.insert(gps.end(), pps.begin(), pps.end());
        }
        sort(gps.begin(), gps.end());
        gps.erase(unique(gps.begin(), gps.end()), gps.end());
        return gps;
    }

    bool is_ancestor(const string &a, const string &x) const
    {
        // DFS up from x to roots
        unordered_set<string> vis;
        stack<string> st;
        st.push(x);
        while (!st.empty())
        {
            string cur = st.top();
            st.pop();
            if (vis.count(cur))
                continue;
            vis.insert(cur);
            for (auto &p : parents_of(cur))
            {
                if (p == a)
                    return true;
                st.push(p);
            }
        }
        return false;
    }

    vector<string> cousins_of(const string &x) const
    {
        // Children of aunts/uncles (siblings of parents)
        vector<string> cos;
        for (auto &p : parents_of(x))
        {
            for (auto &gp : parents_of(p))
            {
                // siblings of parent p = other children of grandparent gp (excluding p)
                auto it = childrenOf.find(gp);
                if (it == childrenOf.end())
                    continue;
                for (auto &aunt_uncle : it->second)
                    if (aunt_uncle != p)
                    {
                        // their children are cousins
                        auto it2 = childrenOf.find(aunt_uncle);
                        if (it2 == childrenOf.end())
                            continue;
                        for (auto &c : it2->second)
                            cos.push_back(c);
                    }
            }
        }
        sort(cos.begin(), cos.end());
        cos.erase(unique(cos.begin(), cos.end()), cos.end());
        return cos;
    }
};

int main()
{
    KB kb;
    // Facts
    kb.add_father("Robert", "Alice");
    kb.add_mother("Maria", "Alice");
    kb.add_father("Robert", "Ben");
    kb.add_mother("Maria", "Ben");

    kb.add_father("David", "Carol");
    kb.add_mother("Nina", "Carol");

    kb.add_father("Ben", "Eva");
    kb.add_mother("Sara", "Eva");

    kb.add_father("Ben", "Ian");
    kb.add_mother("Sara", "Ian");

    kb.add_father("Carol", "Mia");
    kb.add_mother("Oscar", "Mia");

    // Queries
    auto printVec = [](const string &label, const vector<string> &v)
    {
        cout << label << ": ";
        if (v.empty())
            cout << "(none)\n";
        else
        {
            for (auto &s : v)
                cout << s << " ";
            cout << "\n";
        }
    };

    cout << boolalpha;
    cout << "Is Robert parent of Alice? " << kb.is_parent("Robert", "Alice") << "\n";
    printVec("Siblings of Alice", kb.siblings_of("Alice"));
    printVec("Grandparents of Eva", kb.grandparents_of("Eva"));
    cout << "Is Robert ancestor of Ian? " << kb.is_ancestor("Robert", "Ian") << "\n";
    printVec("Cousins of Eva", kb.cousins_of("Eva"));
    printVec("Parents of Mia", kb.parents_of("Mia"));
    return 0;
}
