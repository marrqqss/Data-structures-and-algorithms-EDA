#include <iostream>
#include <vector>
using namespace std;

int n, k;
vector<vector<char>> board;

bool possible(int row, int column)
{
    if (row - 1 >= 0 and board[row - 1][column] == 'K') return false; //up
    if (row + 1 < n and board[row + 1][column] == 'K') return false; //down;
    if (column - 1 >= 0 and board[row][column - 1] == 'K') return false; //left;
    if (column + 1 < n and board[row][column + 1] == 'K') return false; //right
    if (row - 1 >= 0 and column - 1 >= 0 and board[row - 1][column - 1] == 'K') return false; //up left
    if (row - 1 >= 0 and column + 1 < n and board[row - 1][column + 1] == 'K') return false; //up right
    if (row + 1 < n and column - 1 >= 0 and board[row + 1][column - 1] == 'K') return false; //down left
    if (row + 1 < n and column + 1 < n and board[row + 1][column + 1] == 'K') return false; //down right
    return true;
}

void kings(int row, int column, int count)
{
    if (count == k)
    {
        for (int i = 0; i < n; ++i)
        {
            for (int j = 0; j < n; ++j)
            {
                if (board[i][j] == 'K') cout << 'K';
                else cout << '.';
            }
            cout << endl;
        }
        cout << "----------" << endl;
    }
    else
    {
        if (column >= n and row < n) 
        {
            column = 0;
            ++row;
        }
        if (row < n and column < n and board[row][column] == '.')
        {
            if (possible(row, column))
            {
                board[row][column] = 'K';
                kings(row, column + 1, count + 1);
                board[row][column] = '.';
            }
        }
        if (row < n and column < n) kings(row, column + 1, count);
    }
}

int main()
{
    cin >> n >> k;
    board = vector<vector<char>>(n, vector<char>(n, '.'));
    kings(0, 0, 0);
}