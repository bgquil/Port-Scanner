CC=g++

CFLAGS=-std=c++11

all: ; $(CC) $(CFLAGS) ./src/ParseHelper.cpp ./src/PortEntry.cpp ./src/portscan.cpp ./src/Scan.cpp ./src/ScanLog.cpp -o portscan.o
