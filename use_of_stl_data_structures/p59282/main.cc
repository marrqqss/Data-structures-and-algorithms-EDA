#include <iostream>
#include <map>
using namespace std;

/*
Write a program to compute the most common statistical measures (minimum, maximum and average) 
of several integer numbers. These numbers are known increasingly. At every moment, it is also 
possible to delete the smallest element.

Input consists of a sequence of (possibly, many) numbers, together with deleting instructions, 
as can be seen in the sample input. The numbers may be repeated. Deleting means removing the smallest 
element (one instance of it, if it is repeated). If there are no elements, deleting does nothing.

After every instruction of the input, print the minimum, maximum and average of the current elements 
with four digits after the decimal point, or tell that there are no elements. Follow the format of the 
sample output.
*/

int main()
{
    cout.setf(ios::fixed);
    cout.precision(4);
    map<int, int> m; //key = number, value = times it repeats
    map<int, int>::iterator it;
    double total = 0;
    double n = 0;
    string command;
    while (cin >> command)
    {
        if (command == "number")
        {
            int number;
            cin >> number;
            it = m.find(number);
            if (it == m.end()) //number doesn't exist
            {
                m.insert(it, make_pair(number, 1));
            }
            else //number exists
            {
                it -> second++;
            }
            total += number;
            ++n;
            cout << "minimum: " << m.begin() -> first;
            it = m.end();
            --it;
            cout << ", maximum: " << it -> first;
            cout << ", average: " << total/n << endl;
            //cout << "total: " << total << " n: " << n << endl;
        }
        else if (command == "delete")
        {
            if (not m.empty())
            {
                it = m.begin();
                it -> second--;
                int number = it -> first;
                total -= number;
                --n;
                if (it -> second == 0) m.erase(it);
                if (not m.empty())
                {
                    cout << "minimum: " << m.begin() -> first;
                    it = m.end();
                    --it;
                    cout << ", maximum: " << it -> first;
                    cout << ", average: " << total/n << endl;
                }
                else cout << "no elements" << endl;
            }
            else cout << "no elements" << endl;
        }
    }
}