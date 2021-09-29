#include <stdio.h>
#include <fcntl.h>
#include <unistd.h>
#include <stdlib.h>
#include <limits.h>
#include <sys/types.h>
#include <sys/stat.h>

int main(int argc, char *argv[])
{
    int file = open(argv[1], O_RDONLY);
    if(file < 0) {
        exit(1);
    }
    
    unsigned short max3 = 0, h_byte = 0, l_byte = 0, ans = 0;
    int cnt = 0;
    // считываю число 16-битные беззнаковые целые числа в представлении Big Endian в бинарном виде.
    while(read(file, &h_byte, 1) > 0 && read(file, &l_byte, 1) > 0) {
        ans = (h_byte << 8);  //CHAR_BIT, USHRT_MAX
        ans += l_byte;

        if (ans % 3 == 0) {
            if (ans >= max3) {
                cnt = 1;
                max3 = ans;
            }
        }
    }
    // Если в файле отсутствуют такие числа, программа не должна выводить ничего.
    if(cnt) {
        printf("%hu\n", max3);
    }
    close(file);
    return 0;
}