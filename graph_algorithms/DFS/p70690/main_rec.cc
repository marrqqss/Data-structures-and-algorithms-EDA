#include <iostream>
#include <vector>
#include <stack>
using namespace std;

typedef vector<vector<char>> graph;
typedef vector<vector<bool>> visited;

graph g;
visited v;
stack<pair<int,int>> p;

void read_graph(const int n, const int m)
{
    for (int i = 0; i < n; ++i)
    {
        for (int j = 0; j < m; ++j) cin >> g[i][j];
    }
}

bool pos_ok(int r, int c)
{
    if (r >= 0 and r < g.size() and c >= 0 and c < g[0].size() and g[r][c] != 'X') return true;
    return false;
}

bool dfs_search(int r, int c)
{
    if (pos_ok(r, c))
    {
        if (g[r][c] == 't') return true;
        v[r][c] = true;
        p.push(make_pair(r, c));
        if (pos_ok(r-1, c) and not v[r-1][c]) return dfs_search(r-1, c); //up
        if (pos_ok(r, c-1) and not v[r][c-1]) return dfs_search(r, c-1); //left
        if (pos_ok(r+1, c) and not v[r+1][c]) return dfs_search(r+1, c); //down
        if (pos_ok(r, c+1) and not v[r][c+1]) return dfs_search(r, c+1); //up
        int r2 = p.top().first;
        int c2 = p.top().first;
        p.pop();
        return dfs_search(r2, c2);
    }
    return false;
}

int main()
{
    int n, m;
    cin >> n >> m;
    g = graph(n, vector<char>(m));
    read_graph(n, m);
    v = visited(n, vector<bool>(m, false)); //lista de adyaciencias
    int pos_r, pos_c;
    cin >> pos_r >> pos_c;
    if (dfs_search(pos_r - 1, pos_c - 1)) cout << "yes" << endl; //-1 pq son posiciones relativas, no del vector (1 == 0)
    else cout << "no" << endl;
}