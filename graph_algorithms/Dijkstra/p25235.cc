#include <iostream>
#include <vector>
#include <limits>
#include <queue>
using namespace std;

const int INFINITY =  numeric_limits<int>::max();
typedef pair<int, int> arch; //pair distance, node
typedef vector<vector<arch>> Graf;

void dijkstra(const Graf &g, int node, vector<int> &distance, vector<int> &steps)
{
    distance[node] = 0;
    vector<bool> visited(g.size(), false);
    priority_queue<arch, vector<arch>, greater<arch>> pq; //priority queue of archs where the first element is the closest arch, it is important to put the distance first to respect the order
    pq.push(arch(0, node));

    while (not pq.empty())
    {
        int act_node = pq.top().second;
        pq.pop();
        if (not visited[act_node])
        {
            visited[act_node] = true;
            for (int i = 0; i < g[act_node].size(); ++i) //goes through all of his adjacent nodes
            {
                int next_node = g[act_node][i].first;
                int next_cost = g[act_node][i].second;
                if (distance[next_node] > distance[act_node] + next_cost or (distance[next_node] == distance[act_node] + next_cost and steps[next_node] > steps[act_node] + 1))
                {
                    steps[next_node] = steps[act_node] + 1;
                    distance[next_node] = distance[act_node] + next_cost;
                    pq.push(arch(distance[next_node], next_node));
                }
            }
        }
    }
}

int main()
{
    int nver, narc;
    while (cin >> nver >> narc) //nver = number of vertexs, narc = number of archs
    {
        Graf g(nver);
        vector<int> distance(nver, INFINITY); //initially, the distance from x to every node is infinity
        vector<int> steps(nver, 0);
        for (int i = 0; i < narc; ++i)
        {
            int v1, v2, c;
            cin >> v1 >> v2 >> c; //arch from v1 to v2 with cost c
            g[v1].push_back(make_pair(v2,c)); //only one push cuz it is a directed graph
        }
        int x, y;
        cin >> x >> y;
        dijkstra(g, x, distance, steps);
        if (distance[y] == INFINITY) cout << "no path from " << x << " to " << y << endl;
        else cout << "cost " << distance[y] << ", " << steps[y] << " step(s)" <<endl;
    }
}