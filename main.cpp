// номер 8

// 1) Найти максимум в массиве
// 3) реализовать при помощи mutex (без condition_variable), 
// возвращать из потоков значение через future/promise
// 1) int (32-bit)

#include <iostream>
#include <vector> 
#include <thread>
#include <future> 
#include <mutex> 

using namespace std;

const size_t number_of_threads = 4;

mutex mtx;  

// вспомогательная функция для поиска максимума в части массива
// чтобы лямбду не нагружать
int find_chunk_max(const vector<int>& array, size_t start, size_t end) {
    int chunk_max = array[start];
    for (size_t i = start + 1; i < end; ++i) {
        if (array[i] > chunk_max) {
            chunk_max = array[i];
        }
    }
    return chunk_max;
}

int main() {

    vector<int> array = {5, 12, 7, 87, 3, 15, 8, 10, 99, 12698654, 0 };

    size_t chunk_size = array.size() / number_of_threads;

    // результаты работы потоков
    vector<future<int>> futures;

    // запускаем по одной асинхронной задаче на каждый поток
    for (size_t i = 0; i < number_of_threads; ++i) {
        size_t start = i * chunk_size;

        size_t end = (i == number_of_threads - 1) ? array.size() : start + chunk_size;

        // launch::async - явно говорим, что нужны потоки
        futures.push_back(
            async(launch::async, [&, start, end]() {
                return find_chunk_max(array, start, end);
            })
        );
    }

    int array_max = array[0];

    // проходим по всем фьючерам и собираем результаты
    for (auto& fut : futures) {
        // синхронная операция
        int chunk_max = fut.get();

        if (chunk_max > array_max) {
            array_max = chunk_max;
        }
    }

    cout << "Array max: " << array_max << endl;

    return 0; 
}