//partial 20
#include <stdio.h>
#include <math.h>
#include <string.h>
#include <inttypes.h>
#include <ctype.h>

int main()
{
    // ssh bpmi19290@sandbox.ejudge.ru
    // [Login:bpmi19290,Password:uGjT4KolPeA4x91X]
    // scp /home/LOGIN/.ssh/id_rsa.pub bpmi19290@sandbox.ejudge.ru:ё
    // scp /Users/rinatgorbachev/.ssh/id_rsa.pub bpmi19290@sandbox.ejudge.ru:
    // ssh -v bpmi19290@sandbox.ejudge.ru exit 2> output.txt
    //string S1;
    //string S2;
    // меньше 64
    int x, max = 0;
    int last[3] = {0, 0, 0};
    int cnt = 0;
    while ((x = getchar())!= EOF){
        if (x < 'a' || x > 'z'){
            if (last[0] == 'a'){
                max = cnt;
            }
        last[0]=last[1]=last[2]=0;
    }
        else{
            last[0]=last[1];
            last[1]= last[2];
            last[2] = x;
            cnt++;
        }
        if (x <'a' || x > 'z'){
            if (last[0] == 'a' && max<cnt){
                max= cnt;
            }
            last[0]=last[1]=last[2]=0;
        }else{
            last[0]=last[1];
            last[1]= last[2];
            last[2] = x;
        }
    }
    printf("%d", max);
    return 0;
}