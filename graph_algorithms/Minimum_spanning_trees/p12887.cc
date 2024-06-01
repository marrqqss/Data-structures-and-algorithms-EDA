#include <iostream>
#include <vector>
#include <queue>
using namespace std;

typedef vector<vector<pair<int,int>>> graph; //a matrix where stores the adjacent vertexs and the weight. First is weight and second is vertex

int MST (graph &g, vector<bool> &visited)
{
    priority_queue<pair<int, int>, vector<pair<int,int>>, greater<pair<int,int>>> pq;
    pq.push(make_pair(0,0));
    int sum = 0;
    while (not pq.empty())
    {
        int weight = pq.top().first;
        int node = pq.top().second;
        pq.pop();
        if (not visited[node])
        {
            visited[node] = true;
            sum += weight;
            for (int i = 0; i < g[node].size(); ++i)
            {
                int next_node = g[node][i].second;
                int next_weight = g[node][i].first;
                pq.push(make_pair(next_weight, next_node));
            }
        }
    }
    return sum;
}

int main()
{
    int n, m; //n = num vertexs, m = num edges
    while (cin >> n >> m)
    {
        graph g(n);
        vector<bool> visited(n, false);
        for (int i = 0; i < m; ++i)
        {
            int u, v, w; //u,v vertexs, w edge weight
            cin >> u >> v >> w;
            --u; //they are given from 1
            --v;
            g[u].push_back(make_pair(w, v));
            g[v].push_back(make_pair(w, u));
        }
        cout << MST(g, visited) << endl;
    }
}