.text
        .global main
main:                           /* %esi is even sum, %edi is odd sum */
        xor     %esi, %esi
        xor     %edi, %edi
        jmp     seq
        
seq:    call    readi32
        jc      prinf
        mov     %eax, %ebx
        andl    $1, %eax
        test    %eax, %eax
        jz      chet
        jnz     nechet

prinf:  mov     %esi, %eax
        call    writei32
        call    nl
        mov     %edi, %eax
        call    writei32
        call    nl
        call    finish

nechet: add     %ebx, %edi
        jmp     seq
        
chet:   add     %ebx, %esi
        jmp     seq