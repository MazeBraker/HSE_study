|                      |       |
|----------------------|-------|
| **Time limit:**      | `1 s` |
| **Real time limit:** | `5 s` |
| **Memory limit:**    | `64M` |


### Problem ku02-3: ku02-3 (дореш)

На стандартном потоке ввода вводится 8 чисел от 0 до 7, каждое из чисел встречается ровно один раз.
Эти числа задают перестановку бит в байте. Например, последовательность 4, 3, 2, 1, 0, 7, 6, 5
означает, что бит 0 в байте должен быть переставлен на место бита 4, бит 1 - на место бита 3... бит
7 - на место бита 5.

Далее на стандартном потоке ввода идут числа от 0 до 255 (в десятичной записи). Для каждого числа
выполните заданную перестановку бит в числе и выведите результат в десятичном виде на стандартный
поток вывода.

### Examples

#### Input

    
    
    4 3 2 1 0 7 6 5
    78
    207

#### Output

    
    
    78
    126

