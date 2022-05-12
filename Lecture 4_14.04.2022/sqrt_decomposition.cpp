#include <iostream>
#include <vector>


int main() {
    int sz = 4; // Корень размера исходного вектора — должно быть целое число
    std::vector<int> v = {1, 7, 2, 3, 7, 3, 8, 1, 2, 6, 7, 3, 4, 9, 3, 2}; // исходный вектор
    std::vector<int> b(4, 0); // вспомогательный вектор
    for (size_t i = 0; i < v.size(); ++i) {
        b[i / sz] += v[i]; // ищем сумму на подотрезке
    }
    int l = 1, r = 12; // запрос на сумму на полуинтервале [l, r)
    int s = 0; // переменная для ответа
    while (l < r) {
        if (l % sz == 0 && l + sz < r) { // условие для добавления к сумме целого блока
            s += b[l / sz];
            l += sz;
        } else { // иначе добавляем поэлементно
            s += v[l];
            ++l;
        }
    }
    std::cout << s;
    return 0;
}
