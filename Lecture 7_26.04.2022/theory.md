# Представление сетей в компьютере. Обход в глубину: связность, циклы, двудольность.

- Графом называется множество вершин и множество дуг, соединяющих эти вершины;
- Сетью (или взвешанным) называют граф, на дугах или вершинах которого определены какие-либо функции: расстояние, время, стоимость и тп.;
- Обозначение: G = {N, E, f(E)};
- Мы можем проиндексировать вершины (присвоить номера);
- Также можем добавить ориентацию рёбер стрелками (создать ор-граф);
- Длина пути: подсчёт значений (функции) ребер на пути;
- Формальные названия элементов:
  - Вершины/узлы графа (node, vertex);
  - Неориентированые дуги/рёбра (edge);
  - Ориентированные дуги (arc);
- Графы бывают связные и несвязные (1 или несколько компонент связности);
    <br></br>

<ins>Репрезентация графов:</ins>

_Матрица смежности:_
  - Проходя по столбцу, видим все входящие в вершину рёбра;
  - Проходя по строке, видим все исходящие рёбра;
  - Асимптотика:
    - Просмотр пары/ребра i->j — O(n);
    - Просмотр рёбер от i и до всех достижимых i->... — O(n) (проход целиком по строке);
    - От всех до всех ...->... — O(n^2) (проход по всем клеткам);
<img width="746" alt="Screenshot 2022-06-09 at 8 53 06" src="https://user-images.githubusercontent.com/101647250/172787710-59d2e2b0-5156-4d4a-bdbb-2597a0f0c82e.png">
<br>
    
_Матрица инцидентности:_
- m — количество дуг;
- По индексу ребра в 3 списках храним вершины to, from и вес ребра;
- Асимптотика:
  - Просмотр инцидентности вершины/пары — O(m) (надо пройтись по всему списку рёбер в худшем случае);
  - Просмотр рёбер от i и до всех достижимых i->... — O(m) (смотрим весь граф/все рёбра);
  - От всех до всех ...->... — O(m) (смотрим все рёбра);
<img width="800" alt="Screenshot 2022-06-09 at 8 53 15" src="https://user-images.githubusercontent.com/101647250/172787721-a9fe4efa-b98c-41f0-aa09-3aa66866a083.png">
<br>

_Список смежности:_
- Каждая вершина по соответвующему индексу хранит ссылку на все исходящие из неё вершины — т.е. в массиве g[v] храним список [k_1, k_2, ...] таких, что есть ребро v->k_i;
- Можно хранить `std::pair` для обозначения длины/веса дуги;
- Асимптотика:
  - Просмотр инцидентности вершины/пары — O(n) (O(1) для перемещения по индексу во внешнем контейнере, O(n) в худшем случае для прохода по подконтейнеру);
  - Просмотр рёбер от i и до всех достижимых i->... — O(n) (аналогично пункту 1);
  - От всех до всех ...->... — O(m) (суммарно в графе не больше m рёбер, а мы ровно столько ячеек и заполнили);
<img width="777" alt="Screenshot 2022-06-09 at 8 53 29" src="https://user-images.githubusercontent.com/101647250/172787725-380dd916-846e-4d5d-8a53-4148fd6a5ce9.png">
<br></br>

<ins>Задача обхода (раскраски) графа:</ins>
_Используется DFS_
- Задача: раскрасить или пометить все вершины, исходя из какой-то;
- Замечание:
  - Неориентированный граф;
  - Не гарантируется одна компонент связности;
- Можно написать алгоритм с помощью рекурсии, но это необязательно;
<br>
_Алгоритм:_
  1. Создаём стэк ("активных вершин"), храним там путь;
  2. Помечаем вершины, где побывали, и кладём их в стэк;
  3. При приходе в лист помечаем его и удаляем из стэка (откатываемся назад);
  4. Далее рассматриваем нераскрашенные исходящие из предыдущей вершины;
  5. Если новых исходящих вершин в какой-то момент больше нет, откатываемся назад, пока стэк не опустеет; 
- Каждая вершина в стэке побывала 1 раз;
- Если мы не будем "щупать" раскрашенные рёбра дважды, то сложность алгоритма будет O(n + m) ~ O(m) если m > n (где m — количество рёбер, n — количество вершин);
