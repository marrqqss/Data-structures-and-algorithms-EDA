#include <iostream>
#include <vector>
#include <algorithm>
using namespace std;

void rec(const int x, int sum, vector<int> &coins, vector<int> &num_coins_used, int index , int &count)
{
    if (sum == x) ++count;
    else if (x > sum and index < coins.size())
    {
        if (coins[index]+sum <= x)
        {
            if (num_coins_used[index] < 2)
            {
                ++num_coins_used[index];
                rec(x, sum+coins[index], coins, num_coins_used, index, count);
                --num_coins_used[index];
            }
        }
        rec(x, sum, coins, num_coins_used, index+1, count);
    }
}

int main()
{
    int x, n;
    while (cin >> x >> n)
    {
        vector<int> coins(n);
        for (int i = 0; i < n; ++i) cin >> coins[i];
        sort(coins.begin(), coins.end());
        vector<int> num_coins_used(n);
        int count = 0;
        rec(x, 0, coins, num_coins_used, 0, count);
        cout << count << endl;
    }
}