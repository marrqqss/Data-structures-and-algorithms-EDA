#include <iostream>
#include <vector>
#include <queue>
using namespace std;

vector<vector<int>> adjacency;
vector<bool> visited;
vector<int> degrees;
priority_queue<int, vector<int>, greater<int>> pq;

int n, m;

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
        }
        degrees = vector<int>(n,0);
        //we store the degree of entry of each node
        for (int i = 0; i < n; ++i)
        {
            for (int j = 0; j < adjacency[i].size(); ++j)
            {
                ++degrees[adjacency[i][j]];
            }
        }
        //we push into the queue the nodes with 0 degrees
        for (int i = 0; i < n; ++i)
        {
            if (degrees[i] == 0) pq.push(i);
        }
        if (pq.empty()) cout << "yes" << endl; //if no 0 degree, its cyclic
        else
        {
            int count = n;
            while (not pq.empty())
            {
                --count;
                int node = pq.top();
                pq.pop();
                for (int i = 0; i < adjacency[node].size(); ++i)
                {
                    int next_node = adjacency[node][i];
                    --degrees[next_node];
                    if (degrees[next_node] == 0)
                    {
                        pq.push(next_node);
                    }
                }
            }
            //cout << count << endl;
            if (count == 0) cout << "no" << endl;
            else cout << "yes" << endl;
        }
    }
}