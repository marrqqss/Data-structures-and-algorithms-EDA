#include <iostream>
#include <vector>
using namespace std;

vector<vector<char>> board;
vector<vector<bool>> visited;
int n, m;
int fx, fy;

const int dirx[4] = {-1, 1, 0, 0};
const int diry[4] = {0, 0, -1, 1};


bool pos_ok(int x, int y)
{
    if (x < 0 or x >= n or y < 0 or y >= m or visited[x][y]) return false;
    return true;
}

bool dangerous(int x, int y)
{
    for (int i = 0; i < 4; ++i)
    {
        if (pos_ok(x+dirx[i], y+diry[i]) and board[x+dirx[i]][y+diry[i]] == 'M') 
        {
            //cout << "CUIDAO" << endl;
            return true;
        }
    }
    return false;
}

bool dfs(int x, int y)
{
    //cout << x << " " << y << endl;
    bool posible = false;
    if (x == fx and y == fy) return true;
    else
    {
        visited[x][y] = true;
        for (int i = 0; i < 4; ++i)
        {
        //cout << "hola" << endl;
            if (pos_ok(x+dirx[i], y+diry[i]) and not dangerous(x+dirx[i], y+diry[i]))
            {
                posible = dfs(x+dirx[i], y+diry[i]);
                if (posible) return true;
            }
        }
    }
    return posible;
}

int main()
{
    while (cin >> n >> m)
    {
        board = vector<vector<char>>(n, vector<char>(m));
        visited = vector<vector<bool>>(n, vector<bool>(m, false));
        int x, y;
        for (int i = 0; i < n; ++i)
        {
            for (int j = 0; j < m; ++j)
            {
                cin >> board[i][j];
                if (board[i][j] == 'I')
                {
                    x = i;
                    y = j;
                }
                else if (board[i][j] == 'F')
                {
                    fx = i;
                    fy = j;
                }
            }
        }
        if (dfs(x, y)) cout << "SI" << endl;
        else cout << "NO" << endl;
    }
}