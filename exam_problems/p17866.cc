#include <iostream>
#include <vector>
#include <queue>
using namespace std;

vector<vector<char>> board;
vector<vector<int>> bdistance;
queue<pair<int,int>> bqueue;
int n, m;

const int dirx[8] = {-2, -2, -1, 1, 2, 2, 1, -1};
const int diry[8] = {-1, 1, 2, 2, 1, -1, -2, -2};

bool carrot(int x, int y, int act_distance)
{
    if (x < 0 or x >= n or y < 0 or y >= m or board[x][y] == 'X' or bdistance[x][y] != -1) return false;
    else if (board[x][y] == 'p') return true;
    else
    {
        bdistance[x][y] = act_distance;
        bqueue.push(make_pair(x, y));
        return false;
    }
}

int bfs(int x, int y)
{
    bdistance[x][y] = 0;
    bqueue.push(make_pair(x, y));
    int act_distance = 0;
    while (not bqueue.empty())
    {
        int x2 = bqueue.front().first;
        int y2 = bqueue.front().second;
        bqueue.pop();
        act_distance = bdistance[x2][y2] + 1;
        for (int i = 0; i < 8; ++i)
        {
            if (carrot(x2+dirx[i], y2+diry[i], act_distance)) return act_distance;
        }
    }
    return -1;
}

int main()
{
    while(cin >> n >> m)
    {
        board = vector<vector<char>>(n, vector<char>(m));
        bdistance = vector<vector<int>>(n, vector<int>(m, -1));
        bqueue = queue<pair<int,int>>();
        for (int i = 0; i < n; ++i)
        {
            for (int j = 0; j < m; ++j) cin >> board[i][j];
        }
        int x, y;
        cin >> x >> y;
        int dist = bfs(x-1,y-1);
        if (dist != -1) cout << dist << endl;
        else cout << "no" << endl;
    }
}