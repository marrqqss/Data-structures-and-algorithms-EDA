#include <iostream>
#include <vector>
using namespace std;

vector<vector<char>> board;
vector<bool> used_rows;
vector<bool> used_columns;
int n, m;

void backtr(int row)
{
    if (row >= n)
    {
        for (int i = 0; i < n; ++i)
        {
            for (int j = 0; j < m; ++j)
            {
                if (board[i][j] == 'R') cout << 'R';
                else cout << '.';
            }
            cout << endl;
        }
        cout << endl;
    }
    else
    {
        for (int column = 0; column < m; ++column)
        {
            if (board[row][column] != 'R' and not used_columns[column] and not used_rows[row])
            {
                used_columns[column] = true;
                used_rows[row] = true;
                board[row][column] = 'R';
                backtr(row+1);
                used_columns[column] = false;
                used_rows[row] = false;
                board[row][column] = ' ';
            }
        }
    }
}

int main()
{
    cin >> n >> m;
    board = vector<vector<char>>(n, vector<char>(m));
    used_rows = vector<bool>(n, false);
    used_columns = vector<bool>(m, false);
    backtr(0);
}