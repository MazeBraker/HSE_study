U. Семипроцентный барьер
========================

Ограничение времени

1 секунда

Ограничение памяти

64Mb

Ввод

стандартный ввод или input.txt

Вывод

стандартный вывод или output.txt

В Государственную Думу Федерального Собрания Российской Федерации выборы производятся по партийным спискам. Каждый избиратель указывает одну партию, за которую он отдает свой голос. В Государственную Думу попадают партии, которые набрали не менее 7% от числа голосов избирателей.

Дан список партий и список голосов избирателей. Выведите список партий, которые попадут в Государственную Думу.

Формат ввода
------------

В первой строке входного файла написано слово PARTIES:. Далее идет список партий, участвующих в выборах.

Затем идет строка, содержащая слово VOTES:. За ним идут названия партий, за которые проголосовали избиратели, по одному названию в строке. Названия могут быть только строками из первого списка.

Формат вывода
-------------

Программа должна вывести названия партий, получивших не менее 7% от числа голосов в том порядке, в котором они следуют в первом списке.

### Пример 1

Ввод

Вывод

PARTIES:
Party one
Party two
Party three
VOTES:
Party one
Party one
Party three
Party one
Party one
Party three
Party two
Party one
Party three
Party three
Party one
Party one
Party three
Party three
Party one

Party one
Party three

### Пример 2

Ввод

Вывод

PARTIES:
Party one
VOTES:
Party one
Party one
Party one
Party one
Party one
Party one
Party one

Party one

### Пример 3

Ввод

Вывод

PARTIES:
The first party
The best party
VOTES:
The best party
The best party
The best party
The best party
The best party
The best party
The best party
The first party
The best party
The best party
The best party
The best party
The best party
The best party

The first party
The best party