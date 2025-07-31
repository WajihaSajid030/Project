#include <iostream>
#include <vector>
#include <set>
#include <map>
#include <algorithm>
#include <limits>
#include <string>

using namespace std;
void displayMainMenu();
void manageStudentMarks(vector<int>& marks);
void manageDepartments(set<string>& departments);
void manageDepartmentCounts(map<string, int>& deptCounts);
void displayVector(const vector<int>& vec);
void displaySet(const set<string>& s);
void displayMap(const map<string, int>& m);

int main() {
    vector<int> studentMarks;
    set<string> departments;
    map<string, int> departmentCounts;

    int choice;
    do {
        displayMainMenu();
        cout << "Enter your choice (1-4): ";
        cin >> choice;
        cin.ignore(numeric_limits<streamsize>::max(), '\n');

        switch(choice) {
            case 1:
                manageStudentMarks(studentMarks);
                break;
            case 2:
                manageDepartments(departments);
                break;
            case 3:
                manageDepartmentCounts(departmentCounts);
                break;
            case 4:
                cout << "Exiting program...\n";
                break;
            default:
                cout << "Invalid choice. Please try again.\n";
        }
    } while(choice != 4);

    return 0;
}

void displayMainMenu() {
    cout << "\n===== Data Organizer Menu =====\n";
    cout << "1. Manage Student Marks\n";
    cout << "2. Manage Department Names\n";
    cout << "3. Manage Department Student Counts\n";
    cout << "4. Exit\n";
}

void manageStudentMarks(vector<int>& marks) {
    int subChoice;
    do {
        cout << "\n===== Student Marks Management =====\n";
        cout << "1. Add Mark\n";
        cout << "2. Search Mark\n";
        cout << "3. Remove Mark\n";
        cout << "4. Sort and Display Marks\n";
        cout << "5. Back to Main Menu\n";
        cout << "Enter your choice (1-5): ";
        cin >> subChoice;

        switch(subChoice) {
            case 1: {
                int mark;
                cout << "Enter mark to add: ";
                cin >> mark;
                marks.push_back(mark);
                cout << "Mark added successfully.\n";
                break;
            }
            case 2: {
                int mark;
                cout << "Enter mark to search: ";
                cin >> mark;
                auto it = find(marks.begin(), marks.end(), mark);
                if(it != marks.end()) {
                    cout << "Mark found in the collection.\n";
                } else {
                    cout << "Mark not found.\n";
                }
                break;
            }
            case 3: {
                int mark;
                cout << "Enter mark to remove: ";
                cin >> mark;
                auto it = find(marks.begin(), marks.end(), mark);
                if(it != marks.end()) {
                    marks.erase(it);
                    cout << "Mark removed successfully.\n";
                } else {
                    cout << "Mark not found.\n";
                }
                break;
            }
            case 4: {
                sort(marks.begin(), marks.end());
                cout << "Sorted Marks: ";
                displayVector(marks);
                break;
            }
            case 5:
                break;
            default:
                cout << "Invalid choice. Please try again.\n";
        }
      
        cin.ignore(numeric_limits<streamsize>::max(), '\n');
    } while(subChoice != 5);
}

void manageDepartments(set<string>& departments) {
    int subChoice;
    do {
        cout << "\n===== Department Names Management =====\n";
        cout << "1. Add Department\n";
        cout << "2. Search Department\n";
        cout << "3. Remove Department\n";
        cout << "4. Display All Departments\n";
        cout << "5. Back to Main Menu\n";
        cout << "Enter your choice (1-5): ";
        cin >> subChoice;
        cin.ignore(numeric_limits<streamsize>::max(), '\n');

        switch(subChoice) {
            case 1: {
                string dept;
                cout << "Enter department name to add: ";
                getline(cin, dept);
                auto result = departments.insert(dept);
                if(result.second) {
                    cout << "Department added successfully.\n";
                } else {
                    cout << "Department already exists.\n";
                }
                break;
            }
            case 2: {
                string dept;
                cout << "Enter department name to search: ";
                getline(cin, dept);
                auto it = departments.find(dept);
                if(it != departments.end()) {
                    cout << "Department found: " << *it << endl;
                } else {
                    cout << "Department not found.\n";
                }
                break;
            }
            case 3: {
                string dept;
                cout << "Enter department name to remove: ";
                getline(cin, dept);
                auto it = departments.find(dept);
                if(it != departments.end()) {
                    departments.erase(it);
                    cout << "Department removed successfully.\n";
                } else {
                    cout << "Department not found.\n";
                }
                break;
            }
            case 4: {
                cout << "All Departments:\n";
                displaySet(departments);
                break;
            }
            case 5:
                break;
            default:
                cout << "Invalid choice. Please try again.\n";
        }
    } while(subChoice != 5);
}

void manageDepartmentCounts(map<string, int>& deptCounts) {
    int subChoice;
    do {
        cout << "\n===== Department Student Counts =====\n";
        cout << "1. Add/Update Department Count\n";
        cout << "2. Search Department\n";
        cout << "3. Remove Department\n";
        cout << "4. Display All Departments\n";
        cout << "5. Back to Main Menu\n";
        cout << "Enter your choice (1-5): ";
        cin >> subChoice;
        cin.ignore(numeric_limits<streamsize>::max(), '\n');

        switch(subChoice) {
            case 1: {
                string dept;
                int count;
                cout << "Enter department name: ";
                getline(cin, dept);
                cout << "Enter student count: ";
                cin >> count;
                cin.ignore(numeric_limits<streamsize>::max(), '\n');
                deptCounts[dept] = count;
                cout << "Department count updated successfully.\n";
                break;
            }
            case 2: {
                string dept;
                cout << "Enter department name to search: ";
                getline(cin, dept);
                auto it = deptCounts.find(dept);
                if(it != deptCounts.end()) {
                    cout << "Department found: " << it->first 
                         << " has " << it->second << " students.\n";
                } else {
                    cout << "Department not found.\n";
                }
                break;
            }
            case 3: {
                string dept;
                cout << "Enter department name to remove: ";
                getline(cin, dept);
                auto it = deptCounts.find(dept);
                if(it != deptCounts.end()) {
                    deptCounts.erase(it);
                    cout << "Department removed successfully.\n";
                } else {
                    cout << "Department not found.\n";
                }
                break;
            }
            case 4: {
                cout << "Department Student Counts:\n";
                displayMap(deptCounts);
                break;
            }
            case 5:
                break;
            default:
                cout << "Invalid choice. Please try again.\n";
        }
    } while(subChoice != 5);
}

void displayVector(const vector<int>& vec) {
    if(vec.empty()) {
        cout << "No marks available.\n";
        return;
    }
    for(const auto& mark : vec) {
        cout << mark << " ";
    }
    cout << endl;
}

void displaySet(const set<string>& s) {
    if(s.empty()) {
        cout << "No departments available.\n";
        return;
    }
    for(const auto& dept : s) {
        cout << dept << endl;
    }
}

void displayMap(const map<string, int>& m) {
    if(m.empty()) {
        cout << "No department counts available.\n";
        return;
    }
    for(const auto& pair : m) {
        cout << pair.first << ": " << pair.second << " students" << endl;
    }
}