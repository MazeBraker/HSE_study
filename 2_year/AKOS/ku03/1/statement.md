|                      |       |
|----------------------|-------|
| **Time limit:**      | `1 s` |
| **Real time limit:** | `5 s` |
| **Memory limit:**    | `64M` |


### Problem ku03-1: kr03-1 (дореш)

В аргументах командной строки передаются строки, состоящие только из цифр девятеричной системы
счисления (то есть от ‘0’ до ‘8’ включительно). Конкатенация всех аргументов командной строки, кроме
имени программы рассматривается как "перевернутая" запись одного числа в девятеричной системе
счисления. На стандартный поток вывода напечатайте остаток от деления этого числа на 7.

Если конкатенация представляет собой пустую строку, выводите 0.

Пример запуска программы:

    
    
    ./solution 22 33 44

Конкатенация всех аргументов дает `223344`, соответствующее число в девятеричной записи будет
`443322`, что соответствует десятичному числу 264890, дающему при делении на 7 остаток 3.

Результат работы программы:

    
    
    3

