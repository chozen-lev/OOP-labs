#pragma once

#include "BinTree.h"

class TrainStationDatabase
{
public:
    TrainStationDatabase(const std::string file_path);
    ~TrainStationDatabase() {};

    void print();
    void print(int);
    void print(const std::string);
    void deleteTrain(int);
private:
    BinTree db;
};
