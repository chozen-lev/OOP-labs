#include "Database.h"

int main()
{
    Database db;
    db.LoadFromFile("input.csv");
    db.ArrangeSubordinates();
    db.DisplayAll();
    cout << "------------------------------" << endl;
    db.DisplayDepartmentEmployees("IT");
    cout << "------------------------------" << endl;
    db.FireEmployee(2);
    db.DisplayAll();
}