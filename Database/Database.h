#pragma once

#include "Manager.h"
#include <vector>

class Database
{
public:
    Database() {};
    ~Database() {}; // no need in destructor

    // creates “flat” database
    bool LoadFromFile(const char *file);

    // arranges "flat" database after loading from the file
    void ArrangeSubordinates();

    // hire a new employee
    Person* HireEmployee(Person *p);

    void DisplayDepartmentEmployees(string _department);    

    // fire the employee
    bool FireEmployee(int id);

    void DisplayAll();

    // Add here whatever you need

private:
    vector<Person *> employees;  
    vector<int> ids;

    bool ParseInfo(string, int &, int &, string &, string &, int &, string &, int &);
};