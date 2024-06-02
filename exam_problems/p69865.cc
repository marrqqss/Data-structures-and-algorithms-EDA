#include <iostream>
#include <vector>
#include <stack>
using namespace std;

stack<pair<int, int>> squares_bishops;
stack<pair<int, int>> squares_knights;
vector<vector<char>> board;
vector<vector<bool>> visited;
vector<pair<int,int>> bishops;
vector<pair<int, int>> knights;
int total_coins = 0;
int spots_coins = 0; //count of how many spots with coins there are
int visited_spots = 0;
int n, m;

const int DXK[8] = {2, 2, -2, -2, 1, 1, -1, -1};
const int DYK[8] = {1, -1, 1, -1, 2, -2, 2, -2};

bool pos_ok(int x, int y)
{
    if (x >= 0 and x < n and y >= 0 and y < m and board[x][y] != 'T') return true;
    return false;
}

bool is_coins(int x, int y)
{
    if (board[x][y] == 'B') return false;
    else if (board[x][y] == 'K') return false;
    else if (board[x][y] == 'T' or board[x][y] == '.') return false;
    return true;
}

int bishop_dfs(int x, int y)
{
    int coins = 0;
    squares_bishops.push(make_pair(x, y));
    visited[x][y] = true;
    while (not squares_bishops.empty() and visited_spots < spots_coins)
    {
        int x2 = squares_bishops.top().first;
        int y2 = squares_bishops.top().second;
        if (pos_ok(x2 - 1, y2 - 1) and not visited[x2-1][y2-1]) //up left
        {
            //cout << x2 << " " << y2 <<" up left" << endl;
            squares_bishops.push(make_pair(x2-1, y2-1));
            visited[x2-1][y2-1] = true;
            if (is_coins(x2-1, y2-1))
            {
                ++visited_spots;
                coins += board[x2-1][y2-1] - '0';
                board[x2-1][y2-1] = '.';
            }
        }
        else if (pos_ok(x2 + 1, y2 - 1) and not visited[x2+1][y2-1]) //down left
        {
            //cout << x2 << " " << y2 <<" down left" << endl;
            squares_bishops.push(make_pair(x2+1, y2-1));
            visited[x2+1][y2-1] = true;
            if (is_coins(x2+1, y2-1))
            {
                ++visited_spots;
                coins += board[x2+1][y2-1] - '0';
                board[x2+1][y2-1] = '.';
            }
        }
        else if (pos_ok(x2 - 1, y2 + 1) and not visited[x2-1][y2+1]) //up right
        {
            //cout << x2 << " " << y2 <<" up right" << endl;
            squares_bishops.push(make_pair(x2-1, y2+1));
            visited[x2-1][y2+1] = true;
            if (is_coins(x2-1, y2+1))
            {
                ++visited_spots;
                coins += board[x2-1][y2+1] - '0';
                board[x2-1][y2+1] = '.';
            }
        }
        else if (pos_ok(x2 + 1, y2 + 1) and not visited[x2+1][y2+1]) //down right
        {
            //cout << x2 << " " << y2 <<" down right" << endl;
            squares_bishops.push(make_pair(x2+1, y2+1));
            visited[x2+1][y2+1] = true;
            if (is_coins(x2+1, y2+1))
            {
                ++visited_spots;
                coins += board[x2+1][y2+1] - '0';
                board[x2+1][y2+1] = '.';
            }
        }
        else squares_bishops.pop();
    }
    return coins;
}

int knights_dfs(int x, int y)
{
    int coins = 0;
    squares_knights.push(make_pair(x,y));
    visited[x][y] = true;
    while (not squares_knights.empty() and visited_spots < spots_coins)
    {
        int x2 = squares_knights.top().first;
        int y2 = squares_knights.top().second;
        bool visitable = false;
        for (int i = 0; i < 8; ++i)
        {
            if (pos_ok(x2 + DXK[i], y2 + DYK[i]) and not visited[x2 + DXK[i]][y2 + DYK[i]])
            {
                visitable = true;
                squares_knights.push(make_pair(x2 + DXK[i], y2 + DYK[i]));
                visited[x2 + DXK[i]][y2 + DYK[i]] = true;
                if (is_coins(x2 + DXK[i], y2 + DYK[i]))
                {
                    ++visited_spots;
                    coins += board[x2 + DXK[i]][y2 + DYK[i]] - '0';
                    board[x2 + DXK[i]][y2 + DYK[i]] = '.';
                }
            }
        }
        if (not visitable) squares_knights.pop();
    }
    return coins;
}

int main()
{
    while (cin >> n >> m)
    {
        total_coins = 0;
        spots_coins = 0;
        visited_spots = 0;
        board = vector<vector<char>>(n, vector<char>(m));
        visited = vector<vector<bool>>(n, vector<bool>(m, false));
        bishops = vector<pair<int,int>>();
        knights = vector<pair<int,int>>();
        for (int i = 0; i < n; ++i)
        {
            for (int j = 0; j < m; ++j)
            {
                cin >> board[i][j];
                if (board[i][j] == 'B') bishops.push_back(make_pair(i,j));
                else if (board[i][j] == 'K') knights.push_back(make_pair(i,j));
                else if (board[i][j] != 'T' and board[i][j] != '.') ++spots_coins;
            }
        }
        int i = 0;
        while (visited_spots < spots_coins and i < bishops.size())
        {
            total_coins += bishop_dfs(bishops[i].first, bishops[i].second);
            ++i;
        }
        i = 0;
        visited = vector<vector<bool>>(n, vector<bool>(m, false));
        while (visited_spots < spots_coins and i < knights.size())
        {
            total_coins += knights_dfs(knights[i].first, knights[i].second);
            ++i;
        }
        cout << total_coins << endl;
    }
}