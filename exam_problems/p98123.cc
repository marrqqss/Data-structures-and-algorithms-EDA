#include <iostream>
#include <set>
using namespace std;

int main()
{
    int n;
    cin >> n;
    string command;
    set<long int> bag;
    set<long int> max;
    int gems = 0;
    long int max_total = 0;
    while (cin >> command)
    {
        if (command == "leave")
        {
            int value;
            cin >> value;
            bag.insert(value);
            if (gems >= n) //more or equal gems to the size of the bag
            {
                ++gems;
                int smaller_max = *(max.begin());
                if (value > smaller_max)
                {
                    max_total -= smaller_max;
                    max_total += value;
                    max.erase(max.begin());
                    max.insert(value);
                }
            }
            else
            {
                ++gems;
                max_total += value;
                max.insert(value);
            }
            cout << max_total << endl;
        }
        else if (command == "take")
        {
            long int value;
            cin >> value;
            long int suma = 0;
            bag.erase(value);
            if (gems > n) //more or equal gems to the size of the bag
            {
                --gems;
                set<long int>::iterator it = max.find(value);
                if (it != max.end())
                {
                    max.erase(it);
                    max_total -= value;
                    set<long int>::iterator it2 = bag.end();
                    advance(it2, -n);
                    long int bag_max = *it2;
                    max_total += bag_max;
                    max.insert(bag_max);
                }
            }
            else
            {
                --gems;
                max.erase(value);
                max_total -= value;
            }
            cout << max_total << endl;
        }
    }
}