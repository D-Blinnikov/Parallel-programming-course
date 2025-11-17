CC = g++
CFLAGS = -Wall -O2 -fopenmp
TARGET = task

# дефолтно параллельный режим, 4 потока
DFLAGS ?= -DPARALLEL -DNUM_THREADS=4

all: $(TARGET)

$(TARGET): main.cpp
	$(CC) $(CFLAGS) $(DFLAGS) main.cpp -o $(TARGET)

parallel: DFLAGS = -DPARALLEL -DNUM_THREADS=4
parallel: clean $(TARGET)
	@echo "PARALLEL (4 threads)"
	./$(TARGET)

linear: DFLAGS = -DLINEAR
linear: clean $(TARGET)
	@echo "LINEAR"
	./$(TARGET)

threads: DFLAGS = -DPARALLEL -DNUM_THREADS=$(T)
threads: clean $(TARGET)
	@echo "PARALLEL with $(T) threads"
	./$(TARGET)

clean:
	rm -f $(TARGET)

.PHONY: all parallel linear threads clean
