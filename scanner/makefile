TARGET = lab3

.PHONY: all clean

all: $(TARGET)
	
clean:
	rm -rf $(TARGET) *.o *.idx *.dba *.txt

scanner_db.o: scanner_db.c scanner.h
	gcc -o scanner_db.o -c scanner_db.c

scanner.o: scanner.c scanner.h
	gcc -o scanner.o -c scanner.c

$(TARGET): scanner_db.o scanner.o
	gcc scanner_db.o scanner.o -o $(TARGET)