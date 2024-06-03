#include <iostream>
#include <vector>
using namespace std;

vector<int> dividers;
int n, m;

bool banned(int x)
{
    for (int i = 0; i < m; ++i)
    {
        if (x%dividers[i] == 0) return true;
    }
    return false;
}

void backtracking(int index, int total, int decimal)
{
    if (index == n)
    {
        cout << total << endl;
    }
    else
    {
        for (int i = 0; i <= 9; ++i)
        {
            if (total == 0) //base case
            {
                if (not banned(i))
                {
                    backtracking(index+1, i, decimal*10);
                }
            }
            else
            {
                if (not banned((total*decimal)+i))
                {
                    int temp = total*decimal+i;
                    backtracking(index+1, temp, decimal);
                }
            }
        }
    }
}

int main()
{
    while (cin >> n >> m)
    {
        dividers = vector<int>(m);
        for (int i = 0; i < m; ++i) cin >> dividers[i];
        backtracking(0,0,1);
        cout << "----------" << endl;
    }
}