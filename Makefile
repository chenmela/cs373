TARGET = chen_p1
CFLAGS = -Wall -Wextra -DDEBUG -g -pedantic -std=c++14
SOURCE = chen_p1.cpp TuringMachine.h TuringMachine.cpp Makefile

all: $(TARGET)

$(TARGET): $(TARGET).o TuringMachine.o
	g++ $(TARGET).o TuringMachine.o -o $(TARGET)

$(TARGET).o: $(TARGET).cpp 
	g++ $(CFLAGS) -c $(TARGET).cpp -o $(TARGET).o

TuringMachine.o: TuringMachine.cpp
	g++ $(CFLAGS) -c TuringMachine.cpp -o TuringMachine.o
