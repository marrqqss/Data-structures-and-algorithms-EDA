#include <iostream>
#include <vector>
#include <queue>
#include <list>
#include <map>
using namespace std;

map<string, vector<string>> adyaciencia;
map<string, int> degrees; //almacena los grados de entrada de los nodos, es decir, cuantas "acciones" hay que hacer antes/cuantos nodos se dirigen a ese nodo
priority_queue<string, vector<string>, greater<string>> q; //almacena los nodos de grado 0 

int main()
{
    int n, m;
    cin >> n;
    for (int i = 0; i < n; ++i)
    {
        string s;
        cin >> s;
        adyaciencia.insert(make_pair(s, vector<string>()));
    }
    cin >> m;
    for (int i = 0; i < m; ++i)
    {
        string s1, s2;
        cin >> s1 >> s2;
        adyaciencia[s1].push_back(s2);
    }

    map<string, vector<string>>::const_iterator it = adyaciencia.begin();
    while (it != adyaciencia.end())
    {
        for (int i = 0; i < (*it).second.size(); ++i)
        {
            string first = (*it).second[i];
            degrees[first]++;
        }
        ++it;
    }
    map<string, int>::const_iterator it2 = degrees.begin();
    while (it2 != degrees.end())
    {
        cout << (*it2).first << " " << (*it2).second << endl;
        ++it2;
    }
}