TARGET = lab3

.PHONY: all clean

all: $(TARGET)
	
clean:
	rm -rf $(TARGET) *.o

main.o: main.cpp
	icpc -c -o main.o main.cpp

BinTree.o: BinTree.cpp BinTree.h
	icpc -c -o BinTree.o BinTree.cpp

TrainStationDatabase.o: TrainStationDatabase.cpp TrainStationDatabase.h
	icpc -c -o TrainStationDatabase.o TrainStationDatabase.cpp

TreeNode.o: TreeNode.cpp TreeNode.h
	icpc -c -o TreeNode.o TreeNode.cpp

$(TARGET): main.o BinTree.o TrainStationDatabase.o TreeNode.o
	icpc -o $(TARGET) main.o BinTree.o TrainStationDatabase.o TreeNode.o