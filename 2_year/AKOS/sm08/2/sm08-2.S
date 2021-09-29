.text
        .global satsum
        
        
satsum:
	// стандартный пролог
        push    %ebp
        movl     %esp, %ebp

        mov     8(%ebp), %eax
        add     12(%ebp), %eax
        
        jnc     out
        // то есть регистр edx будет содержать 0, 
        // если eax >= 0 и 0xffffffff если eax < 0
        movl    $0, %eax
        not     %eax
        
        // стандартны эпилог
out:    pop    %ebp
        ret