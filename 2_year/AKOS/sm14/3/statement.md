|                      |       |
|----------------------|-------|
| **Time limit:**      | `1 s` |
| **Real time limit:** | `5 s` |
| **Memory limit:**    | `64M` |


### Problem sm14-3: unix/mmap/count-lines-1

Программе в аргументах командной строки передаются пути к текстовым файлам. Для каждого файла
найдите и напечатайте на стандартный поток вывода число строк текста в этом файле. Каждое число
должно быть напечатано на отдельной строке.

Каждая строка текста в текстовом файле завершается символом '\n', кроме, возможно, последней
непустой строки. Если файл пуст, число строк в нем равно 0.

Если файл не существует, не может быть открыт или отображен в память выводите `-1`.

Для работы с содержимым файла используйте системный вызов `mmap`.

Обратите внимание, что поведение функции `mmap` не определено, если размер файла равен 0.

