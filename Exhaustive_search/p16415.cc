#include <iostream>
#include <vector>
using namespace std;

int n;
vector<bool> occupied_columns;
vector<bool> occupied_rows;
vector<bool> occupied_diagonal1; // ///// diagonals; pos = row+column
vector<bool> occupied_diagonal2; // \\\\\ diagonals; pos =

int queens(int row)
{
    if (row >= n) return 1;
    else
    {
        int sum = 0;
        for (int column = 0; column < n; ++column)
        {
            if (not occupied_rows[row] and not occupied_columns[column] and not occupied_diagonal1[row+column] and not occupied_diagonal2[n-1+column-row])
            {
                occupied_rows[row] = true;
                occupied_columns[column] = true;
                occupied_diagonal1[row+column] = true;
                occupied_diagonal2[n-1+column-row] = true;
                sum += queens(row+1);
                occupied_rows[row] = false;
                occupied_columns[column] = false;
                occupied_diagonal1[row+column] = false;
                occupied_diagonal2[n-1+column-row] = false;
            }
        }
        return sum;
    }
}

int main()
{
    cin >> n;
    occupied_columns = vector<bool>(n, false);
    occupied_rows = vector<bool>(n, false);
    occupied_diagonal1 = vector<bool>(n*2 - 1, false); 
    occupied_diagonal2 = vector<bool>(n*2 - 1, false); 
    cout << queens(0) << endl;
}