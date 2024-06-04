#include <iostream>
#include <vector>
using namespace std;

vector<vector<int>> adjacency;
vector<bool> visited;
int n, m;

//returns true if cycle is found
bool dfs(int node, int prev_node)
{
    bool cycle = false;
    if (visited[node]) return true; //base case
    else
    {
        visited[node] = true;
        int i = 0;
        while (not cycle and i < adjacency[node].size())
        {
            int next_node = adjacency[node][i];
            if (next_node != prev_node) cycle = dfs(next_node, node);
            ++i;
        }
    }
    return cycle;
}

int ini_dfs()
{
    int count = 0;
    for (int node = 0; node < n; ++node)
    {
        if (not visited[node])
        {
            if (dfs(node, -1)) return -1;
            else ++count;
        }
    }
    return count;
}

int main()
{
    while (cin >> n >> m)
    {
        adjacency = vector<vector<int>>(n);
        visited = vector<bool>(n, false);
        for (int i = 0; i < m; ++i)
        {
            int x, y;
            cin >> x >> y;
            adjacency[x].push_back(y);
            adjacency[y].push_back(x);
        }
        int count_trees = ini_dfs();
        if (count_trees != -1) cout << count_trees << endl;
        else cout << "no" << endl; 
    }
}