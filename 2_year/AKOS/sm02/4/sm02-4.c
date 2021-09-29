#include <ctype.h>
#include <inttypes.h>
#include <stdio.h>
//так как 16 числа приходят с слева направо двойками,то алгоритм такой:
//умножаем само число сразу на 16^2=2^8 и добавляем новое число->повторяем

int main() {
    unsigned int decimal = 0;
    int num, count = 0, hex_pair = 0;
    //(num)сразу считывет 16тичное и запоминает в 10
    //пока есть числа
    while (scanf("%x", &num) == 1) {
        // если уже 16,то ввод на новую строку переходит
        //пропускаем 16 смещение
        if ((count++) != 16) {
            if (count > 1) {
                hex_pair++;
                decimal <<= 8;
                decimal += num;
                if (hex_pair == 4) {
                    //печатаем только 4ки
                    printf("%u\n", decimal);
                    decimal = 0;
                    hex_pair = 0;
                }
            }
        } else {
            decimal <<= 8;
            decimal += num;
            printf("%u\n", decimal);
            count = 0;
            hex_pair = 0;
            decimal = 0;
        }
    }
    return 0;
}