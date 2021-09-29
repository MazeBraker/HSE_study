.text
        .global forward.args
forward.args:
        // стандартный пролог
        pushl   %ebp
        movl    %esp, %ebp

        // читаем int v1 кладем на стэк в обратном порядке
        pushl   8(%ebp)

        // int v3
        pushl   20(%ebp)

        //читаем long long v2
        pushl   16(%ebp)
        pushl   12(%ebp)

        call    process
        //меняем знак результата
        negl    %eax
        //выравнивание стэка по 16
        addl    $16, %esp
        //стандартный эпилог
        pop     %ebp
        ret