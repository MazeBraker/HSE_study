#include <unistd.h>
#include <stdio.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <fcntl.h>
#include <sys/wait.h>
#include <errno.h>

int main(int argc, char const *argv[]) {
    if (argc != 4) {
        _exit(0);
    }

    pid_t pid;
    if (!(pid = fork())) {
        // ./prog wc in.txt out.txt
        const char *cmd = argv[1];
        const char *file1 = argv[2];
        const char *file2 = argv[3];

        int file_in = open(file1, O_RDONLY);
        int file_out = open(file2, O_WRONLY | O_CREAT | O_TRUNC, 0666);
        if (file_in >= 0 && file_out >= 0) {
            if (dup2(file_in, fileno(stdin)) >= 0 && dup2(file_out, fileno(stdout)) >= 0) {
                close(file_in);
                close(file_out);
                execlp(cmd, cmd, NULL);
                _exit(1);
            } else {
                return 0;
            }
        } else {
            return 0;
        }
    } else if (pid < 0) {
        return 0;
    }
    wait(NULL);
    _exit(0);
}
// #include <stdio.h>

// int main(){
// 	int a, b;
// 	int sum;
// 	scanf("%d %d", &a, &b);
// 	sum = a + b;
// 	printf("%d\n", sum);
// 	return 0;
// }