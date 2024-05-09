#include <iostream>
#include <vector>
#include <queue>
#include <list>
using namespace std;

typedef vector<vector<int>> graph;

graph g; //lista de adyaciencia
vector<int> degrees; //almacena los grados de entrada de los nodos, es decir, cuantas "acciones" hay que hacer antes/cuantos nodos se dirigen a ese nodo
priority_queue<int, vector<int>, greater<int>> q; //almacena los nodos de grado 0 

int main()
{
    int n, m;
    while (cin >> n >> m)
    {
        g = graph(n);
        for (int i = 0; i < m; ++i)
        {
            int x, y;
            cin >> x >> y;
            g[x].push_back(y);
        }
        /*
        for (int i = 0; i < n; ++i)
        {
            cout << i << ": ";
            for (int j = 0; j < g[i].size(); ++j) cout << g[i][j] << " ";
            cout << endl;
        }
        */

        degrees = vector<int> (n, 0); 
        for (int i = 0; i < n; ++i)
        {
            for (int j = 0; j < g[i].size(); ++j)
            {
                ++degrees[g[i][j]];
            }
        }

        //for (int i = 0; i < n; ++i) cout << i << ": " << degrees[i] << endl;
        for (int i = 0; i < n; ++i)
        {
            if (degrees[i] == 0) q.push(i); //almacenamos los nodos grado 0
        }
        list<int> l;
        while (not q.empty())
        {
            int node = q.top();
            q.pop();
            l.push_back(node);
            for (int i = 0; i < g[node].size(); ++i)
            {
                int next_node = g[node][i];
                --degrees[next_node]; //se reduce el grado porque su previo (node) ya ha sido completado
                if (degrees[next_node] == 0) q.push(next_node);
            }
        }
        list<int>::const_iterator it = l.begin();
        cout << *it;
        ++it;
        while (it != l.end())
        {
            cout << " " << *it;
            ++it;
        }
        cout << endl;
    }
}