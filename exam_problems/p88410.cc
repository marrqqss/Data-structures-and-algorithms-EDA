#include <iostream>
#include <vector>
using namespace std;

void escriu solucions (vector<int>& rosers, vector<int>& sol parcial, bool consec , int idx ) 
{
    if (idx == sol parcial . size ()){
        if ( consec ) {
        for (int x : sol parcial ) cout << x;
        cout << endl;
        }
    }
    else {
        for (int r = 1; r ≤ 3; ++r) {
            if ( rosers [r] > 0 and (not consec or idx == 0 or sol parcial [idx−1] 6 = r)) {
                sol parcial [idx ] = r ;
                −−rosers[r];
                escriu solucions ( rosers , sol parcial , consec or (idx > 0 and sol parcial [idx−1] == r) , idx +1);
                ++rosers[r ];
            }
        }
    }
}

void escriu solucions (int n) {
    vector<int> sol parcial (3*n );
    vector<int> rosers(4,n ); // rosers[0] no utilitzat
    escriu solucions ( rosers , sol parcial , false ,0);
}

int main ( ){
    int n;
    while (cin >> n){
    escriu solucions (n );
    cout << string(10, ' * ' ) << endl;
    }
}