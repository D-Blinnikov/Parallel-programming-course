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
using namespace std::chrono;

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
    auto start_time = high_resolution_clock::now();
    auto start_time_ms = duration_cast<milliseconds>(start_time.time_since_epoch()).count();

    cout << "Start time: " << start_time_ms << " ms" << endl;
    
    vector<int> array = {
        4832915,  729104,  5628371,  1048293,  9183746,
        3719205,  2847561,  6739201,  4591823,  8273645,
        1928374,  5061829,  3749201,  9182736,  2638491,
        7482910,  3051827,  8192736,  4728193,  1563827,
        9201746,  3819205,  6748291,  2938471,  7582910,
        1047293,  5639201,  8192734,  3728192,  6574839,
        2918374,  4051829,  7382910,  1928374,  5061829,
        3749201,  9182736,  2638491,  7482910,  3051827,
        8192736,  4728193,  1563827,  9201746,  3819205,
        6748291,  2938471,  7582910,  1047293,  5639201,
        8192734,  3728192,  6574839,  2918374,  4051829,
        7382910,  1928374,  5061829,  3749201,  9182736,
        2638491,  7482910,  3051827,  8192736,  4728193,
        1563827,  9201746,  3819205,  6748291,  2938471,
        7582910,  1047293,  5639201,  8192734,  3728192,
        6574839,  2918374,  4051829,  7382910,  1928374,
        5061829,  3749201,  9182736,  2638491,  7482910,
        3051827,  8192736,  4728193,  1563827,  9201746,
        3819205,  6748291,  2938471,  7582910,  1047293
    };

    int array_max;

#ifdef LINEAR
    cout << "LINEAR mode" << endl;

    array_max = array[0];
    for (size_t i = 1; i < array.size(); ++i) {
        if (array[i] > array_max) {
            array_max = array[i];
        }
    }

#else
    cout << "PARALLEL mode with " << number_of_threads << " threads" << endl;

    // результаты работы потоков
    size_t chunk_size = array.size() / number_of_threads;
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

    array_max = array[0];

    // проходим по всем фьючерам и собираем результаты
    for (auto& fut : futures) {
        // синхронная операция
        int chunk_max = fut.get();

        lock_guard<mutex> lock(mtx);
        if (chunk_max > array_max) {
            array_max = chunk_max;
        }
    }
#endif

    auto end_time = high_resolution_clock::now();
    auto end_time_ms = duration_cast<milliseconds>(end_time.time_since_epoch()).count();

    cout << "End time: " << end_time_ms << " ms" << endl;

    auto duration_ms = end_time_ms - start_time_ms;

    cout << "Duration: " << duration_ms << " ms" << endl;

    cout << "Array max: " << array_max << endl;
    return 0;
}