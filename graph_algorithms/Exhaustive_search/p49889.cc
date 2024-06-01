#include <iostream>
#include <vector>
#include <string>
using namespace std;

void recursive(string &consonants, string &vowels, vector<bool> &used_cons, vector<bool> &used_vow, vector<char> &result, int index, bool &consonant)
{
    if (index >= result.size())
    {
        for (int i = 0; i < result.size(); ++i) cout << result[i];
        cout << endl;
    }
    else
    {
        for (int i = 0; i < consonants.size(); ++i)
        {
            if (consonant and not used_cons[i])
            {
               //cout << "CONSONANTE " << consonants[i] << endl;
                result[index] = consonants[i];
                used_cons[i] = true;
                consonant = not consonant;
                recursive(consonants, vowels, used_cons, used_vow, result, index + 1, consonant);
                consonant = not consonant;
                used_cons[i] = false;
            }
            else if (not used_vow[i])
            {
                //cout << "VOCAL " << vowels[i] << endl;
                result[index] = vowels[i];
                used_vow[i] = true;
                consonant = not consonant;
                recursive(consonants, vowels, used_cons, used_vow, result, index + 1, consonant);
                consonant = not consonant;
                used_vow[i] = false;
            }
        }
    }
}

int main()
{
    int n;
    string consonants, vowels;
    cin >> n >> consonants >> vowels;
    vector<bool> used_cons(n, false);
    vector<bool> used_vow(n, false);
    vector<char> result(2*n);
    bool consonant = true;
    recursive(consonants, vowels, used_cons, used_vow, result, 0, consonant);
}