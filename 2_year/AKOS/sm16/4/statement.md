|                      |       |
|----------------------|-------|
| **Time limit:**      | `1 s` |
| **Real time limit:** | `5 s` |
| **Memory limit:**    | `64M` |


### Problem sm16-4: unix/processes/invoke-script-1

В аргументах командной строки передаются целые положительные числа произвольного размера. Число
передаваемых аргументов больше или равно 1. На стандартный поток вывода напечатайте произведение
этих чисел.

Для вычисления результата используйте скриптовый язык программирования, поддерживающий арифметику
произвольной точности, например, python, python3.

На языке python3 умножение двух чисел выглядит следующим образом:

    
    
    print(1*2)
    

Если записать эту программу в файл `apb.py` и запустить интерпретатор командой

    
    
    python3 apb.py

То на стандартном потоке вывода будет получен результат:

    
    
    2

Ваша программа должна создать скрипт, который не будет требовать никаких дополнительных входных
данных и при запуске выведет на стандартный поток вывода произведение чисел. При запуске команды на
выполнение из вашей программы не должно указываться явное имя интерпретатора, поэтому в скрипте
используйте запись `#!`.

Не создавайте новый процесс. Ваша программа может запускаться в произвольном рабочем каталоге.
Программа должна поддерживать возможность одновременной работы своих копий. Программа не должна
допускать возможность изменения скрипта другими пользователями. Скрипт должен удаляться после
выполнения.

Не используйте функции tmpnam, tmpnam_r, mktemp, mkstemp, tmpfile и аналогичные. В качестве пути к
каталогу временных файлов используйте значение переменной окружения XDG_RUNTIME_DIR, если эта
переменная не установлена, используйте значение переменной окружения TMPDIR, если и эта переменная
не установлена, используйте путь /tmp.

