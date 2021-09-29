#include <stdio.h>
#include <math.h>
#include <string.h>
#include <inttypes.h>
#include <ctype.h>

int main()
{
    //[Host:S1,Login:S2,Password:S3]
    //string S1;
    //string S2;
    // меньше 64
    char S1 [256] , S2 [256], S3[256];
    scanf ( "%s\n%s\n%s" ,  S1 , S2, S3 );
    printf("[Host:%s,Login:%s,Password:%s]", S1, S2, S3);
    printf("\n");
    // [Host:localhost,Login:misha,Password:secret]
    // [Host:localhost,Login:misha,Password:secret]
    return 0;
}