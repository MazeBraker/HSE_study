#include <iostream>
using namespace std;
int main(){
char n;
int a=0,b=0,c=0,d=0;
while(cin >> n)
{
if(n>='0' && n<='9')a=1;
if(n>='a' && n<='z')b=1;
if(n>='A' && n<='Z')c=1;
d++;
}
if(d>=8 && a==1 && b==1 && c==1)
        cout<<"YES";
    else cout<<"NO";
    
    return 0;
}