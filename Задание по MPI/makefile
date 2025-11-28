CC = mpic++
CFLAGS = -Wall -O2 -fopenmp
TARGET = task

# дефолтное число процессов
P ?= 4

all: $(TARGET)

$(TARGET): main.cpp
	$(CC) $(CFLAGS) main.cpp -o $(TARGET)

run: clean $(TARGET)
	@echo "MPI run with $(P) processes"
	mpirun  -np $(P) ./$(TARGET)

# запуск с нестандартным числом процессов:
# make P=8 runp
runp: clean $(TARGET)
	@echo "MPI run with $(P) processes"
	mpirun -np $(P) ./$(TARGET)

clean:
	rm -f $(TARGET)

.PHONY: all run runp clean
