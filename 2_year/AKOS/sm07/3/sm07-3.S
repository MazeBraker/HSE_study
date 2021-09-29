.text
        .global main
main:
        call    readi32
        mov     %eax, %ebx
        cmpl    $0, %eax
        jge     rev_ord
        call    finish

rev_ord:
        mov     %ebx, %eax
        call    writei32
        call    nl
        decl    %ebx
        cmpl    $0, %ebx
        jge     rev_ord
        call    finish