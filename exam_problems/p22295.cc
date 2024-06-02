#include <iostream>
#include <vector>
using namespace std;

vector<vector<char>> board;
vector<vector<bool>> visited;
vector<char> result;
int n, m;

void tortoise(int x1, int y1, const int x2, const int y2)
{
    if (x1 == x2 and y1 == y2)
    {
        for (int i = 0; i < result.size(); ++i) cout << result[i];
        cout << board[x2][y2];
        cout << endl;
    }
    else
    {
        if (x1 + 1 < n and not visited[x1 + 1][y1]) //down
        {
            //cout << x1 << " " << y1 << endl;
            //cout << "down" << endl;
            visited[x1][y1] = true;
            result.push_back(board[x1][y1]);
            tortoise(x1+1, y1, x2, y2);
            result.pop_back();
            visited[x1][y1] = false;
        }
        if (x1 - 1 >= 0 and not visited[x1-1][y1]) //up
        {
            //cout << x1 << " " << y1 << endl;
            //cout << "up" << endl;
            visited[x1][y1] = true;
            result.push_back(board[x1][y1]);
            tortoise(x1-1, y1, x2, y2);
            result.pop_back();
            visited[x1][y1] = false;
        }
        if (y1 - 1 >= 0 and not visited[x1][y1-1]) //left
        {
            //cout << x1 << " " << y1 << endl;
            //cout << "left" << endl;
            visited[x1][y1] = true;
            result.push_back(board[x1][y1]);
            tortoise(x1, y1-1, x2, y2);
            result.pop_back();
            visited[x1][y1] = false;
        }
        if (y1 + 1 < m and not visited[x1][y1+1]) //right
        {
            //cout << x1 << " " << y1 << endl;
            //cout << "rigth" << endl;
            visited[x1][y1] = true;
            result.push_back(board[x1][y1]);
            tortoise(x1, y1+1, x2, y2);
            result.pop_back();
            visited[x1][y1] = false;
        }
    }
}

int main()
{
    cin >> n >> m;
    board = vector<vector<char>>(n, vector<char>(m));
    visited = vector<vector<bool>>(n, vector<bool>(m, false));
    for (int i = 0; i < n; ++i)
    {
        for (int j = 0; j < m; ++j) cin >> board[i][j];
    }
    int x1, y1, x2, y2;
    cin >> x1 >> y1 >> x2 >> y2;
    tortoise(x1, y1, x2, y2);
}