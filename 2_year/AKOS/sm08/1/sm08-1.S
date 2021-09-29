 .data
format:   .string "%d %d %d\n" // вывод 3 чисел
          .text
          .global print_fib
          
          
print_fib:
	// стандартный пролог
        push   %ebp
        mov    %esp, %ebp
        
         // первое A
        mov    A, %eax
        // а+б 1новое число
        add    B, %eax
        // перемещаем б
        mov    %eax, %ecx
        // новое число а+б+б
        add    B, %ecx
        mov    %ecx, %edx
        add    %eax, %edx
        push   %edx
        push   %ecx
        push   %eax
        push   $format  // положили на стек
        call   printf  // убрали со стекаЖ)
        add    $16, %esp  //32bit chisla
        
        mov    $0, %eax
        pop    %ebp  // стандартный эпилог
        ret   // возврат