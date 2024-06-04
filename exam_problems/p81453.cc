#include <iostream>
#include <vector>
#include <queue>
#include <stack>
#include <algorithm>
using namespace std;

vector<vector<int>> matrix;
vector<int> mdistance;
vector<int> mprev;
queue<int> mqueue;
int n, m;

bool found(int x, int prev, int act_distance)
{
    if (mdistance[x] != -1) return false;
    else if (x == n-1)
    {
        mprev[x] = prev;
        mdistance[x] = act_distance;
        return true;
    }
    else
    {
        mqueue.push(x);
        mprev[x] = prev;
        mdistance[x] = act_distance;
        return false;
    }
}

void bfs(int x)
{
    mdistance[x] = 0;
    mqueue.push(x);
    int act_distance = 0;
    while (not mqueue.empty())
    {
        int x2 = mqueue.front();
        mqueue.pop();
        act_distance = mdistance[x2] + 1;
        sort(matrix[x2].begin(), matrix[x2].end());
        for (int i = 0; i < matrix[x2].size(); ++i)
        {
            if (found(matrix[x2][i], x2, act_distance)) break;
        }
    }
}

int main()
{
    while (cin >> n >> m)
    {
        matrix = vector<vector<int>>(n);
        mdistance = vector<int>(n, -1);
        mprev = vector<int>(n, -1);
        for (int i = 0; i < m; ++i)
        {
            int node1, node2;
            cin >> node1 >> node2;
            matrix[node1].push_back(node2);
        }
        bfs(0);
        //cout << "distance: " << mdistance[n-1] << endl;
        stack<int> mstack;
        int prev = mprev[n-1];
        cout << 0 << " ";
        while (prev != 0)
        {
            mstack.push(prev);
            prev = mprev[prev];
        }
        while (not mstack.empty())
        {
            cout << mstack.top() << " ";
            mstack.pop();
        }
        cout << n - 1 << endl;
    }  
}