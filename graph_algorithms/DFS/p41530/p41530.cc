#include <iostream>
#include <stack>
#include <vector>
using namespace std;

typedef vector<vector<int>> matrix;

matrix mat;
vector<bool> visited;

bool cicle_search(int node, int prev_node)
{
    //cout << node << endl;
    bool cicle = false;
    if (visited[node]) return true;
    else
    {
        visited[node] = true;
        for (int i = 0; not cicle and i < mat[node].size(); ++i) //recorremos los adyacientes al nodo
        {
            int next_node = mat[node][i];
            if (next_node != prev_node) cicle = cicle_search(next_node, node);
        }
    }
    return cicle;
}

int dfs(const int n)
{
    int count = 0;
    for (int node = 0; node < n; ++node)
    {
        if (not visited[node])
        {
            if (cicle_search(node, -1)) return -1;
            else ++count;
        }
    }
    return count;
}

int main()
{
    int n, m;
    while (cin >> n >> m)
    {
        mat = matrix(n); //lista de adyaciencias
        visited = vector<bool>(n, false);
        int contador = 0;
        for (int i = 0; i < m; ++i)
        {
            int x, y;
            cin >> x >> y;
            mat[x].push_back(y); // se añade a la adyaciencia de x la y
            mat[y].push_back(x); //al reves tb
        }
        int kek = dfs(n);
        if (kek == -1) cout << "no" << endl;
        else cout << kek << endl;
    }
}