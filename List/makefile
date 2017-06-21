TARGET = lab4

.PHONY: all clean

all: $(TARGET)
	
clean:
	rm -rf $(TARGET) *.o

main.o: main.cpp List.h References.h Iterator.h
	icpc -c -o main.o main.cpp

References.o: References.cpp References.h List.h Iterator.h
	icpc -c -o References.o References.cpp

$(TARGET): main.o References.o
	icpc -o $(TARGET) main.o References.o