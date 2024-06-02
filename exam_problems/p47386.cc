#include <iostream>
#include <map>
#include <set>
using namespace std;

int main()
{
    map<string, string> couples1, couples2;
    set<string> alone;
    string command;
    while (cin >> command)
    {
        if (command == "affair")
        {
            string person1, person2;
            cin >> person1 >> person2;
            if (couples1.empty())
            {
                if (person1 < person2)
                {
                    couples1.insert(make_pair(person1, person2));
                    couples2.insert(make_pair(person2, person1));
                }
                else
                {
                    couples1.insert(make_pair(person2, person1));
                    couples2.insert(make_pair(person1, person2));
                }
            }
            else
            {
                map<string, string>::iterator it = couples1.find(person1);
                if (it != couples1.end()) //if person1 was in affair with another person, this last persone becomes alone and the couple erases
                {
                    alone.insert((*it).second); //second person becomes alone
                    couples2.erase((*it).second); //erase second instance couple
                    couples1.erase(it); //erase first instance couple
                }
                it = couples2.find(person1);
                if (it != couples2.end()) //if person1 was in affair with another person, this last persone becomes alone and the couple erases
                {
                    alone.insert((*it).second); //second person becomes alone
                    couples1.erase((*it).second); //erase second instance couple
                    couples2.erase(it); //erase first instance couple
                }
                map<string, string>::iterator it2 = couples1.find(person2);
                if (it2 != couples1.end()) //if person2 was in affair with another person, this last persone becomes alone and the couple erases
                {
                    alone.insert((*it2).second); //second person becomes alone
                    couples2.erase((*it2).second); //erase second instance couple
                    couples1.erase(it2); //erase first instance couple
                }
                it2 = couples2.find(person2);
                if (it2 != couples2.end()) //if person2 was in affair with another person, this last persone becomes alone and the couple erases
                {
                    alone.insert((*it2).second); //second person becomes alone
                    couples1.erase((*it2).second); //erase second instance couple
                    couples2.erase(it2); //erase first instance couple
                }
                set<string>::iterator it3 = alone.find(person1);
                if (it3 != alone.end()) alone.erase(it3);
                set<string>::iterator it4 = alone.find(person2);
                if (it4 != alone.end()) alone.erase(it4);
                if (person1 < person2)
                {
                    couples1.insert(make_pair(person1, person2));
                    couples2.insert(make_pair(person2, person1));
                }
                else
                {
                    couples1.insert(make_pair(person2, person1));
                    couples2.insert(make_pair(person1, person2));
                }
            }
        }
        else if (command == "info")
        {
            map<string, string>::iterator it = couples1.begin();
            cout << "COUPLES:" << endl;
            while (it != couples1.end())
            {
                cout << (*it).first << " " << (*it).second << endl;
                ++it;
            }
            set<string>::iterator it2 = alone.begin();
            cout << "ALONE:" << endl;
            while (it2 != alone.end())
            {
                cout << *it2 << endl;
                ++it2;
            }
            cout << "----------" << endl;
        }
    }
}