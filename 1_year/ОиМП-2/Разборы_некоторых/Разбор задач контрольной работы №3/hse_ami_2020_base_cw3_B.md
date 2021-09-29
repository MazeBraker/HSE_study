## Разбор задачи «Крестики-нолики»

### Условие
Один студент решил написать класс для своей реализации игры «крестики-нолики».
Игра ведётся на квадратном поле размера N × N двумя игроками.
Игроки должны составить K крестиков или ноликов в ряд (по горизонтали, по вертикали или по диагонали).

Класс должен уметь создавать квадратное поле заданных размеров, выполнять очередной ход в пустую клетку, а также проверять, не наступил ли выигрыш.
Кроме того, должен быть оператор `<<`, который печатает поле.

Студент пока не реализовал проверку выигрыша по диагоналям.
А ещё его программа почему-то «падает» при попытке напечатать поле.
Помогите ему исправить и сдать программу. Вот код студента:
```cpp
#include <iostream>
#include <vector>

class TicTacToe {
public:
  const size_t N;  // размер игрового поля
  const size_t K;  // сколько фишек нужно поставить в ряд, чтобы выиграть

private:
  // 0 - пусто, 1 - фишка первого игрока (крестик), 2 - фишка второго игрока (нолик)
  std::vector<std::vector<int>> Table;

  // номер текущего игрока (1 или 2)
  int CurrentPlayer;

public:
  TicTacToe(size_t n, size_t k): N(n), K(k), CurrentPlayer(1) {
    Table.reserve(N);
    for (size_t i = 0; i != N; ++i)
      Table[i].reserve(N);
  }

  int operator()(size_t i, size_t j) const {
    return Table[i][j];
  }

  int GetCurrentPlayer() const {
    return CurrentPlayer;
  }

  bool Set(size_t i, size_t j) {  // возвращает true, если ход завершился выигрышем
    Table[i][j] = CurrentPlayer;
    CurrentPlayer = CurrentPlayer % 2 + 1;
    bool wins = CheckRow(i, j)
      || CheckColumn(i, j)
      || CheckDiagonal1(i, j)
      || CheckDiagonal2(i, j);
    return wins;
  }

private:
  bool CheckRow(size_t i, size_t j) const {
    size_t d1 = 0;
    while (d1 <= j && Table[i][j-d1] == Table[i][j])
      ++d1;
    size_t d2 = 0;
    while (j + d2 < N && Table[i][j+d2] == Table[i][j])
      ++d2;
    return d1 + d2 > K;
  }

  bool CheckColumn(size_t i, size_t j) const {
    size_t d1 = 0;
    while (d1 <= i && Table[i-d1][j] == Table[i][j])
      ++d1;
    size_t d2 = 0;
    while (i + d2 < N && Table[i+d2][j] == Table[i][j])
      ++d2;
    return d1 + d2 > K;
  }

  bool CheckDiagonal1(size_t i, size_t j) const;

  bool CheckDiagonal2(size_t i, size_t j) const;
};

std::ostream& operator << (std::ostream& out, TicTacToe& field) {
  for (size_t i = 0; i != field.N; ++i) {
    for (size_t j = 0; j != field.N; ++j) {
      switch (field(i, j)) {
      case 0:
        std::cout << '.';
        break;
      case 1:
        std::cout << 'X';
        break;
      case 2:
        std::cout << 'O';
      }
    }
    std::cout << "\n";
  }
  return out;
}
```

Вам требуется сдать только исправленный (и дополненный для проверки выигрыша по диагоналям) код класса `TicTacToe` и оператора `<<`.
Функции `main` в Вашем коде быть не должно.
Ваша программа будет автоматически собрана с нашей функцией `main` примерно такого содержания:
```cpp
#include "tic_tac_toe.correct.h"
#include <iostream>

int main() {
  size_t N, M;
  std::cin >> N >> M;
  TicTacToe game(N, M);
  size_t x, y;
  while (std::cin >> x >> y) {
    int curPlayer = game.GetCurrentPlayer();
    if (game.Set(x, y))
      std::cout << "Player #" << curPlayer << " wins!\n";
  }
  std::cout << game;
}
```

### Решение
Прежде всего заметим, что неверно написан конструктор.
В нём лишь резервируется память для вектора, но не меняется его размер. Перепишем его так:
```cpp
TicTacToe(size_t n, size_t k): N(n), K(k), CurrentPlayer(1) {
  Table.resize(N);
  for (size_t i = 0; i != N; ++i)
    Table[i].resize(N);
}
```

Во-вторых, в операторе `<<` есть две ошибки: ответ печатается в `std::cout` вместо `out`, и второй аргумент принимается по обычной, а не по константной ссылке.
(В тестах, увы, не проверялась корректность выбранного потока вывода. Поэтому решения, где `std::cout` не было исправлено на `out`, проходили.)

Наконец, нам нужно реализовать функции `CheckDiagonal1` и `CheckDiagonal2`.
Вопреки заблуждению некоторых студентов, видимо, много решавших задачи про матрицы, диагональ тут (как в самых обычных крестиках-ноликах) может быть любая, а не только главная или побочная.
Рассмотрим, как сделана, например, аналогичная функция `CheckRow`, проверяющая, образуется ли `K` подряд идущих фишек по горизонтали после хода в указанную позицию:
```cpp
bool CheckRow(size_t i, size_t j) const {
  size_t d1 = 0;
  while (d1 <= j && Table[i][j-d1] == Table[i][j])  // считаем, сколько слева от нас таких же фишек
    ++d1;
  size_t d2 = 0;
  while (j + d2 < N && Table[i][j+d2] == Table[i][j])  // считаем, сколько справа от нас таких же фишек
    ++d2;
  return d1 + d2 > K;  // всего мы насчитали d1 + 1 + d2 фишек вместе с текущей, это число должно быть не меньше K
}
```
Тут важно проверять корректности индексов: они должны быть неотрицательны и меньше `N`.
Напишем по аналогии проверку наличия диагональных выигрышных позиций:
```cpp
bool CheckDiagonal1(size_t i, size_t j) const {
  size_t d1 = 0;
  while (d1 <= i && d1 <= j && Table[i-d1][j-d1] == Table[i][j])
    ++d1;
  size_t d2 = 0;
  while (i + d2 < N && j + d2 < N && Table[i+d2][j+d2] == Table[i][j])
    ++d2;
  return d1 + d2 > K;
}

bool CheckDiagonal2(size_t i, size_t j) const {
  size_t d1 = 0;
  while (d1 <= i && j + d1 < N && Table[i-d1][j+d1] == Table[i][j])
    ++d1;
  size_t d2 = 0;
  while (i + d2 < N && d2 <= j && Table[i+d2][j-d2] == Table[i][j])
    ++d2;
  return d1 + d2 > K;
}
```