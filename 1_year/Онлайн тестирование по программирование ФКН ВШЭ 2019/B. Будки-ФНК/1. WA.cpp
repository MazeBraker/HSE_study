#include <iostream>
#include <vector>
#include <algorithm>

using namespace std;

int main() {
    int m,n,a,b,k;
    cin >> m >> n >> a >> b;
        if ( n <= m){
            cout << 0;
            return 0;
        }
        k = n - m;
        if (k%4 * a > b){
            cout << k/4 * b + b;
        }
        else if (a*4 < b){
            cout << (k/4) * a*4 + n%4 * a;
        }
		else 
        	cout << k/4*b + k%4*a;
    return 0;
}