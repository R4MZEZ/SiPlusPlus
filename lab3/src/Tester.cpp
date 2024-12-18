#include "Message.hpp"
#include <vector>
#include <stdio.h>
#include <list>
#include <iostream>
#include <algorithm>
#include <numeric>

int main() {
    // 1. Создание вектора v1 с 500-1000 случайных элементов
    std::vector<Message> v1;
    unsigned size_v1 = 500 + rand() % 501; // Генерация размера вектора от 500 до 1000
    v1.reserve(size_v1);

    for (unsigned i = 0; i < size_v1; ++i) {
        v1.push_back(Message(rand() % 100 + 1)); // случайные элементы
    }

    // 2. Создание вектора v2, содержащего последние 200 элементов из v1
    std::vector<Message> v2(v1.end() - 200, v1.end());

    // 3. Создание списка list1 с n наибольших элементов из v1
    std::sort(v1.begin(), v1.end(), [](const Message& m1, const Message& m2) {
        return m1.getSize() > m2.getSize(); // Сортировка по размеру
    });

    unsigned n = 30;
    std::list<Message> list1(v1.begin(), v1.begin() + n);

    // 4. Создание списка list2 с n наименьших элементов из v2
	std::sort(v2.begin(), v2.end(), [](const Message& m1, const Message& m2) {
        return m1.getSize() > m2.getSize(); // Сортировка по размеру
    });

    std::list<Message> list2(v2.end() - n, v2.end());

    // 5. Удаление перемещенных элементов из v1 и v2
    v1.erase(v1.begin(), v1.begin() + n);
    v2.erase(v2.end() - n, v2.end());

    // 6. Перегруппировка элементов в list1 по среднему значению
	int total_size = std::accumulate(list1.begin(), list1.end(), 0, [](int sum, const Message& m) {
		return sum + m.getSize();
	});
	int avg = total_size / list1.size();

    list1.sort([avg](const Message& m1, const Message& m2) {
        return m1.getSize() > avg; // Все элементы больше среднего значения в начале
    });

    // 7. Удаление нечётных элементов из list2
    list2.remove_if([](const Message& m) {
        return m.getSize() % 2 != 0; // Удаление нечётных элементов
    });

    // 8. Создание вектора v3 из общих элементов v1 и v2
    std::vector<Message> v3;
    std::set_intersection(v1.begin(), v1.end(), v2.begin(), v2.end(), std::back_inserter(v3));

    // 9. Формирование списка list3 из пар элементов list1 и list2
	size_t min_size = std::min(list1.size(), list2.size());
	if (list1.size() > min_size) {
		auto it = list1.begin();
		std::advance(it, list1.size() - min_size);
		list1.erase(list1.begin(), it);
	}else if (list2.size() > min_size) {
		auto it = list2.begin();
		std::advance(it, list2.size() - min_size);
		list2.erase(list2.begin(), it);
	}
    std::list<std::pair<Message, Message>> list3;
	std::transform(list1.begin(), list1.end(), list2.begin(), std::back_inserter(list3),
		[](const Message& m1, const Message& m2) {
			return std::make_pair(m1, m2);
		});
    // 10. Создание списка пар для векторов v1 и v2
    std::vector<std::pair<Message, Message>> v3_pairs;

	std::transform(v1.begin(), v1.begin() + std::min(v1.size(), v2.size()), 
               v2.begin(), 
               std::back_inserter(v3_pairs), 
               [](const Message& m1, const Message& m2) {
                   return std::make_pair(m1, m2);
               });

    return 0;
}