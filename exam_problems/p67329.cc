#include <iostream>
#include <vector>
using namespace std;
    
int n;
vector<char> letters = {'A', 'C', 'G', 'T'};

void backtracking(int index, vector<char>& result)
{
    if (index >= n)
    {
        for (int i = 0; i < n; ++i)
        {
            cout << result[i];
        }
        cout << endl;
    }
    else
    {
        for (int i = 0; i < 4; ++i)
        {
            result[index] = letters[i];
            backtracking(index+1, result);
        }
    }
}

int main()
{
    cin >> n;
    vector<char> result(n);
    backtracking(0, result);
}