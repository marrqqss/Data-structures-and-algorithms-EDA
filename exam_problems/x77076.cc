#include <iostream>
#include <vector>
using namespace std;

int first_occurrence(double input, const vector<double>& numbers, int l, int r)
{
    if (l > r) return -1;
    else
    {
        int m = (l+r)/2;
        if (numbers[m] == input)
        {
            int p_left = first_occurrence(input, numbers, l, m-1); //comprobar que no aparece antes a su izquierda
            if (p_left == -1) return m;
            else return p_left;
        }
        else if (numbers[m] > input) //esta a la izquierda
        {
            int p_left = first_occurrence(input, numbers, l, m-1);
            if (p_left == -1)
            {
                if (m+1 <= r and numbers[m+1] == input) return m + 1; //caso en el que se puede haber quedado en el medio?
                else return -1;
            }
        }
        else
        {
            if (m - 1 >= l and numbers[m - 1] == input) return m-1;
            return first_occurrence(input, numbers, m + 1, r);
        }
    }
    return -1;
}

int main()
{
    int n;
    while (cin >> n)
    {
        vector<double> numbers(n);
        for (int i = 0; i < n; ++i) cin >> numbers[i];
        int m;
        cin >> m;
        for (int i = 0; i < m; ++i)
        {
            double input;
            cin >> input;
            cout << first_occurrence(input, numbers, 0, numbers.size() - 1) << endl;
        }
    }
}