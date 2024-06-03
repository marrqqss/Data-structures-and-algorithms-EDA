#include <iostream>
#include <vector>
using namespace std;

int n;
vector<string> names;
vector<string> result;
vector<vector<int>> dislikes;
vector<bool> visited;

int friends(int index_result, int i, int sum)
{
    if (index_result == n) return sum;
    else
    {
        int max = 0;
        for (int k = 0; k < n; ++k)
        {
            visited[i] = true;
            if (k != i)
            {
                int new_sum = friends(index_result+1, )
            }
        }
    }
}

int main()
{
    while (cin >> n)
    {
        names = vector<string>(n);
        result = vector<string>(n);
        dislikes = vector<vector<int>>(n, vector<int>(n));
        visited = vector<bool>(n, false);
        for (int i = 0; i < n; ++i) cin >> names[i];
        for (int i = 0; i < n; ++i)
        {
            for (int j = 0; j < n; ++j)
            {
                cin >> dislikes[i][j];
            }
        }
        cout << friends(0, 0, 0)

    }
}