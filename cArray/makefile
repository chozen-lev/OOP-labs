TARGET = lab1

.PHONY: all clean

all: $(TARGET)
	
clean:
	rm -rf $(TARGET) *.o

main.o: main.cpp cArray.h
	g++ -std=c++11 -o main.o -c main.cpp

cArray.o: cArray.cpp cArray.h
	g++ -std=c++11 -o cArray.o -c cArray.cpp

$(TARGET): main.o cArray.o
	g++ main.o cArray.o -o $(TARGET)