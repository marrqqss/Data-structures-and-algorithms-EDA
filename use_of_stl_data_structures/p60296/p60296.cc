#include <iostream>
#include <map>
#include <set>
using namespace std;

/*
Simulate a server of a role-playing game for two players. Each player has an “elo”,
 which is a value larger the better is the player. Everyone starts with 1200 points, 
 and nobody ever gets a lower quantity, no matter how many games are lost. Whenever 
 there is a match, the winner gets 10 elo points, and the loser loses 10 elo points 
 (with the limitation above). The elo of a player is kept when he or she disconnects 
 from the server.

We have these instructions:

    “LOGIN” j : The player j starts a session. Ignore it if the player is already connected.
    “LOGOUT” j : The player j closes the session. Ignore it if the player is not connected.
    “PLAY” j1   j2 : Indicates that j1 has beaten j2, with j1 ≠ j2. Ignore it but print an 
    error message if any of the two players is not connected.
    “GET_ELO” j : Print the player j (who was connected for sure previously, although now 
    may be disconnected) with his or her current elo. 

Input

Input consists of several instructions for at most 105 players. Each player’s name is 
different and made up of only lowercase letters.

Output

For every instruction “GET_ELO” (and perhaps “PLAY”) print the proper output. At the end, 
print an empty line, the word “RANKING”, and a ranking sorted in decreasing order by elo 
(if there is a tie, print first the alfabetically smallest name) with all the players ever 
connected to the server.
*/

int main()
{
    map<string, pair<int, bool>> log;
    string command;
    while (cin >> command)
    {
        if (command == "LOGIN")
        {
            string player;
            cin >> player;
            auto it = log.find(player);
            if (it == log.end())
            {
                log.insert(it, make_pair(player, make_pair(-1200, true))); //its inverted to match the conditions of sorting
            }
            else
            {
                it->second.second = true;
            }
        }
        else if (command == "LOGOUT")
        {
            string player;
            cin >> player;
            auto it = log.find(player);
            if (it != log.end())
                it->second.second = false;
        }
        else if (command == "PLAY")
        {
            string player1, player2;
            cin >> player1 >> player2;
            auto it1 = log.find(player1);
            auto it2 = log.find(player2);
            if (it1 != log.end() and it2 != log.end())
            {
                if (it1->second.second == true and it2->second.second == true)
                {
                    it1->second.first -= 10; //wins
                    it2->second.first +=10; //loses
                    if (it2->second.first > -1200) it2->second.first = -1200;
                }
                else cout << "player(s) not connected" << endl;
            }
            else cout << "player(s) not connected" << endl;
        }
        else if (command == "GET_ELO")
        {
            string player;
            cin >> player;
            cout << player << " " << log[player].first * (-1) << endl;
        }
    }
    cout << endl << "RANKING" << endl;
    set<pair<int, string>> ranking;
    for (auto it = log.begin(); it != log.end(); ++it)
    {
        ranking.insert(make_pair(it->second.first, it->first));
    }
    for (auto it = ranking.begin(); it != ranking.end(); ++it)
    {
        cout << it->second << " " << it->first * (-1) << endl;
    }
}