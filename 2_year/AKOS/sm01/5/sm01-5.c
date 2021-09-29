// 5 прога
#include <stdio.h>
#include <ctype.h>
int main() {
    int a;
    int sum = 0;
    while ((a = getchar())!= EOF){
        //putchar(a);
        if(isdigit(a)){
            // гений:) - '0', а как еще можно?
            sum+= a - '0';
        }
    }
    printf("%d", sum);
    putchar('\n');
    return 0;
}