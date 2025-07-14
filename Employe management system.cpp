#include <iostream>
#include <fstream>
#include <vector>
#include <string>
#include <iomanip>
#include <ctime>

using namespace std;

// Employee structure
struct Employee {
    int id;
    string name;
    string department;
    double salary;
};

// Function prototypes
void addEmployee(vector<Employee>& employees, ofstream& logFile);
void viewAllEmployees(const vector<Employee>& employees);
void updateSalary(vector<Employee>& employees, ofstream& logFile);
void calculateSalaryStats(const vector<Employee>& employees);
void saveToFile(const vector<Employee>& employees, const string& filename);
void loadFromFile(vector<Employee>& employees, const string& filename);
void logAction(ofstream& logFile, const string& action);

int main() {
    vector<Employee> employees;
    const string dataFile = "employee_data.txt";
    const string logFile = "employee_log.txt";
    
    // Open log file
    ofstream log(logFile, ios::app);
    if (!log.is_open()) {
        cerr << "Error opening log file!" << endl;
        return 1;
    }
    
    // Load existing data
    loadFromFile(employees, dataFile);
    logAction(log, "Program started. Loaded " + to_string(employees.size()) + " employees.");
    
    int choice;
    do {
        cout << "\nEmployee Record Management System\n";
        cout << "1. Add New Employee\n";
        cout << "2. View All Employees\n";
        cout << "3. Update Employee Salary\n";
        cout << "4. Calculate Salary Statistics\n";
        cout << "5. Exit\n";
        cout << "Enter your choice: ";
        cin >> choice;
        
        cin.ignore(); // Clear input buffer
        
        switch (choice) {
            case 1:
                addEmployee(employees, log);
                saveToFile(employees, dataFile);
                break;
            case 2:
                viewAllEmployees(employees);
                break;
            case 3:
                updateSalary(employees, log);
                saveToFile(employees, dataFile);
                break;
            case 4:
                calculateSalaryStats(employees);
                break;
            case 5:
                logAction(log, "Program exiting. Saved " + to_string(employees.size()) + " employees.");
                cout << "Exiting program..." << endl;
                break;
            default:
                cout << "Invalid choice. Please try again." << endl;
        }
    } while (choice != 5);
    
    log.close();
    return 0;
}

void addEmployee(vector<Employee>& employees, ofstream& logFile) {
    Employee emp;
    
    cout << "\nEnter Employee ID: ";
    cin >> emp.id;
    
    // Check for duplicate ID
    for (const auto& e : employees) {
        if (e.id == emp.id) {
            cout << "Employee with this ID already exists!" << endl;
            logAction(logFile, "Duplicate ID attempt: " + to_string(emp.id));
            return;
        }
    }
    
    cout << "Enter Employee Name: ";
    cin.ignore();
    getline(cin, emp.name);
    
    cout << "Enter Department: ";
    getline(cin, emp.department);
    
    cout << "Enter Salary: $";
    cin >> emp.salary;
    
    employees.push_back(emp);
    cout << "Employee added successfully!" << endl;
    
    logAction(logFile, "Added employee: ID=" + to_string(emp.id) + 
              ", Name=" + emp.name + ", Dept=" + emp.department);
}

void viewAllEmployees(const vector<Employee>& employees) {
    if (employees.empty()) {
        cout << "No employees to display." << endl;
        return;
    }
    
    cout << "\nEmployee List:\n";
    cout << left << setw(10) << "ID" << setw(20) << "Name" 
         << setw(15) << "Department" << setw(10) << "Salary" << endl;
    cout << string(55, '-') << endl;
    
    for (const auto& emp : employees) {
        cout << left << setw(10) << emp.id 
             << setw(20) << emp.name 
             << setw(15) << emp.department 
             << "$" << fixed << setprecision(2) << emp.salary << endl;
    }
}

void updateSalary(vector<Employee>& employees, ofstream& logFile) {
    if (employees.empty()) {
        cout << "No employees to update." << endl;
        return;
    }
    
    int id;
    cout << "\nEnter Employee ID to update: ";
    cin >> id;
    
    bool found = false;
    for (auto& emp : employees) {
        if (emp.id == id) {
            double newSalary;
            cout << "Current salary: $" << emp.salary << endl;
            cout << "Enter new salary: $";
            cin >> newSalary;
            
            double oldSalary = emp.salary;
            emp.salary = newSalary;
            
            cout << "Salary updated successfully!" << endl;
            logAction(logFile, "Updated salary for ID=" + to_string(id) + 
                     " from $" + to_string(oldSalary) + " to $" + to_string(newSalary));
            found = true;
            break;
        }
    }
    
    if (!found) {
        cout << "Employee with ID " << id << " not found." << endl;
        logAction(logFile, "Failed salary update for ID=" + to_string(id));
    }
}

void calculateSalaryStats(const vector<Employee>& employees) {
    if (employees.empty()) {
        cout << "No employees to calculate statistics." << endl;
        return;
    }
    
    double total = 0.0;
    for (const auto& emp : employees) {
        total += emp.salary;
    }
    
    double average = total / employees.size();
    
    cout << "\nSalary Statistics:\n";
    cout << "Total Salary: $" << fixed << setprecision(2) << total << endl;
    cout << "Average Salary: $" << fixed << setprecision(2) << average << endl;
}

void saveToFile(const vector<Employee>& employees, const string& filename) {
    ofstream outFile(filename);
    if (!outFile.is_open()) {
        cerr << "Error saving data!" << endl;
        return;
    }
    
    for (const auto& emp : employees) {
        outFile << emp.id << "," << emp.name << "," 
                << emp.department << "," << emp.salary << endl;
    }
    
    outFile.close();
}

void loadFromFile(vector<Employee>& employees, const string& filename) {
    ifstream inFile(filename);
    if (!inFile.is_open()) {
        return; // File may not exist yet
    }
    
    employees.clear();
    Employee emp;
    char comma; // To read the commas
    
    while (inFile >> emp.id >> comma &&
           getline(inFile, emp.name, ',') &&
           getline(inFile, emp.department, ',') &&
           inFile >> emp.salary) {
        employees.push_back(emp);
    }
    
    inFile.close();
}

void logAction(ofstream& logFile, const string& action) {
    if (!logFile.is_open()) return;
    
    // Get current time
    time_t now = time(nullptr);
    char timestamp[20];
    strftime(timestamp, sizeof(timestamp), "%Y-%m-%d %H:%M:%S", localtime(&now));
    
    logFile << "[" << timestamp << "] " << action << endl;
}