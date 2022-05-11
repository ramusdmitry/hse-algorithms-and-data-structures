#include <iostream>
#include <algorithm>
#include <cmath>


struct Tree {
    // текущий макс:
    int64_t curr_max = -2e9; // сделает неявное приведение типов от double к int
    int64_t assign = 0;
    // ссылки на предыдущие ноды:
    Tree* left = 0;
    Tree* right = 0;
    // обслуживаемые границы:
    int left_bound = 0;
    int right_bound = 0;


    // конструктор:
    Tree(int left_bound, int right_bound) {
        this->left_bound = left_bound;
        this->right_bound = right_bound;
        if (left_bound + 1 < right_bound) {
            int mid = (left_bound + right_bound) / 2;
            this->left = new Tree(left_bound, mid);
            this->right = new Tree(mid, right_bound);
        }
    }
    // данный метод добавляет значение:
    void add(int id, int64_t value) {
        curr_max = std::max(curr_max, value);
        if (left != 0) { // мы не в "листе" (есть потомки)
            if (id < left->right_bound) { // обращаемся к потомку, смотрим его правую границу
                // передаём id, value — рекурсивно спускаемся:
                left->add(id, value);
            } else {
                right->add(id, value);
            }
        }
    }
    // —————
    void push() { // "пушим" вниз
        if (assign != 0) { // если 0 — ничего не накопилось, к данной вершине не надо ничего прибавлять
            curr_max += assign;
            // смотрим, есть ли левый потомок:
            if (left != 0) {
                // проталкиваем вниз, накапливаем "assign" в нодах-потомках:
                left->assign += assign;
                right->assign += assign;
            }
            assign = 0; // обнуляем после каждого очередного "пуша"
        }
    }


    void update(int left_query, int right_query, int64_t value) { // обновляем значeния на отрезке
        push(); // сначала проталкиваем вниз то, что уже накопилось
        if (left_query <= left_bound && right_bound <= right_query) { // наш отрезок, который обслуживает вершина, полностью принадлежит запросу на обновление
            assign += value; // накапливаем значение
            push(); // протолкнули ещё раз вниз
        } else if (left != 0 && std::max(left_bound, left_query) < std::min(right_bound, right_query)) { // проверям, есть потомки + проверяем, пересеклись ли отрезки
            // спускаемся вниз, к вершинам, которые покроют нужный отрезок:
            left->update(left_query, right_query, value);
            right->update(left_query, right_query, value);
            // обновляем максимум:
            curr_max = std::max(left->curr_max, right->curr_max);
        }
    }
    // —————

    int64_t get_max(int left_query, int right_query) {

        // —————
        push(); // не забываем перед каждым извлечением максимума делать push
        // —————

        if (left_query <= left_bound && right_bound <= right_query) { // отрезок вошёл в запрос
            return this->curr_max; // значение вершины
        } else if (std::max(left_bound, left_query) >= std::min(right_bound, right_query)) {
            return -2e9; // возвращаем -inf, если отрезки не пересекаются (допустим, пользователь задал границы, которые полностью превышают количество листьев в дереве
        } else {
            return std::max(left->get_max(left_query, right_query), right->get_max(left_query, right_query)); // передаём запрос ниже
        }
    }
};

int main() {
    std::ios_base::sync_with_stdio(0); // отключаем синхронизацию между потоками (C, C++) — std::cout, printf
    // не надо использовать C–шный и C++–овский ввод/вывод в одной программе -> но это ускоряет ввод-вывод
    std::cin.tie(NULL);
    int n = 0; // размер дерева
    int m = 0; // количество запросов
    int x = 0; // значение ноды
    int right_query = 0; // границы запросов — полуинтервалы начиная с 1
    int left_query = 0;
    std::cin >> n >> x;
    Tree* t = new Tree(1, n+1);
    for (size_t i = 1; i <= n; ++i) {
        t->add(i, 0);
    }
    std::cin >> m;
    for (size_t i = 1; i <= m; ++i) {
        std::cin >> left_query >> right_query;
        left_query += 1;
        right_query += 1;
        // важно следить за индексацией — в нашем решении она идёт с 1, а в задаче нам даются индексы с 0, поэтому мы к каждому числу прибавляем 1
        // далее важно учесть, что на последней станции человек не занимает место — поэтому в "checker" условие отправляем НЕ right_query + 1, как мы делали раньше
        if (x > t->get_max(left_query, right_query)) {
            // если места есть, добавляем пассажира на отрезок:
            t->update(left_query, right_query, 1);
            std::cout << 1 << std::endl;
        } else {
            std::cout << 0 << std::endl;
        }
    }
    return 0;
}
