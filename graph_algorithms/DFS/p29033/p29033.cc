#include <iostream>
#include <vector>
using namespace std;

typedef vector<vector<int>> matrix;

matrix mat;
vector<int> color; //-1 not coloured, 0 blue, 1 red, also serves as visited

bool colourable(int node, int prev_node)
{
    if (prev_node == -1) color[node] = 0;
    else
    {
        if (color[prev_node] == 0) color[node] = 1;
        else color[node] = 0;
    }
    bool can_colour = true;
    for (int i = 0; can_colour and i < mat[node].size(); ++i)
    {
        int next_node = mat[node][i];
        if (color[next_node] == -1) can_colour = colourable(next_node, node);
        else if (color[next_node] == color[node]) can_colour = false;
    }
    return can_colour;
}

bool dfs(const int n)
{
    for (int node = 0; node < n; ++node)
    {
        if (color[node] == -1)
        {
            if (not colourable(node, -1)) return false;
        }
    }
    return true;
}

int main()
{
    int n, m;
    while (cin >> n >> m)
    {
        mat = matrix(n);
        for (int i = 0; i < m; ++i)
        {
            int x, y;
            cin >> x >> y;
            mat[x].push_back(y);
            mat[y].push_back(x);
        }
        color = vector<int>(n, -1);
        if (dfs(n)) cout << "yes" << endl;
        else cout << "no" << endl;
    }
}