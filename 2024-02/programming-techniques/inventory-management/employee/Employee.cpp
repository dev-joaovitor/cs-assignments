#include <iostream>
#include <limits>
#include <string>
#include "Employee.h"

Employee::Employee(const std::string& username, const std::string& password)
    : id { ++this->lastId }
    , username { username }
    , password { password }
    , created_at { time(NULL) }
{
}

const bool Employee::hasUnextractedInput()
{
    return !std::cin.eof() && std::cin.peek() != '\n';
}

const void Employee::ignoreLine()
{
    std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
}

const bool Employee::logIn()
{
    std::cout << "\n[EMPLOYEE LOGIN]\n";

    if (Employee::employees.empty()) {
        std::cout << "\n[NO USERS REGISTERED]\n";
        return false;
    }

    std::string username{},
                password{};

    std::cout << "\nEnter employee username: ";
    std::cin >> username;

    if (hasUnextractedInput()) {
        ignoreLine(); 
    }
    
    if (Employee::employees.find(username)
        == Employee::employees.end()) {
        std::cout << "\n[EMPLOYEE DOESN'T EXIST]\n";
        return false;
    }

    std::cout << "\n[LOGGING IN AS " << username << "]\n";
    std::cout << "\nEnter employee password: ";
    std::cin.ignore();
    std::getline(std::cin, password);

    return Employee::employees[username]->getPassword() == password;
}

const bool Employee::registerEmployee()
{
    std::cout << "\n[EMPLOYEE REGISTER]\n";

    std::string username{},
                password{};

    std::cout << "\nEnter employee username: ";
    std::cin >> username;

    if (hasUnextractedInput()) {
        std::cout << "\n[SPACE CHARACTER NOT ALLOWED]\n";
        ignoreLine(); 
        return false;
    }
    
    if (Employee::employees.find(username)
        != Employee::employees.end()) {
        std::cout << "\n[EMPLOYEE ALREADY EXISTS]\n";
        return false;
    }

    std::cout << "\nEnter employee password: ";
    std::cin.ignore();
    std::getline(std::cin, password);

    Employee::employees[username] = new Employee(username, password);

    return Employee::employees.find(username) != Employee::employees.end();
}

const void Employee::deleteAll()
{
    for (auto& employee : Employee::employees) {
        delete employee.second;
    }
    Employee::employees.clear();
}

unsigned int Employee::lastId{ 0 };
std::unordered_map<std::string, Employee*> Employee::employees{};

