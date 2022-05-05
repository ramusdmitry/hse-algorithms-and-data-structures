## Быстрое возведение в степень

Возводить в степень можно гораздо быстрее, чем за _n_ умножений! Для этого нужно воспользоваться следующими рекуррентными соотношениями:

_a_ ^ _n_ = (_a_ ^ 2) ^ (_n_ / 2) при четном _n_,

_a_ ^ _n_ = _a_ * _a_ ^(_n_ − 1) при нечетном _n_.

Реализуйте алгоритм быстрого возведения в степень. Если вы все сделаете правильно, то сложность вашего алгоритма будет O(log _n_). <br></br>
### Формат ввода

Вводится действительное число _a_ и целое число _n_. <br></br>
### Формат вывода

Выведите ответ на задачу.
<br></br>
#### Пример 1

<ins>Ввод:</ins><br>
2<br>
1<br>

<ins>Вывод:</ins><br>
2
<br>
#### Пример 2

<ins>Ввод:</ins><br>
2<br>
2<br>

<ins>Вывод:</ins><br>
4
<br>
#### Пример 1

<ins>Ввод:</ins><br>
2<br>
3<br>

<ins>Вывод:</ins><br>
8
<br>