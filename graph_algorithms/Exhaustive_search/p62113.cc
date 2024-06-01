#include <iostream>
#include <vector>
#include <algorithm>
using namespace std;

void rec(const int x, int sum, vector<int> &coins, vector<pair<bool, bool>> &used, int index)
{
    if (sum == x)
    {
        int count = 0;
        cout << x << " = ";
        for (int i = 0; i < coins.size(); i++) {
            if (used[i].first) {
                cout << coins[i];
                count += coins[i];
                if (count != x) cout << " + ";
            }
            if (used[i].second) {
                cout << coins[i] << "p";
                count += coins[i];
            if (count != x) cout << " + ";
            }
        }
        cout << endl;
    }
    else if (x > sum and index < coins.size())
    {
        if (coins[index]+sum <= x)
        {
            if (not used[index].first)
            {
                used[index].first = true;
                rec(x, sum+coins[index], coins, used, index);
                used[index].first = false;
            }
            if (not used[index].second)
            {
                used[index].second = true;
                rec(x, sum+coins[index], coins, used, index+1);
                used[index].second = false;
            }
        }
        rec(x, sum, coins, used, index+1);
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
        vector<pair<bool, bool>> used(n, make_pair(false, false));
        rec(x, 0, coins, used, 0);
        cout << "----------" << endl;
    }
}