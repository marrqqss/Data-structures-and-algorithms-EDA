#include <iostream>
#include <vector>
#include <map>
using namespace std;

void word_permutation(vector<string> &words, vector<string> &result, map<string, bool> &used, int index)
{
    if (index >= result.size())
    {
        cout << "(";
        for (int i = 0; i < result.size() - 1; ++i) cout << result[i] << ",";
        cout << result[result.size() - 1] << ")" << endl;
    }
    else
    {
        for (int i = 0; i < result.size(); ++i)
        {
            string act_word = words[i];
            if (not used[act_word])
            {
                used[act_word] = true;
                result[index] = act_word;
                word_permutation(words, result, used, index + 1);
                used[act_word] = false;
            }
        }
    }
}

int main()
{
    int n;
    cin >> n;
    vector<string> words(n);
    vector<string> result(n);
    map<string, bool> used;
    for (int i = 0; i < n; ++i) 
    {
        cin >> words[i];
        used.insert(make_pair(words[i], false));
    }
    word_permutation(words, result, used, 0);

}