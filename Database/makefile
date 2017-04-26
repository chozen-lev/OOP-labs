TARGET = lab2

.PHONY: all clean

all: $(TARGET)
	
clean:
	rm -rf $(TARGET) *.o

main.o: main.cpp Employee.h Manager.h Database.h
	g++ -std=c++11 -o main.o -c main.cpp

Employee.o: Employee.cpp Employee.h
	g++ -std=c++11 -o Employee.o -c Employee.cpp

Manager.o: Manager.cpp Manager.h
	g++ -std=c++11 -o Manager.o -c Manager.cpp

Database.o: Database.cpp Database.h
	g++ -std=c++11 -o Database.o -c Database.cpp

$(TARGET): main.o Employee.o Manager.o Database.o
	g++ main.o Employee.o Manager.o Database.o -o $(TARGET)