#include <iostream>
#include <vector>
using namespace std;

vector<char> result;
vector<bool> used;
int n;

void backtr(int index)
{
    if (index >= n)
    {
        for (int i = 0; i < n; ++i) cout << result[i];
        cout << endl;
    }
    else
    {
        for (int i = 0; i < n; ++i)
        {
            if (index == 0)
            {
                result[index] = char('a' + i);
                used[i] = true;
                backtr(index+1);
                used[i] = false;
            }
            else
            {
                if (char(result[index-1] + 1) != char('a' + i) and not used[i])
                {
                    result[index] = char('a' + i);
                    used[i] = true;
                    backtr(index+1);
                    used[i] = false;
                }
            }
        }
    }
}

int main()
{
    cin >> n;
    result = vector<char>(n);
    used = vector<bool>(n);
    backtr(0);
}