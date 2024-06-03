#include <iostream>
#include <vector>
#include <stack>
using namespace std;

vector<vector<char>> board;
vector<vector<bool>> visited;
stack<pair<int,int>> nextn;
int n, m;

vector<int> dirx = {-1, 1, 0, 0, -1, 1, -1, 1}; //up, down, left, right, upleft, downleft, upright, downright
vector<int> diry = {0, 0, -1, 1, -1, -1, 1, 1};

vector<int> dfsx = {-1, 1, 0, 0};
vector<int> dfsy = {0, 0, -1, 1};

bool posible(int x, int y)
{
    if (x < 0 or x >= n or y < 0 or y >= m or board[x][y] == 'X') return false;
    return true;
}

bool dangerous(int x, int y)
{
    for (int i = 0; i < 8; ++i)
    {
        if (posible(x+dirx[i], y+diry[i]) and board[x+dirx[i]][y+diry[i]] == 'F') return true;
    }
    return false;
}

bool pacman_dfs(int x, int y)
{
    if (not dangerous(x, y))
    {
        visited[x][y] = true;
        nextn.push(make_pair(x, y));
        while (not nextn.empty())
        {
            int x2 = nextn.top().first;
            int y2 = nextn.top().second;
            if (board[x2][y2] == 'B') return true;
            else if (posible(x2-1, y2) and not dangerous(x2-1, y2) and not visited[x2-1][y2])
            {
                nextn.push(make_pair(x2-1, y2));
                visited[x2-1][y2] = true;
            }
            else if (posible(x2+1, y2) and not dangerous(x2+1, y2) and not visited[x2+1][y2])
            {
                nextn.push(make_pair(x2+1, y2));
                visited[x2+1][y2] = true;
            }
            else if (posible(x2, y2 - 1) and not dangerous(x2, y2 - 1) and not visited[x2][y2 - 1])
            {
                nextn.push(make_pair(x2, y2 - 1));
                visited[x2][y2 - 1] = true;
            }
            else if (posible(x2, y2 + 1) and not dangerous(x2, y2 + 1) and not visited[x2][y2 + 1])
            {
                nextn.push(make_pair(x2, y2 + 1));
                visited[x2][y2 + 1] = true;
            }
            else nextn.pop();
        }
    }
    return false; 
}

int main()
{
    while (cin >> n >> m)
    {
        int x = 0;
        int y = 0;
        board = vector<vector<char>>(n, vector<char>(m));
        visited = vector<vector<bool>>(n, vector<bool>(m, false));
        nextn = stack<pair<int,int>>();
        for (int i = 0; i < n; ++i)
        {
            for (int j = 0; j < m; ++j)
            {
                cin >> board[i][j];
                if (board[i][j] == 'P') //pacman position
                {
                    x = i;
                    y = j;
                }
            }
        }
        if (pacman_dfs(x, y)) cout << "yes" << endl;
        else cout << "no" << endl;
    }
}