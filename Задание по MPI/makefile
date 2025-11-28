CC = mpic++
CFLAGS = -Wall -O2 -fopenmp
TARGET = task

# дефолтное число процессов
P ?= 4

all: run

$(TARGET): main.cpp
	$(CC) $(CFLAGS) main.cpp -o $(TARGET)

run: clean $(TARGET)
	@echo "MPI run with $(P) processes"
	mpirun  -np $(P) ./$(TARGET)

runp: clean $(TARGET)
	@echo "MPI run with $(P) processes"
	mpirun -np $(P) ./$(TARGET)

clean:
	rm -f $(TARGET)

.PHONY: all run runp clean
