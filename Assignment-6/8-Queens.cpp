// eight_queens.cpp
#include <bits/stdc++.h>
using namespace std;

int N = 8;
vector<int> col(8, -1);                            
bool usedCol[8] = {0}, d1[16] = {0}, d2[16] = {0}; 
vector<vector<string>> solutions;

void place(int r)
{
    if (r == N)
    {
        vector<string> board(N, string(N, '.'));
        for (int i = 0; i < N; i++)
            board[i][col[i]] = 'Q';
        solutions.push_back(board);
        return;
    }
    for (int c = 0; c < N; c++)
    {
        int id1 = r - c + 7, id2 = r + c;
        if (usedCol[c] || d1[id1] || d2[id2])
            continue;
        usedCol[c] = d1[id1] = d2[id2] = true;
        col[r] = c;
        place(r + 1);
        usedCol[c] = d1[id1] = d2[id2] = false;
        col[r] = -1;
    }
}

int main()
{
    place(0);
    cout << "Total solutions: " << solutions.size() << "\n\n";
    if (!solutions.empty())
    {
        cout << "One solution:\n";
        for (auto &row : solutions[0])
            cout << row << "\n";
    }
    return 0;
}
