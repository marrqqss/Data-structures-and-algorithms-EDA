#include <iostream>
#include <queue>
#include <list>
#include <utility>
using namespace std;

typedef vector<vector<char>> graph;

typedef vector<vector<int>> g_distance;

graph g;
g_distance dist;
queue<pair<int, int>> Q;

bool treasure(int x, int y, int n, int m, int d)
{
    bool found = false;
    if (x < 0 or x >= n or y < 0 or y >= m or g[x][y] == 'X' or dist[x][y] != -1) return false;
    if (g[x][y] == 't') found = true;
    dist[x][y] = d;
    Q.push(make_pair(x, y));
    return found; 
}
int bfs(int x, int y, int n, int m)
{
    dist = g_distance(n, vector<int>(m, -1));
    Q.push(make_pair(x, y));
    dist[x][y] = 0;
    int max_distance = -1;
    while (not Q.empty())
    {
        pair<int, int> v = Q.front();
        Q.pop();
        int x2 = v.first;
        int y2 = v.second;
        int distance_act = dist[x2][y2] + 1;
        if (treasure(x2, y2 + 1, n, m, distance_act) or treasure(x2, y2 - 1, n, m, distance_act) or treasure(x2 + 1, y2, n, m, distance_act) or treasure(x2 - 1, y2, n, m, distance_act))
        {
            if (distance_act > max_distance) max_distance = distance_act;
        }
    }
    return max_distance;
}

int main()
{
    int n, m;
    cin >> n >> m;
    g = graph(n, vector<char>(m));
    for (int i = 0; i < n; ++i)
    {
        for (int j = 0; j < m; ++j) cin >> g[i][j];
    }
    int x, y;
    cin >> x >> y;
    int distance = bfs(x - 1, y - 1, n, m);
    if (distance != -1) cout << "maximum distance: " << distance << endl;
    else cout << "no treasure can be reached" << endl;
}