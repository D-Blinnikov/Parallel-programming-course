CC = g++
CFLAGS = -Wall -O2 -pthread
TARGET = task

# По умолчанию: параллельная, 4 потока
DFLAGS ?= -DPARALLEL -DNUM_THREADS=4

all: $(TARGET)

$(TARGET): main.cpp
	$(CC) $(CFLAGS) $(DFLAGS) main.cpp -o $(TARGET)

clean:
	rm -f $(TARGET)