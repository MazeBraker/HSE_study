#include <stdio.h>
#include <unistd.h>
#include <stdio.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <fcntl.h>
#include <fcntl.h>
#include <inttypes.h>
#include <signal.h>
#include <stdio.h>
#include <stdlib.h>
#include <sys/stat.h>
#include <sys/types.h>
#include <sys/wait.h>
#include <unistd.h>


int main(int argc, const char *argv[]){ 
    int n = argc - 1; // кроме названия проги
    
    if (n < 1) {
        exit(0);
    }
    
    pid_t cpids[n + 1];
    
    cpids[0] = getpid();
    
    for (int i = 1; i < n + 1; ++i) {
        pid_t pid = fork();
        cpids[i] = pid;
        if (pid == -1) {
            /* неполучилось */
            exit(1);
        } else if (pid == 0) {
            int digit, res = 0;
            int64_t num = strtoll(argv[i], NULL, 10);
            while (num != 0) {
                digit = num % 4;
                if (digit < 0) { // если минус то, *-1 = +
                    digit *= -1;
                }
                num /= 4;
                res += digit;
            }
            exit(res);
        }
    }
    // запускаемся кол-во аргументов раз подряд
    for (int i = 1; i < n + 1; ++i) {
        int wstatus;
        waitpid(cpids[i], &wstatus, 0);
        printf("%d\n", WEXITSTATUS(wstatus)); // здесь печатаем res
    }
    return 0;
}