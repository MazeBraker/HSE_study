.att_syntax
       .data
       .global парам
   парам:  .int 1
       .global тарам
   тарам:  .int 2
       .global пампам
   пампам: .int 4
       .text
       .global обработка
   обработка:
      push %ebp
      movl %esp, %ebp
      push %edi
      push %esi
      movl парам, %eax
      mull %ecx
      //subl $1, %ecx
      decl %ecx
      mull %ecx
      movl %eax, %esi
      movl тарам, %eax
      //addl $1, %ecx
      incl %ecx
      mull %ecx
      movl пампам, %edi
      // деление
      shrl $2, %edi
      subl %edi, %eax
      addl %eax, %esi
      movl %esi, %ecx
      //стандартный эпилог
      pop %esi
      pop %edi
      pop %ebp
      ret