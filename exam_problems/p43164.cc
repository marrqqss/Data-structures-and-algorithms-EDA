#include <iostream>
#include <vector>
#include <queue>
using namespace std;
int n, m, x, y;
int maxdistance, secondmax;
int total_count;

vector<vector<char>> board;
vector<vector<int>> bdistance;
queue<pair<int,int>> bqueue;

const int dirx[4] = {-1,1,0,0};
const int diry[4] = {0,0,-1,1};

bool treasure(int x, int y, int act_distance)
{
    if (x < 0 or x >= n or y < 0 or y >= m or board[x][y] == 'X' or bdistance[x][y] != -1) return false;
    else if (board[x][y] == 't')
    {
        bdistance[x][y] = act_distance;
        bqueue.push(make_pair(x,y));
        if (maxdistance == -1) maxdistance = act_distance;
        else if (secondmax == -1)
        {
            if (act_distance > maxdistance)
            {
                secondmax = maxdistance;
                maxdistance = act_distance;
            }
            else
            {
                secondmax = act_distance;
            }
        }
        else if (maxdistance < act_distance)
        {
            secondmax = maxdistance;
            maxdistance = act_distance;
        }
        else if (secondmax < act_distance) secondmax = act_distance; 
        return true;
    }
    else
    {
        bdistance[x][y] = act_distance;
        bqueue.push(make_pair(x,y));
        return false;
    }
}

int bfs(int x, int y)
{
    int count = 0;
    int act_distance = 0;
    bdistance[x][y] = 0;
    bqueue.push(make_pair(x, y));
    while (not bqueue.empty() and count < total_count)
    {
        int x2 = bqueue.front().first;
        int y2 = bqueue.front().second;
        bqueue.pop();
        act_distance = bdistance[x2][y2] + 1;
        for (int i = 0; i < 4; ++i)
        {
            if (treasure(x2+dirx[i], y2+diry[i], act_distance)) ++count;
        }
    }
    return count;
}

int main()
{
    cin >> n >> m;
    board = vector<vector<char>>(n, vector<char>(m));
    bdistance = vector<vector<int>>(n, vector<int>(m, -1));
    bqueue = queue<pair<int,int>>();
    maxdistance = -1;
    secondmax = -1;
    total_count = 0;
    for (int i = 0; i < n; ++i)
    {
        for (int j = 0; j < m; ++j) 
        {
            cin >> board[i][j];
            if (board[i][j] == 't') ++total_count;
        }
    }
    cin >> x >> y;
    if (bfs(x - 1, y - 1) < 2) cout << "we cannot reach two or more treasures" << endl;
    else cout << "second maximum distance: " << secondmax << endl;
}