#include "TrainStationDatabase.h"
#include <iostream>
#include <fstream>

TrainStationDatabase::TrainStationDatabase(const std::string file_path)
{
    std::ifstream File(file_path);

    if (!File)
    {
        std::cerr << "File could not be opened" << std::endl;
        exit(1);
    }

    int number;
    std::string dest, time;
    char divider;

    while (File >> number)
    {
        File >> divider;
        getline(File, dest, ';');
        getline(File, time);

        db.addNode(new TreeNode(number, dest, time));
    }

    File.close();
}

void TrainStationDatabase::print()
{
    std::cout << "List of available trains: " << std::endl << std::endl;
    db.print();
}

void TrainStationDatabase::print(int number) {

    std::cout << "Information about train number " << number << ":" << std::endl << std::endl;

    TreeNode* p = db.find(number);

    if (p != nullptr) {
        p->print();
    }
    else {
        std::cout << "Train with such number doesn't exist" << std::endl << std::endl;
    }
}

void TrainStationDatabase::print(const std::string dest) {

    std::cout << "Trains that follow to " << dest << ":" << std::endl << std::endl;
    db.print(dest);
}

void TrainStationDatabase::deleteTrain(int number)
{
    if (!db.removeNode(number)) {
        std::cout << "Can't be deleted because train with such number doesn't exist" << std::endl << std::endl;
        return;
    }

    std::cout << "Train with number " << number << " was deleted" << std::endl << std::endl;
}