#include <bits/stdc++.h>
using namespace std;

struct Node
{
    int r, c;
    int g;
    int h;
    int f;
    int pr, pc;
};
struct Cmp
{
    bool operator()(const Node &a, const Node &b) const { return a.f > b.f; }
};

int manhattan(int r1, int c1, int r2, int c2) { return abs(r1 - r2) + abs(c1 - c2); }

int main()
{
    vector<vector<int>> grid = {
        {0, 0, 0, 0, 0, 1, 0},
        {1, 1, 0, 1, 0, 1, 0},
        {0, 0, 0, 1, 0, 0, 0},
        {0, 1, 0, 0, 0, 1, 0},
        {0, 1, 0, 1, 0, 0, 0}};
    int R = grid.size(), C = grid[0].size();
    pair<int, int> start = {0, 0};
    pair<int, int> goal = {4, 6};

    vector<vector<int>> bestG(R, vector<int>(C, INT_MAX));
    vector<vector<pair<int, int>>> parent(R, vector<pair<int, int>>(C, {-1, -1}));

    priority_queue<Node, vector<Node>, Cmp> pq;
    Node s{start.first, start.second, 0, manhattan(start.first, start.second, goal.first, goal.second), 0, -1, -1};
    s.f = s.g + s.h;
    pq.push(s);
    bestG[s.r][s.c] = 0;

    int dr[4] = {-1, 1, 0, 0}, dc[4] = {0, 0, -1, 1};
    bool found = false;

    while (!pq.empty())
    {
        Node cur = pq.top();
        pq.pop();
        if (cur.r == goal.first && cur.c == goal.second)
        {
            found = true;
            break;
        }
        for (int k = 0; k < 4; k++)
        {
            int nr = cur.r + dr[k], nc = cur.c + dc[k];
            if (nr < 0 || nr >= R || nc < 0 || nc >= C || grid[nr][nc] == 1)
                continue;
            int ng = cur.g + 1;
            if (ng < bestG[nr][nc])
            {
                bestG[nr][nc] = ng;
                parent[nr][nc] = {cur.r, cur.c};
                int h = manhattan(nr, nc, goal.first, goal.second);
                pq.push(Node{nr, nc, ng, h, ng + h, cur.r, cur.c});
            }
        }
    }

    if (!found)
    {
        cout << "No path.\n";
        return 0;
    }

    vector<pair<int, int>> path;
    for (auto p = goal; p.first != -1; p = parent[p.first][p.second])
        path.push_back(p);
    reverse(path.begin(), path.end());

    cout << "Path length: " << (int)path.size() - 1 << "\nPath:\n";
    for (auto [r, c] : path)
        cout << "(" << r << "," << c << ") ";
    cout << "\n";

    vector<string> vis(R, string(C, '.'));
    for (int r = 0; r < R; r++)
        for (int c = 0; c < C; c++)
            if (grid[r][c] == 1)
                vis[r][c] = '#';
    for (auto [r, c] : path)
        vis[r][c] = '*';
    vis[start.first][start.second] = 'S';
    vis[goal.first][goal.second] = 'G';
    cout << "\nGrid:\n";
    for (auto &row : vis)
        cout << row << "\n";
    return 0;
}
