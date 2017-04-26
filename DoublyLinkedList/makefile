TARGET = lab4

.PHONY: all clean

all: $(TARGET)
	
clean:
	rm -rf $(TARGET) *.o

main.o: main.cpp ListNode.h DoublyLinkedList.h
	g++ -std=c++11 -o main.o -c main.cpp

ListNode.o: ListNode.cpp ListNode.h
	g++ -std=c++11 -o ListNode.o -c ListNode.cpp

DoublyLinkedList.o: DoublyLinkedList.cpp DoublyLinkedList.h ListNode.h
	g++ -std=c++11 -o DoublyLinkedList.o -c DoublyLinkedList.cpp

$(TARGET): main.o ListNode.o DoublyLinkedList.o
	g++ main.o ListNode.o DoublyLinkedList.o -o $(TARGET)