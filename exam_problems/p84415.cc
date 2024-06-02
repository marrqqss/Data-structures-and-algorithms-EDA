#include <iostream>
#include <map>
using namespace std;

int main()
{
    string command;
    map<string, int> bag; //string is the word and the int the number of times it appears
    while (cin >> command)
    {
        if (command == "store")
        {
            string word;
            cin >> word;
            bag[word] += 1;
        }
        else if (command == "delete")
        {
            string word;
            cin >> word;
            map<string, int>::iterator it = bag.find(word);
            if (it != bag.end())
            {
                --(*it).second;
                if ((*it).second == 0) bag.erase(it);
            }
        }
        else if (command == "maximum?")
        {
            if (bag.empty()) cout << "indefinite maximum" << endl;
            else
            {
                map<string, int>::iterator it = bag.end();
                --it;
                cout << "maximum: " << (*it).first << ", " << (*it).second << " time(s)" << endl;
            }
        }
        else if (command == "minimum?")
        {
            if (bag.empty()) cout << "indefinite minimum" << endl;
            else
            {
                map<string, int>::iterator it = bag.begin();
                cout << "minimum: " << (*it).first << ", " << (*it).second << " time(s)" << endl;
            }
        }
    }
    
}