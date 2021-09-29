//partial 1
#include <stdio.h>
#include <stdlib.h>

char *getline2(FILE *f) {
    char *line = NULL;
    char bytie = 0;
    int i = 0;
    while (fscanf(f, "%c", &bytie) != EOF) {
        line = (char *) (realloc(line, (i) * sizeof(bytie)));
        line[i] = bytie;
        if (bytie == '\n') {
            break;
        }
        i++;
    }
    if (i == 1 && bytie == ' ') {
        free (line);
        return NULL;
    }
    return line;
}
/*
int main(int argc, char *argv[])
{
    FILE *p = fopen("input.txt","r");
    char *stroka = getline2(p);
    printf("%s",stroka);
}*/