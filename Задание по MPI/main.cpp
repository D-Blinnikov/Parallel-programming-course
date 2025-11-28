// номер 8
// 1) Паттерн: 
// Группы процессов и подкоммуникаторы
// Разделение MPI_COMM_WORLD на подгруппы с помощью
// MPI_Comm_split / MPI_Group_*.

// 2) int (32-bit)

// Задача: посчитать сумму массива чеез суммы разных частей массива 
// в двух группах процессов (четные и нечетные ранги)

// задача позволяетт показать, что можно создать несколько независимых процессов,
// разбить их на групапы, группы процессов независимо работают на своими задачами


#include <mpi.h>
#include <iostream>
#include <vector>
#include <numeric>

using namespace std;

int main(int argc, char* argv[]) {
    // дефолтное число процессов при запуске (указано в makefile) - 4
    MPI_Init(&argc, &argv);

    
    int world_rank, world_size;
    MPI_Comm_rank(MPI_COMM_WORLD, &world_rank);
    MPI_Comm_size(MPI_COMM_WORLD, &world_size);

 
    // не дублируем
    if (world_rank == 0) {
        cout << "----------" << endl;
        cout << "Student number: 8" << endl;
        cout << "Task: Sum parts of array using subcommunicators" << endl;
        cout << "Pattern: MPI_Comm_split (groups of processes)" << endl;
        cout << "----------" << endl;
    }

    const int N = 1000000;
    vector<int> data;

    // процесс 0 генерирует массив
    if (world_rank == 0) {
        data.resize(N);
        for (int i = 0; i < N; i++) data[i] = (i % 7) + 1;
    }

    // шарим массив всем процессам
    data.resize(N);
    MPI_Bcast(data.data(), N, MPI_INT, 0, MPI_COMM_WORLD);

    // создаем подкоммуникаторы: четные и нечетные ранги
    int color = world_rank % 2;
    MPI_Comm subcomm;
    MPI_Comm_split(MPI_COMM_WORLD, color, world_rank, &subcomm);

    int sub_rank, sub_size;
    MPI_Comm_rank(subcomm, &sub_rank);
    MPI_Comm_size(subcomm, &sub_size);

    // каждый процесс считает свою сумму части массива,
    // обрабатывая элементы с отступом в sub_size элементов
    long long local_sum = 0;
    for (int i = sub_rank; i < N; i += sub_size) {
        local_sum += data[i];
    }

    long long group_sum = 0;
    // суммируем независимо внутри групп, две группы процессов работают параллельно
    MPI_Reduce(&local_sum, &group_sum, 1, MPI_LONG_LONG, MPI_SUM, 0, subcomm);


    if (sub_rank == 0) {
        // отправляем свою сумму в процесс 0 глобального коммуникатора
        MPI_Send(&group_sum, 1, MPI_LONG_LONG, 0, 0, MPI_COMM_WORLD);
    }

    if (world_rank == 0) {
        long long total_sum = 0;
        long long recv;

        for (int i = 0; i < 2; i++) {
            MPI_Recv(&recv, 1, MPI_LONG_LONG, MPI_ANY_SOURCE, 0, MPI_COMM_WORLD, MPI_STATUS_IGNORE);
            total_sum += recv;
        }

        cout << "Total: " << total_sum << endl;
}

    MPI_Comm_free(&subcomm);
    MPI_Finalize();
    return 0;
}
