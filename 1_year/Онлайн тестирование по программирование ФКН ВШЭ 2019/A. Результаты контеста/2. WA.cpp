#include <iostream>
#include <vector>
#include <algorithm>

using namespace std;

int main() {
    int a,b,n;
    cin >> a >> b >> n;
        if(a/n > b/n){
            cout << "YES";
        }
        else{        
            cout << "NO";
        }
    return 0;
}