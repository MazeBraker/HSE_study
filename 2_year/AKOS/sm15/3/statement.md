|                      |       |
|----------------------|-------|
| **Time limit:**      | `1 s` |
| **Real time limit:** | `5 s` |
| **Memory limit:**    | `64M` |


### Problem sm15-3: unix/processes/fork-5

На стандартном потоке ввода задается целое число _N_ ( _N_ > 0). Требуется создать _N - 1_ процессов
так, чтобы первый процесс (процесс-родитель) вывел на стандартный поток вывода число 1, второй
процесс (его сын) вывел на стандартный поток вывода число 2, третий процесс (сын сына) вывел 3 и так
далее.

Вывод должен быть таким, чтобы всегда на стандартном потоке вывода оказывалась последовательность 1
2 3 ... N, записанная в одну строку строго с одним пробелом между числами. В конце вывода должен
находиться символ \n. Дополнительные пробелы в начале или конце строки не допускаются. Для вывода
использовать средства высокого уровня.

Процесс-родитель должен завершаться самым последним из всех процессов.

Не используйте рекурсию!

