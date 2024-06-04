#include <iostream>
#include <map>
using namespace std;

struct Info {
    string code;
    int price;
};


int main() {
map<int, Info> M; //key length, info code is destination and info price is price
char c;
while (cin >> c) {
    if (c == 'n') 
    {
        cout << "num: " << M.size() << endl;
    }
    else if (c == 'u') 
    {
        string code;
        int length, price;
        cin >> code >> length >> price;
        M[length].code = code;
        M[length].price = price;
    }
    else if (c == 'q') {
        int length;
        cin >> length;
        map<int, Info>::iterator it = M.find(length);
        if (it == M.end()) cout << "-1" << endl;
        else
        {
            cout << (*it).second.price << endl;
        }
    }
    else if (c == 'p') {
        cout << string(10, '-') << endl;
        map<int, Info>::iterator it = M.begin();
        while (it != M.end())
        {
            cout << (*it).second.code << " " << (*it).first << " " << (*it).second.price << endl;
            ++it;
        }
        cout << string(10, '*') << endl;
    }
    else {
        if (M.size() < 2) cout << "no" << endl;
        else
        {
            map<int, Info>::iterator it = M.begin();
            ++it;
            cout << (*it).second.code << " " << (*it).first << " " << (*it).second.price << endl;
        }
    }
}
}