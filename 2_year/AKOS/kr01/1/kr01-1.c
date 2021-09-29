#include <stdio.h>
#include <math.h>
#include <string.h>
#include <inttypes.h>
#include <ctype.h>

int main()
{
    //string S1;
    //string S2;
    // меньше 64
    char S1 [256] , S2 [256];
    scanf ( "%s\n%s" ,  S1 , S2 );
    printf("[Login:%s,Password:%s]", S1, S2);
    printf("\n");
    return 0;
}