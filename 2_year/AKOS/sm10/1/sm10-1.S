#include <asm/unistd_32.h>
        .text
        .global _start
_start:
        subl    $4, %esp
cycle:
        movl    $__NR_read, %eax // или $3, %eax, если заголовочный файл не найден
        movl    $0, %ebx  // первый аргумент (0 - стандартный поток ввода) в %ebx
        leal    (%esp), %ecx  // второй аргумент (адрес переменной c) в %ecx
        movl    $1, %edx  // третий аргумент (размер переменной c) в %edx
        int     $0x80  // в %eax будет возвращаемое значение read

        cmpl    $0, %eax
        je      end

        cmpl    $'0', (%esp)
        jl      print
        cmpl    $'9', (%esp)
        jg      print
        movl    $'0', (%esp)
print:
        movl    $__NR_write, %eax
        movl    $1, %ebx
        movl    %esp, %ecx
        //leal    (%esp), %ecx
        movl    $1, %edx
        int     $0x80
        jmp     cycle
end:
        movl    $__NR_exit, %eax
        xorl    %ebx, %ebx
        int     $0x80