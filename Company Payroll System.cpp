#include <iostream>
#include <vector>
#include <memory>  
#include <limits>
#include <string>
#include <sstream>

using namespace std;
class Taxable {
public:
    virtual ~Taxable() = default;
    virtual double calculateTax() const = 0;
};
class Person {
public:
    Person(const string& name = "", int id = 0) : name(name), id(id) {}
    virtual ~Person() = default;
    
    virtual double calculateSalary() const = 0;
    virtual void displayInfo() const = 0;
    virtual void inputDetails() = 0;
    
    string getName() const { return name; }
    int getId() const { return id; }

protected:
    string name;
    int id;

    int getValidIntInput(const string& prompt) {
        int value;
        while (true) {
            cout << prompt;
            string input;
            getline(cin, input);
            
            stringstream ss(input);
            if (ss >> value && ss.eof() && value >= 0) {
                return value;
            }
            cout << "Invalid input. Please enter a positive integer.\n";
        }
    }

    double getValidDoubleInput(const string& prompt) {
        double value;
        while (true) {
            cout << prompt;
            string input;
            getline(cin, input);
            
            stringstream ss(input);
            if (ss >> value && ss.eof() && value >= 0) {
                return value;
            }
            cout << "Invalid input. Please enter a positive number.\n";
        }
    }
};

class Employee : public Person, public Taxable {
public:
    Employee(const string& name = "", int id = 0, double baseSalary = 0.0, int yearsOfService = 0)
        : Person(name, id), baseSalary(baseSalary), yearsOfService(yearsOfService) {}
    
    void inputDetails() override {
        cout << "\nEnter Employee Details:\n";
        
        cout << "Name: ";
        getline(cin, name);
        
        id = getValidIntInput("ID: ");
        baseSalary = getValidDoubleInput("Base Salary: $");
        yearsOfService = getValidIntInput("Years of Service: ");
    }
    
    double calculateSalary() const override {
        return baseSalary + (yearsOfService * 500);
    }
    
    void displayInfo() const override {
        cout << "\nEmployee Details:\n";
        cout << "Name: " << name << "\n";
        cout << "ID: " << id << "\n";
        cout << "Base Salary: $" << baseSalary << "\n";
        cout << "Years of Service: " << yearsOfService << "\n";
        cout << "Total Salary: $" << calculateSalary() << "\n";
        cout << "Tax: $" << calculateTax() << "\n";
    }
    
    double calculateTax() const override {
        return calculateSalary() * 0.20;
    }

private:
    double baseSalary;
    int yearsOfService;
};

class Intern : public Person, public Taxable {
public:
    Intern(const string& name = "", int id = 0, double stipend = 0.0, int durationWeeks = 0)
        : Person(name, id), stipend(stipend), durationWeeks(durationWeeks) {}
    
    void inputDetails() override {
        cout << "\nEnter Intern Details:\n";
        
        cout << "Name: ";
        getline(cin, name);
        
        id = getValidIntInput("ID: ");
        stipend = getValidDoubleInput("Weekly Stipend: $");
        durationWeeks = getValidIntInput("Duration (weeks): ");
    }
    
    double calculateSalary() const override {
        return stipend * 4;
    }
    
    void displayInfo() const override {
        cout << "\nIntern Details:\n";
        cout << "Name: " << name << "\n";
        cout << "ID: " << id << "\n";
        cout << "Weekly Stipend: $" << stipend << "\n";
        cout << "Duration: " << durationWeeks << " weeks\n";
        cout << "Monthly Salary: $" << calculateSalary() << "\n";
        cout << "Tax: $" << calculateTax() << "\n";
    }
    
    double calculateTax() const override {
        return calculateSalary() * 0.10;
    }

private:
    double stipend;
    int durationWeeks;
};

int getMenuChoice() {
    int choice;
    while (true) {
        cout << "\nCompany Payroll System\n";
        cout << "1. Add Employee\n";
        cout << "2. Add Intern\n";
        cout << "3. Display All Records\n";
        cout << "4. Exit\n";
        cout << "Enter your choice (1-4): ";
        
        string input;
        getline(cin, input);
        
        stringstream ss(input);
        if (ss >> choice && ss.eof() && choice >= 1 && choice <= 4) {
            return choice;
        }
        cout << "Invalid choice. Please enter a number between 1 and 4.\n";
    }
}

int main() {
    vector<unique_ptr<Person>> people;

    while (true) {
        int choice = getMenuChoice();

        switch (choice) {
            case 1: {
                unique_ptr<Employee> emp(new Employee());
                emp->inputDetails();
                people.push_back(move(emp));
                cout << "Employee added successfully!\n";
                break;
            }
            case 2: {
                unique_ptr<Intern> intern(new Intern());
                intern->inputDetails();
                people.push_back(move(intern));
                cout << "Intern added successfully!\n";
                break;
            }
            case 3: {
                if (people.empty()) {
                    cout << "No records found!\n";
                } else {
                    cout << "\n=== Payroll Records ===\n";
                    for (const auto& person : people) {
                        person->displayInfo();
                        cout << "-----------------------\n";
                    }
                }
                break;
            }
            case 4: {
                cout << "Exiting program...\n";
                return 0;
            }
        }
    }
}