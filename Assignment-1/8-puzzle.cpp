#include <iostream>
#include <vector>
#include <queue>
#include <set>
using namespace std;
#define N 3

struct PuzzleState
{
    vector<vector<int>> board;
    int x, y;
    int depth;
    PuzzleState(vector<vector<int>> b, int i, int j, int d) : board(b), x(i), y(j), depth(d) {}
};

int row[] = {0, 0, -1, 1};
int col[] = {-1, 1, 0, 0};


bool isGoalState(vector<vector<int>> &board)
{
    vector<vector<int>> goal = {{1, 2, 3}, {4, 5, 6}, {7, 8, 0}};
    return board == goal;
}
bool isValid(int x, int y)
{
    return (x >= 0 && x < N && y >= 0 && y < N);
}
void printBoard(vector<vector<int>> &board)
{
    for (auto &row : board)
    {
        for (auto &num : row)
            cout << num << " ";
        cout << endl;
    }
    cout << "--------" << endl;
}
void solvePuzzleBFS(vector<vector<int>> &start, int x, int y)
{
    queue<PuzzleState> q;
    set<vector<vector<int>>> visited;

    q.push(PuzzleState(start, x, y, 0));
    visited.insert(start);
    while (!q.empty())
    {
        PuzzleState curr = q.front();
        q.pop();

        cout << "Depth: " << curr.depth << endl;
        printBoard(curr.board);

        if (isGoalState(curr.board))
        {
            cout << "Goal state reached at depth " << curr.depth << endl;
            return;
        }
        for (int i = 0; i < 4; i++)
        {
            int newX = curr.x + row[i];
            int newY = curr.y + col[i];

            if (isValid(newX, newY))
            {
                vector<vector<int>> newBoard = curr.board;
                swap(newBoard[curr.x][curr.y], newBoard[newX][newY]);

                if (visited.find(newBoard) == visited.end())
                {
                    visited.insert(newBoard);
                    q.push(PuzzleState(newBoard, newX, newY, curr.depth + 1));
                }
            }
        }
    }

    cout << "No solution found (BFS Brute Force reached depth limit)" << endl;
}

int main()
{
    vector<vector<int>> start = {{1, 2, 3}, {4, 0, 5}, {6, 7, 8}}; 
    int x = 1, y = 1;

    cout << "Initial State: " << endl;
    printBoard(start);

    solvePuzzleBFS(start, x, y);

    return 0;
}
