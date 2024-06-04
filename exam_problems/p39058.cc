#include <iostream>
#include <vector>
#include <queue>
using namespace std;

vector<vector<char>> board;
vector<vector<int>> bdistance;
queue<pair<int,int>> bqueue;
int n, m;
int cx, cy; //horse position
int flower_count;
double total_distances = 0;

const int dirx[8] = {-2, -2, -1, 1, 2, 2, 1, -1};
const int diry[8] = {-1, 1, 2, 2, 1, -1, -2, -2};

bool flower(int x, int y, int act_distance)
{
    if (x < 0 or x >= n or y < 0 or y >= m or board[x][y] == 'a' or bdistance[x][y] != -1) return false;
    else if (board[x][y] == 'F')
    {
        bdistance[x][y] = act_distance;
        bqueue.push(make_pair(x, y));
        board[x][y] = '.';
        return true;
    }
    else
    {
        bdistance[x][y] = act_distance;
        bqueue.push(make_pair(x, y));
        return false;
    }
}

bool bfs(int x, int y)
{
    bool found = false;
    bdistance[x][y] = 0;
    bqueue.push(make_pair(x, y));
    while (not bqueue.empty())
    {
        int x2 = bqueue.front().first;
        int y2 = bqueue.front().second;
        bqueue.pop();
        int act_distance = bdistance[x2][y2] + 1;
        for (int i = 0; i < 8; ++i)
        {
            if (flower(x2 + dirx[i], y2 + diry[i], act_distance))
            {
                found = true;
                ++flower_count;
                total_distances += act_distance;
            }
        }
    }
    return found;
}

int main()
{
    cout.setf(ios::fixed);
    cout.precision(4);
    cin >> n >> m;
    board = vector<vector<char>>(n, vector<char>(m));
    bdistance = vector<vector<int>>(n, vector<int>(m, -1));
    for (int i = 0; i < n; ++i)
    {
        for (int j = 0; j < m; ++j)
        {
            cin >> board[i][j];
            if (board[i][j] == 'C')
            {
                cx = i;
                cy = j;
            }
        }
    }
    bool check = bfs(cx, cy);
    if (check)
    {
        cout << "flors accessibles: " << flower_count << endl;
        cout << "distancia mitjana: " << double(total_distances/double(flower_count)) << endl;
    }
    else cout << "el cavall no pot arribar a cap flor" << endl;


}