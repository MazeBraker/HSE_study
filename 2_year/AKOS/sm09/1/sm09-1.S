.text
        .global process 
pre_pro:
        .asciz  "%llu\n"
process:
        push    %ebp
        movl    %esp, %ebp
        
// subl    $16, %esp 
        movq    A, %xmm0
        movq    B, %xmm1
        psllq   $1, %xmm0
        psrlq   $1, %xmm1
        psubq   %xmm1, %xmm0
        subl    $8, %esp
        movq    %xmm0, (%esp)
        push    $pre_pro
        call    printf
        
        movl    %ebp, %esp
        popl    %ebp
        ret