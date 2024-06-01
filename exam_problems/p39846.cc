#include <iostream>
#include <vector>
#include <queue>
using namespace std;

typedef vector<vector<char>> graph;
typedef vector<vector<int>> gdistance;

graph g;
gdistance dist;
queue<pair<int, int>> qu;
int n, m;

bool treasure(int x, int y, int distance)
{
    if (x < 0 or x >= n or y < 0 or y >= m or g[x][y] == 'X' or dist[x][y] != -1) return false;
    if (g[x][y] == 't')
    {
        dist[x][y] = distance;
        qu.push(make_pair(x, y));
        return true;
    }
    else
    {
        dist[x][y] = distance;
        qu.push(make_pair(x, y));
        return false;
    }
}

int max_bfs(int x, int y)
{
    int max_distance = -1;
    qu.push(make_pair(x, y));
    dist[x][y] = 0;
    while (not qu.empty())
    {
        pair<int, int> act = qu.front();
        qu.pop();
        int x2 = act.first;
        int y2 = act.second;
        int distance_act = dist[x2][y2] + 1;
        if (treasure(x2, y2 + 1, distance_act))
        {
            if (distance_act > max_distance) max_distance = distance_act;
        }
        if (treasure(x2, y2 - 1, distance_act))
        {
            if (distance_act > max_distance) max_distance = distance_act;
        }
        if (treasure(x2 + 1, y2, distance_act))
        {
            if (distance_act > max_distance) max_distance = distance_act;
        }
        if (treasure(x2 - 1, y2, distance_act))
        {
            if (distance_act > max_distance) max_distance = distance_act;
        }
    }
    return max_distance;
}

int main()
{
    cin >> n >> m;
    g = graph(n, vector<char>(m));
    dist = gdistance(n, vector<int>(m, -1));
    for (int i = 0; i < n; ++i)
    {
        for (int j = 0; j < m; ++j) cin >> g[i][j];
    }
    int x,y;
    cin >> x >> y;
    int max_dist = max_bfs(x - 1, y - 1);
    if (max_dist != -1) cout << "maximum distance: " << max_dist << endl;
    else cout << "no treasure can be reached" << endl;
}