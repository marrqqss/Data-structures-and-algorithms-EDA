#include <iostream>
#include <vector>
using namespace std;

vector<vector<char>> matrix;
int n, m;

int backtr(int row, int column, int counter)
{
    if (row >= n) return counter;
    else
    {
        int next_row, next_column;
        if (column >= m - 1) //reaches limit of column
        {
            next_row = row + 1;
            next_column = 0;
        }
        else
        {
            next_row = row;
            next_column = column + 1;
        }
        matrix[row][column] = 'L';
        int new_lols = 0;
        if (row >= 2 and matrix[row-1][column] == 'O' and matrix[row-2][column] == 'L') ++new_lols;
        if (column >= 2 and matrix[row][column-1] == 'O' and matrix[row][column-2] == 'L') ++new_lols;
        if (row >= 2 and column >= 2 and matrix[row-1][column-1] == 'O' and matrix[row-2][column-2] == 'L') ++new_lols;
        if (row >= 2 and column + 2 < m and matrix[row-1][column+1] == 'O' and matrix[row-2][column+2] == 'L') ++new_lols;
        int count_l = backtr(next_row, next_column, counter+new_lols);
        matrix[row][column] = 'O';
        int count_o = backtr(next_row, next_column, counter);
        return max(count_l, count_o);
    }
}

int main()
{
    while (cin >> n >> m)
    {
        matrix = vector<vector<char>>(n, vector<char>(m));
        cout << backtr(0, 0, 0) << endl;
    }
}