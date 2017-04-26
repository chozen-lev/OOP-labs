#include "Manager.h"

Manager::Manager(const Manager &m)
{
    if (this == &m || &m == nullptr)
        return;

    *this = m;
}

Manager& Manager::operator=(const Manager &m)
{
    if (this == &m || &m == nullptr)
        return *this;

    id = m.id;

    f_name = m.f_name;
    l_name = m.l_name;

    age = m.age;

    department = m.department;
    salary = m.salary;

    subordinates = m.subordinates;

    return *this;
}

Person* Manager::AddSubordinate(Person *p)
{
    if (p == nullptr) {
        return nullptr;
    }

    for (list<Person *>::iterator it = subordinates.begin(); it != subordinates.end(); ++it)
    {
        if (dynamic_cast<Employee*>(*it)->GetId() == dynamic_cast<Employee*>(p)->GetId()) {
            return nullptr;
        }
    }

    if (dynamic_cast<Employee*>(p)->GetDepartment() != this->GetDepartment()) {
        dynamic_cast<Employee*>(p)->SetDepartment(this->GetDepartment());
    }

    subordinates.push_back(p);

    return p;
}

bool Manager::RemoveSubordinate(int id)
{
    if (id <= 0 || id > subordinates.size()) {
        return false;
    }

    list<Person *>::iterator it;

    for (it = subordinates.begin(); it != subordinates.end(); ++it)
    {
        if (dynamic_cast<Employee *>(*it)->GetId() == id)
        {
            subordinates.erase(it);
            break;
        }
    }

    return true;
}

void Manager::Display(bool subordinates)
{
    cout << "Employee type: manager\n";
    cout << "id: " << id << endl;
    cout << f_name << " " << l_name << ", age: " << age << ", salary: " << salary << endl;
    cout << "department: " << department << endl;

    if (subordinates)
    {
        cout << "Subordinates:" << endl;
        DisplaySubordinates();
        cout << endl;
    }
    else {
        cout << endl;
    }
}

void Manager::DisplaySubordinates()
{
    if (subordinates.empty())
    {
        cout << "\t\t" << "none" << endl;
        return;
    }

    for(list <Person *>::iterator it = subordinates.begin(); it != subordinates.end(); ++it) {
        (*it)->Display(false);
    }
}