// R = A*B - C*D
    .data
 A: .int 0
 B: .int 0
 C: .int 0
 D: .int 0
 R: .int 0
   
    .global A
    .global B
    .global C
    .global D
    .global R
    .text
    .global process

 process:  // cdecl call
    movl   (A), %eax
    //movl (B), %edx
    imull  (B)
    movl   %eax, R
    movl   (C), %eax     
    imull  (D)
    subl   %eax, R