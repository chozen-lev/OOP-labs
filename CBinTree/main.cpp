#include <iostream>
#include "TrainStationDatabase.h"

int main()
{
    TrainStationDatabase db("input.csv");
    db.print();
    db.deleteTrain(567);
    db.print();
    db.print(567);
    db.print("Kyiv");

    db.print(173);
    return 0;
}
