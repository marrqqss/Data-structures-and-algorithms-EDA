#include <iostream>
#include <vector>
using namespace std;

int n;
vector<bool> occupied_columns;
vector<bool> occupied_rows;
vector<bool> occupied_diagonal1; // ///// diagonals; pos = row+column
vector<bool> occupied_diagonal2; // \\\\\ diagonals; pos = n-1+column-row
vector<vector<bool>> chessboard;

void print()
{
    for (int i = 0; i < n; ++i)
    {
        for (int j = 0; j < n; ++j)
        {
            if (chessboard[i][j]) cout << "Q";
            else cout << ".";
        }
        cout << endl;
    }
}

void queens(int row, bool &found)
{
    if (not found and row >= n) 
    {
        print();
        found = true;
    }
    else
    {
        for (int column = 0; column < n and not found; ++column)
        {
            if (not occupied_rows[row] and not occupied_columns[column] and not occupied_diagonal1[row+column] and not occupied_diagonal2[n-1+column-row])
            {
                
                occupied_rows[row] = true;
                occupied_columns[column] = true;
                occupied_diagonal1[row+column] = true;
                occupied_diagonal2[n-1+column-row] = true;
                chessboard[row][column] = true;
                queens(row+1, found);
                chessboard[row][column] = false;
                occupied_rows[row] = false;
                occupied_columns[column] = false;
                occupied_diagonal1[row+column] = false;
                occupied_diagonal2[n-1+column-row] = false;
            }
        }
    }
}

int main()
{
    cin >> n;
    occupied_columns = vector<bool>(n, false);
    occupied_rows = vector<bool>(n, false);
    occupied_diagonal1 = vector<bool>(n*2 - 1, false); 
    occupied_diagonal2 = vector<bool>(n*2 - 1, false); 
    chessboard = vector<vector<bool>>(n, vector<bool>(n));
    bool found = false;
    queens(0, found);
    if (not found) cout << "NO SOLUTION" << endl;
}