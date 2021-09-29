#include <string.h>
#include <stdio.h>
#include <stdlib.h>
#include <ctype.h>
#include <math.h>

int main(int argc, char *argv[]) 
{ 
    int num = 0, bit = 0, newnum = 0;
    int pos;
    int bits[8], repbits[8], newbits[8];

    for(int i = 0; i<=7; i++){
            scanf("%d", &bit);
            repbits[i] = bit;
    }
    while(scanf("%d", &num) == 1){
        for(int j = 0; j <= 7; j++){
            if(num < pow(2,7-j)){
                bits[j]=0;
                continue;
            }
            else{
                bits[j]=1;
                num -= pow(2, 7-j);
            }
        }
        for(int k = 0; k <= 7; k++){
            pos = repbits[k];
            newbits[pos] = bits[7-k];
        }
        for(int f = 7; f >=0; f--){
            //printf("%d", newbits[i]);
            newnum += newbits[f] * pow(2,f);
        }
        printf("%d\n", newnum);
        newnum = 0;
    }
    return 0; 
} 