#include "Employee.h"

Employee::Employee(const Employee &e)
{
    if (this == &e || &e == nullptr)
        return;

    *this = e;
}

Employee& Employee::operator=(const Employee &e)
{
    if(this == &e || &e == nullptr)
        return *this;

    id = e.id;

    f_name = e.f_name;
    l_name = e.l_name;

    age = e.age;

    department = e.department;
    salary = e.salary;

    return *this;
}

void Employee::SetSalary(int s)
{
    salary = s;
}

void Employee::SetDepartment(string dept)
{
    department = dept;
}

void Employee::SetId(int n)
{
    id = n;
}

int Employee::GetId()
{
    return id;
}

string Employee::GetDepartment()
{
    return department;
}

void Employee::Display(bool subordinate)
{
    if (subordinate)
    {
        cout << "Employee type: employee" << endl;
        cout << "id: " << id << endl;
        cout << f_name << " " << l_name << ", age: " << age << ", salary: " << salary << endl;
        cout << "department: " << department << endl << endl;
        return;
    }

    cout << "\t" << "Employee type: employee" << endl;
    cout << "\t" << "id: " << id << endl;
    cout << "\t" << f_name << " " << l_name << ", age: " << age << ", salary: " << salary << endl << endl;
}