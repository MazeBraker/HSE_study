.text
        .global mystrcmp
mystrcmp:
//стандартный пролог
        push    %ebp
        mov     %esp, %ebp
        push    %esi
        push    %edi

        mov     8(%ebp), %esi
        mov     12(%ebp), %edi

start:     
//расширяет один байт до 32 бит с 24 ведущими
//  нули и копирует его 
        movzbl   (%esi), %eax
        movzbl   (%edi), %edx
//заходим на след букву
        addl     $1,  %esi
        addl     $1,  %edi
        sub      %edx, %eax
// если разность <0,то меняем флаг
        jne      exit
        testl    %edx, %edx
//флаг ZF, если не измен, то снова в старт
//иначе выход
        jne      start
 
exit:   
//стандартный эпилог
        pop     %edi
        pop     %esi
        pop     %ebp
        ret