//partial 60
#include <string.h>
#include <stdio.h>
#include <stdlib.h>
#include <ctype.h>
#include <math.h>
#include <strings.h>

int main(int argc, char*argv[]) {
    char str[10000];
    int sum = 0;
    char *p = str;
    for (int i = 0; i <argc; i++){
        //if(isdigit(argv[i])){
        if(isdigit(*p)){
            //sum += argc[i];
            strcat(p,str);
            sum += (*p)*9+sum;
            //sum = sum*9 +str[i];
            //strcpy(p)
        }
        //*p++ = argv[i][0];
        p++;
    }
    printf("%d\n", sum%7);    
    return 0;
}