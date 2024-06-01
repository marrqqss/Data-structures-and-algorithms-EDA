#include <iostream>
#include <vector>
using namespace std;

void permutations(vector<int> &v, vector<bool> &visited, int index)
{
    if (index >= v.size())
    {
        cout << "(";
        for (int i = 0; i < v.size() - 1; ++i) cout << v[i] + 1 << ",";
        cout << v[v.size() - 1] + 1<< ")" << endl;
    }
    else
    {
        for (int i = 0; i < v.size(); ++i)
        {
            if (not visited[i])
            {
                v[index] = i;
                visited[i] = true;
                permutations(v, visited, index + 1);
                visited[i] = false;
            }
        }
    }
}

int main()
{
    int n;
    cin >> n;
    vector<int> v(n);
    vector<bool> visited(n, false);
    permutations(v, visited, 0);
}

