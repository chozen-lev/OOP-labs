TARGET = lab2

.PHONY: all clean

all: $(TARGET)
	
clean:
	rm -rf $(TARGET) *.o

mem_dispatcher_test.o: mem_dispatcher_test.c mem_dispatcher.h
	gcc -o mem_dispatcher_test.o -c mem_dispatcher_test.c

mem_dispatcher.o: mem_dispatcher.c mem_dispatcher.h
	gcc -o mem_dispatcher.o -c mem_dispatcher.c

$(TARGET): mem_dispatcher_test.o mem_dispatcher.o
	gcc mem_dispatcher_test.o mem_dispatcher.o -o $(TARGET)