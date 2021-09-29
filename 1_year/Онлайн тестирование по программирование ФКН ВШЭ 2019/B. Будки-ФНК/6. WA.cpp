#include <iostream>
#include <vector>
#include <algorithm>

using namespace std;

int main() {
    int m,n,a,b,k,l;
    cin >> m >> n >> a >> b;
        if ( n - m <= 0){
            cout << 0;
            return 0;
        }
            else{
                k=(n-m)/4;
                l=((n-m)-k*4)/1;
                    if (b*k <= a*l){
                        cout << b;
                        return 0;
                    }
                cout << k*b + l*a;
            }
    return 0;
}