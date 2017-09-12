TARGET = program1
CFLAGS = -Wall -Wextra -DDEBUG -g -pedantic -std=c++14
SOURCE = program1.cpp TuringMachine.h TuringMachine.cpp Makefile

all: $(TARGET)

$(TARGET): $(TARGET).o TuringMachine.o
	g++ $(TARGET).o TuringMachine.o -o $(TARGET)

$(TARGET).o: $(TARGET).cpp 
	g++ $(CFLAGS) -c $(TARGET).cpp -o $(TARGET).o

TuringMachine.o: TuringMachine.cpp
	g++ $(CFLAGS) -c TuringMachine.cpp -o TuringMachine.o

run: all
	./$(TARGET) program1.txt 000111 500

checkmem: all
	valgrind ./$(TARGET)

clean:
	-rm *.o $(TARGET)

zip:
	make clean
	zip -r program1 $(SOURCE)
