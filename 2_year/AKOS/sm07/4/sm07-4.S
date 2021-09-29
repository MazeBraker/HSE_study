.text
        .global main
main:
        xor     %ebx, %ecx
seq:
        call    readi32
        jc      prinf
        addl    %eax, %ebx
        jno     seq
        adcl    $0, %ecx
        movl    $0x7ffffffe, %ebx
        addl    %ecx, %ebx
prinf:
        movl    %ebx, %eax
        call    writei32
        call    nl
        call    finish