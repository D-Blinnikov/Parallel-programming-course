// номер 8

// 1) Найти максимум в массиве
// 3) Использование parallel for и reduction
// 1) int (32-bit)

#include <iostream>
#include <vector>
#include <cstdlib>
#include <ctime>
#include <omp.h>


using namespace std;

int main() {

    cout << "Student number: 8" << endl;
    cout << "Task: Find maximum in array" << endl;
    cout << "Method: parallel for + reduction(max)" << endl;
    cout << "Data type: int (32-bit)" << endl;

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

    for (size_t i = 0; i < array.size(); ++i) {
        array[i] = rand();
    }

    int max_val = array[0];

#ifdef PARALLEL
    cout << "Mode: PARALLEL" << endl;
    cout << "Threads: " << NUM_THREADS << endl;

    omp_set_num_threads(NUM_THREADS);

    #pragma omp parallel for reduction(max:max_val)
    for (size_t i = 0; i < N; i++) {
        if (arr[i] > max_val) {
            max_val = arr[i];
        }
    }

#elif defined(LINEAR)
    cout << "Mode: LINEAR" << endl;

    for (size_t i = 0; i < N; i++) {
        if (arr[i] > max_val) {
            max_val = arr[i];
        }
    }
#else
    cout << "ERROR: No mode selected (define PARALLEL or LINEAR)" << endl;
    return 1;
#endif

    cout << "Maximum: " << max_val << endl;

    return 0;
}
