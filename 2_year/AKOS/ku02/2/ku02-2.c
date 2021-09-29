#include <stdio.h>
#include <stdlib.h>
#include <string.h>

int main(int argc, char *argv[]) 
{ 
    char *p;
    long long a, neg = 0, pos = 0;
    //int count1 = 0, count2 = 0;

    for (int i = 1; i < argc; i++){
        a = strtoll(argv[i], &p, 10);
        if (a > 0){
            pos += a;
            //count1++;
        } 
        if(a < 0){
            //count2++;
            neg += a;
        }
    }
    /*if (count1 == 0 && count2 == 0){
        printf("%d\n", count1);
    } */
    //else{
        printf ("%lld\n", pos);
        printf ("%lld\n", neg);
    //} 
    return 0; 
} 
