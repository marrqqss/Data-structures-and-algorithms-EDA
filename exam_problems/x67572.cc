#include <iostream>
#include <vector>
#include <string>
using namespace std;

vector<string> words;
vector<string> result; 
vector<bool> used;
int n;

void backtr(int index)
{
    if (index == n)
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
                result[index] = words[i];
                used[i] = true;
                backtr(index+1);
                used[i] = false;
            }
            else
            {
                int pos_last_char = result[index - 1].size() - 1;
                char last_char = result[index - 1][pos_last_char];
                if (last_char != words[i][0] and not used[i])
                {
                    result[index] = words[i];
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
    words = vector<string>(n);
    result = vector<string>(n);
    used = vector<bool>(n, false);
    for (int i = 0; i < n; ++i) cin >> words[i];
    backtr(0);
}