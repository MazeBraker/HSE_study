X. Упаковка\*
=============

Ограничение времени

1 секунда

Ограничение памяти

64Mb

Ввод

стандартный ввод или input.txt

Вывод

стандартный вывод или output.txt

В одну транспортную компанию поступил заказ на перевозку двух ящиков из одного города в другой. Для перевозки ящики решено было упаковать в специальный контейнер.

Ящики и контейнер имеют вид прямоугольных параллелепипедов. Длина, ширина и высота первого ящика — l1, w1 и h1, соответствующие размеры второго ящика – l2, w2 и h2. Контейнер имеет длину, ширину и высоту lc, wc и hc.

Поскольку ящики содержат хрупкое оборудование, после упаковки в контейнер каждый из них должен остаться в строго вертикальном положении. Таким образом, ящики можно разместить рядом или один на другом. Для надежного закрепления в контейнере стороны ящиков должны быть параллельны его сторонам. Иначе говоря, если исходно ящики были расположены так, что все их стороны параллельны соответствующим сторонам контейнера, то каждый из них разрешается перемещать и поворачивать относительно вертикальной оси на угол, кратный 90 градусам.

Разумеется, после упаковки оба ящика должны полностью находиться внутри контейнера и не должны пересекаться.

Выясните, можно ли поместить ящики в контейнер с соблюдением указанных условий.

Формат ввода
------------

Первая строка входных данных содержит l1, w1 и h1, вторая — l2, w2 и h2, третья – lc, wc и hc. Все размеры — целые положительные числа, не превышающие 1000. Числа в строках разделены пробелами.

### Пример 1

Ввод

Вывод

2
2
3
3
3
3
3
5
3

YES

### Пример 2

Ввод

Вывод

2
3
3
3
2
3
4
4
4

YES

### Пример 3

Ввод

Вывод

4
1
2
3
3
2
4
3
4

YES

### Пример 4

Ввод

Вывод

1
1
4
1
1
3
10
10
3

NO

### Пример 5

Ввод

Вывод

3
2
2
3
1
2
5
2
3

NO