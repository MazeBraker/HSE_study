O. Максимальный балл по классам
===============================

Ограничение времени

1 секунда

Ограничение памяти

64Mb

Ввод

стандартный ввод или input.txt

Вывод

стандартный вывод или output.txt

В олимпиаде по информатике принимало участие несколько человек. Победителем олимпиады становится человек, набравший больше всех баллов. Победители определяются независимо по каждому классу. Определите количество баллов, которое набрал победитель в каждом классе. Гарантируется, что в каждом классе был хотя бы один участник.

Формат ввода
------------

Информация о результатах олимпиады записана в файле, каждая строка которого имеет вид: фамилия имя класс балл.

Фамилия и имя — текстовые строки, не содержащие пробелов. Класс - одно из трех чисел 9, 10, 11. Балл - целое число от 0 до 100.

В этой задаче файл необходимо считывать построчно, не сохраняя содержимое файла в памяти целиком.

Формат вывода
-------------

Выведите три числа: баллы победителя олимпиады по 9 классу, по 10 классу, по 11 классу. Входной файл в кодировке utf-8 (В Python используйте open('input.txt', 'r', encoding='utf-8')).

### Пример 1

Ввод

Вывод

Иванов Сергей 9 90
Сергеев Петр 10 91
Петров Василий 11 92
Васильев Иван 9 93

93 91 92

### Пример 2

Ввод

Вывод

Егоров Павел 11 30
Кострикова Анна 9 49
Туаршев Тенгиз 9 91
Кузьмин Александр 11 99
Перочинская Виктория 11 53
Лебедев Дмитрий 11 29
Гольсков Алексей 11 92
Васильева Александра 11 41
Медведев Дмитрий 10 86
Аптараули Алексей 9 51

91 86 99

### Пример 3

Ввод

Вывод

Егоров Павел 9 0
Кострикова Анна 9 0
Туаршев Тенгиз 9 0
Кузьмин Александр 9 0
Перочинская Виктория 9 0
Лебедев Дмитрий 9 0
Гольсков Алексей 9 0
Васильева Александра 9 0
Медведев Дмитрий 10 0
Аптараули Алексей 11 0

0 0 0