#include <iostream>
#include <vector>
#include <queue>
#include <stack>
using namespace std;

vector<vector<char>> board;
vector<vector<int>> bdistance;
vector<vector<pair<int,int>>> bprev;
queue<pair<int,int>> bqueue;

int n, m;

int foundx, foundy;

bool peasant(int x, int y, int act_distance, int xprev, int yprev)
{
    if (x < 0 or x >= n or y < 0 or y >= m or board[x][y] == 'X' or bdistance[x][y] != -1) return false;
    else if (board[x][y] == 'F') 
    {
        bprev[x][y] = make_pair(xprev, yprev);
        foundx = x;
        foundy = y;
        return true;
    }
    else
    {
        bqueue.push(make_pair(x,y));
        bdistance[x][y] = act_distance;
        bprev[x][y] = make_pair(xprev, yprev);
    }
    return false;
}

int bfs(int x, int y)
{
    bqueue.push(make_pair(x,y));
    bdistance[x][y] = 0;
    while (not bqueue.empty())
    {
        int x2 = bqueue.front().first;
        int y2 = bqueue.front().second;
        bqueue.pop();
        int act_distance = bdistance[x2][y2] + 1;
        if (peasant(x2-1, y2, act_distance, x2, y2) or peasant(x2+1, y2, act_distance, x2, y2) or peasant(x2, y2-1, act_distance, x2, y2) or peasant(x2, y2+1, act_distance, x2, y2)
            or peasant(x2+1, y2+1, act_distance, x2, y2) or peasant(x2-1, y2-1, act_distance, x2, y2) or peasant(x2-1, y2+1, act_distance, x2, y2) or peasant(x2+1, y2-1, act_distance, x2, y2))
        {
            return act_distance;
        }
    }
    return -1;
}

int main()
{
    while (cin >> n >> m)
    {
        foundx = -1;
        foundy = -1;
        board = vector<vector<char>>(n, vector<char>(m));
        bdistance = vector<vector<int>>(n, vector<int>(m, -1));
        bprev = vector<vector<pair<int,int>>>(n, vector<pair<int,int>>(m, make_pair(-1, -1)));
        bqueue = queue<pair<int,int>>();
        int x, y;
        for (int i = 0; i < n; ++i)
        {
            for (int j = 0; j < m; ++j) 
            {
                cin >> board[i][j];
                if (board[i][j] == 'K')
                {
                    x = i;
                    y = j;
                }
            }
        }
        int bfs_dist = bfs(x, y);
        if (bfs_dist != -1)
        {
            cout << bfs_dist + 1 << "  ";
            stack<pair<int,int>> output;
            cout << x << " " << y << "  ";
            while (foundx != x or foundy != y)
            {
                int tempx = foundx;
                int tempy = foundy;
                output.push(make_pair(tempx, tempy));
                foundx = bprev[tempx][tempy].first;
                foundy = bprev[tempx][tempy].second;
            }
            while (not output.empty())
            {
                cout << output.top().first << " " << output.top().second;
                output.pop();
                if (not output.empty()) cout << "  ";
            }
            cout << endl;
        }
        else cout << 0 << endl;
    }
}

