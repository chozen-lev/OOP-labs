#include "Database.h"
#include <fstream>
#include <typeinfo>
#include <algorithm>

bool Database::LoadFromFile(const char *file)
{
    ifstream FileDB(file);

    if (!FileDB.is_open())
    {
        cout << "Unable to open input file: " << file << endl;
        return false;
    }
 
    string line;
    int employee_type, id, age, salary, i = 0;
    string f_name, l_name, department;
    Employee *employee;
    Manager *manager;

    while (getline(FileDB, line))
    {
        if (!ParseInfo(line, employee_type, id, f_name, l_name, age, department, salary))
        {
            cout << "Wrong data on line " << i + 1 << endl;
            i++;
            continue;
        }

        if (find(ids.begin(), ids.end(), id) != ids.end())
        {
            cout << "Error on line " << i + 1 << ". Employee with such id(" << id << ")" << " is already existed." << endl;
            i++;
            continue;
        }

        if (employee_type == 0)
        {
            employee = new Employee(f_name, l_name, age, id);
            employee->SetDepartment(department);
            employee->SetSalary(salary);

            ids.push_back(id);
            employees.push_back(employee);
        }
        else if (employee_type == 1)
        {
            manager = new Manager(f_name, l_name, age, id);
            manager->SetDepartment(department);
            manager->SetSalary(salary);

            ids.push_back(id);
            employees.push_back(manager);
        }

        i++;
    }

    FileDB.close();

    return true;
}

bool Database::ParseInfo(string str, int &type, int &id, string &f_name, string &l_name, int &age, string &department, int &salary)
{
    int begin = 0, num = 0;
    string buf;

    for (int i = 0; i < str.length(); ++i)
    {
        if (num >= 7) {
            return true;
        }

        if (str[i] == ';')
        {
            buf = str.substr(begin, i - begin);

            if (buf.length() == 0) {
                return false;
            }

            switch (num)
            {
                case 0: {
                    if (buf.find_first_not_of("0123456789") != string::npos) {
                        return false;
                    }
                    type = stoi(buf);
                    break;
                }
                case 1: {
                    if (buf.find_first_not_of("0123456789") != string::npos) {
                        return false;
                    }
                    id = stoi(buf);
                    break;
                }
                case 2: {
                    f_name = buf;
                    break;
                }
                case 3: {
                    l_name = buf;
                    break;
                }
                case 4: {
                    if (buf.find_first_not_of("0123456789") != string::npos) {
                        return false;
                    }
                    age = stoi(buf);
                    break;
                }
                case 5: {
                    department = buf;
                    break;
                }
                case 6: {
                    if (buf.find_first_not_of("0123456789") != string::npos) {
                        return false;
                    }
                    salary = stoi(buf);
                    break;
                }
            }
            begin = i + 1;
            num++;
        }
        else if (i == str.length() - 1 && num == 6)
        {
            buf = str.substr(begin, i - begin + 1);

            if (buf.length() == 0 || buf.find_first_not_of("0123456789") != string::npos) {
                return false;
            }

            salary = stoi(buf);
            num++;
        }
    }

    if (num <= 6) {
        return false;
    }

    return true;
}

void Database::ArrangeSubordinates()
{
    for (vector<Person *>::iterator it = employees.begin(); it != employees.end(); ++it)
    {
        if (typeid(**it) == typeid(Manager))
        {
            for (vector<Person *>::iterator it2 = employees.begin(); it2 != employees.end(); ++it2)
            {
                if (typeid(**it2) == typeid(Employee))
                {
                    if (dynamic_cast<Manager *>(*it)->GetDepartment() == dynamic_cast<Employee *>(*it2)->GetDepartment()) {
                        dynamic_cast<Manager *>(*it)->AddSubordinate(*it2);
                    }
                }
            }
        }
    }
}

Person* Database::HireEmployee(Person *p)
{
    if (p == nullptr) {
        return nullptr;
    }

    employees.push_back(p);

    return employees.back();
}

void Database::DisplayDepartmentEmployees(string _department)
{
    for (vector<Person *>::iterator it = employees.begin(); it != employees.end(); ++it) {
        if (dynamic_cast<Employee *>(*it)->GetDepartment() == _department) {
            (*it)->Display(true);
        }
    }
}

bool Database::FireEmployee(int id)
{
    vector<Person *>::iterator empl;
    for (empl = employees.begin(); empl != employees.end(); ++empl)
    {
        if (dynamic_cast<Employee *>(*empl)->GetId() == id) {
           break;
        }
    }

    if (empl == employees.end()) {
        return false;
    }

    if (typeid(**empl) == typeid(Employee))
    {
        for (vector<Person *>::iterator it = employees.begin(); it != employees.end(); ++it)
        {
            if (typeid(**it) == typeid(Manager) && dynamic_cast<Manager *>(*it)->GetDepartment() == dynamic_cast<Employee *>(*empl)->GetDepartment()) {
                dynamic_cast<Manager *>(*it)->RemoveSubordinate(id);
            }
        }
    }

    employees.erase(empl);

    delete dynamic_cast<Manager *>(*empl);

    return true;
}

void Database::DisplayAll()
{
    for (vector<Person *>::iterator it = employees.begin(); it != employees.end(); ++it) {
        (*it)->Display(true);
    }
}