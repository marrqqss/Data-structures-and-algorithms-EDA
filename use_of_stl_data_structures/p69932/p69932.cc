#include <iostream>
#include <set>
#include <string>
#include <sstream>
using namespace std;

/*
You are given several natural numbers. Put some of the numbers side by side according to these rules:

    the resulting sequence must be increasing;
    there cannot be two even numbers together nor two odd numbers together. 

Write a program such that, for every given line, prints the length of the longest sequence that can be produced according to the rules above using the numbers on that line.

Input

Input consists of several lines. Each line contains a sequence of natural numbers.

Output

For each line of the input, print a line with the length of the longest sequence that can be made according to the rules given above.
*/

int main()
{
    string line;
    while (getline(cin, line)) //get input from console and insert it into line
    {
        set<int> set;
        int num; //used to store the int in the string stream (auto converts the string into int)
        stringstream s(line); //stores the whole linea in a string stream (fractured strings separed by ' ') called s
        while (s >> num) //s passes the next number in the string stream
        {
            set.insert(num);
        }
        int count = 0;
        int last = 0;
        bool op = false;
        auto it = set.begin();
        while (it != set.end())
        {
            if (it != set.begin())
            {
                if ((last%2 == 0 and (*it)%2 != 0) or (last%2 != 0 and (*it)%2 == 0))
                {
                    ++count;
                }
            }
            op = true;
            last = *it;
            ++it;
        }
        if (op) ++count;
        cout << count << endl;
    }
}