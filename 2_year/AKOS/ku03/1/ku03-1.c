#include <string.h>
#include <stdio.h>
#include <stdlib.h>
#include <ctype.h>
#include <math.h>
#include <strings.h>
// оптимальное решение
int main(int argc, char*argv[]) {
    //остатки от 9^i mod 7
    int series[]={1,2,4};
    int index = 0;
    long long result = 0;
    for (int i = 1; i < argc; i++){
        for (int j = 0; argv[i][j] != '\0'; j++){
            char n = argv[i][j]-'0';
            //printf("%lld\n", num); 
            //printf("%lld\n", n); 
            result += n * series[index];
            //printf("%lld\n", result); 
            index = (index + 1) % 3;
            result %= 7;
    }
}
 if (result < 0){
      result = (result + 7) % 7;
 }
    printf("%lld\n", result%7);   
    return 0;
}