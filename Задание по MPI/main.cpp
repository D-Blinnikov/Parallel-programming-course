// номер 8
// Паттерн: группы процессов и подкоммуникаторы (MPI_Comm_split)
// Задача: посчитать суммы разных частей массива в двух группах (четные и нечетные ранги)


#include <mpi.h>
#include <iostream>
#include <vector>
#include <numeric>

using namespace std;

int main(int argc, char* argv[]) {
    MPI_Init(&argc, &argv);
    // std::ios::sync_with_stdio(false);
    // std::cout << std::unitbuf;

    // std::cout << std::unitbuf;    // отключает буферизацию для cout
    // // или так:
    // std::ios::sync_with_stdio(false);
    // std::cout << std::unitbuf;

    

    int world_rank, world_size;
    MPI_Comm_rank(MPI_COMM_WORLD, &world_rank);
    MPI_Comm_size(MPI_COMM_WORLD, &world_size);

    // чтобы не было повторения во всех процессах
    if (world_rank == 0) {
        cout << "----------" << endl;
        cout << "Student number: 8" << endl;
        cout << "Task: Sum parts of array using subcommunicators" << endl;
        cout << "Pattern: MPI_Comm_split (groups of processes)" << endl;
        cout << "----------" << endl;
    }

    // размер массива (для демонстрации)
    const int N = 1000000;
    vector<int> data;

    // только rank 0 создаёт массив
    if (world_rank == 0) {
        data.resize(N);
        for (int i = 0; i < N; i++) data[i] = (i % 7) + 1;
    }

    // шарим массив всем
    data.resize(N);
    MPI_Bcast(data.data(), N, MPI_INT, 0, MPI_COMM_WORLD);

    // Создаем подкоммуникаторы: четные и нечетные ранги
    int color = world_rank % 2;
    MPI_Comm subcomm;
    MPI_Comm_split(MPI_COMM_WORLD, color, world_rank, &subcomm);

    int sub_rank, sub_size;
    MPI_Comm_rank(subcomm, &sub_rank);
    MPI_Comm_size(subcomm, &sub_size);

    // каждый подкоммуникатор считает свою сумму,
    // обрабатывая элементы с отступом в sub_size элементов
    long long local_sum = 0;
    for (int i = sub_rank; i < N; i += sub_size) {
        local_sum += data[i];
    }

    // суммируем внутри группы
    long long group_sum = 0;
    MPI_Reduce(&local_sum, &group_sum, 1, MPI_LONG_LONG, MPI_SUM, 0, subcomm);

    // печатает результаты только главы групп (sub_rank == 0)
    if (sub_rank == 0) {
        cout << (color == 0 ? "[Group EVEN] " : "[Group ODD] ")
             << "sum = " << group_sum
             << ", processes = " << sub_size
             << endl;
    }

    MPI_Comm_free(&subcomm);
    MPI_Finalize();
    return 0;
}
