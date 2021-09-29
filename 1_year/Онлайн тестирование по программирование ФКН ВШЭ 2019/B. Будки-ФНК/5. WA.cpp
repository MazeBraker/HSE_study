#include <iostream>
#include <vector>
#include <algorithm>

using namespace std;

int main() {
    int m,n,a,b;
    cin >> m >> n >> a >> b;
        if ( n <= m){
            cout << 0;
            return 0;
        }
        n = n - m;
        if (n%4 * a > b){
            cout << n/4 * b + b;
        }
        else if (a*4 < b){
            cout << (n/4) * b + n%4 * a;
        }
		else 
        	cout << n/4*b + n%4*a;
    return 0;
}