#include <iostream>
#include <vector>
using namespace std;

int n;
vector<string> names;
vector<vector<int>> dislikes;
vector<bool> visited;

int friends(int index_result, int i, int sum)
{
    int min = -1;
    if (index_result >= n - 1) min = sum;
    else
    {
        int new_sum = -1;
        visited[i] = true;
        for (int k = 0; k < n; ++k)
        {
            if (k != i and not visited[k] and (min == -1 or sum + dislikes[i][k] < min))
            {
                new_sum = friends(index_result+1, k, sum + dislikes[i][k]);
                if (min == -1 or new_sum < min) 
                {
                    min = new_sum;
                }
            }
        }
        visited[i] = false;
    }
    return min;
}

int main()
{
    while (cin >> n)
    {
        names = vector<string>(n);
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
        cout << friends(0, 0, 0) << endl;
        
    }
}