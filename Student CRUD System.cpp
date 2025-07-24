#include <iostream>
#include <fstream>
#include <vector>
#include <algorithm>
#include <iomanip>
#include <limits>
#include <stdexcept>

using namespace std;

class Student {
private:
    int rollNo;
    string name;
    string department;
    float cgpa;

public:
    Student(int roll = 0, string n = "", string dept = "", float gpa = 0.0f) 
        : rollNo(roll), name(n), department(dept), cgpa(gpa) {}
    int getRollNo() const { return rollNo; }
    string getName() const { return name; }
    string getDepartment() const { return department; }
    float getCGPA() const { return cgpa; }
    void setRollNo(int roll) { rollNo = roll; }
    void setName(string n) { name = n; }
    void setDepartment(string dept) { department = dept; }
    void setCGPA(float gpa) { cgpa = gpa; }
    void display() const {
        cout << left << setw(10) << rollNo 
             << setw(25) << name 
             << setw(15) << department 
             << setw(10) << fixed << setprecision(2) << cgpa << endl;
    }
    friend ostream& operator<<(ostream& os, const Student& s);
    friend istream& operator>>(istream& is, Student& s);
};

ostream& operator<<(ostream& os, const Student& s) {
    os.write(reinterpret_cast<const char*>(&s.rollNo), sizeof(s.rollNo));
    size_t nameSize = s.name.size();
    os.write(reinterpret_cast<const char*>(&nameSize), sizeof(nameSize));
    os.write(s.name.c_str(), nameSize);
    size_t deptSize = s.department.size();
    os.write(reinterpret_cast<const char*>(&deptSize), sizeof(deptSize));
    os.write(s.department.c_str(), deptSize);
    os.write(reinterpret_cast<const char*>(&s.cgpa), sizeof(s.cgpa));
    return os;
}
istream& operator>>(istream& is, Student& s) {
    is.read(reinterpret_cast<char*>(&s.rollNo), sizeof(s.rollNo));
    size_t nameSize;
    is.read(reinterpret_cast<char*>(&nameSize), sizeof(nameSize));
    char* nameBuffer = new char[nameSize + 1];
    is.read(nameBuffer, nameSize);
    nameBuffer[nameSize] = '\0';
    s.name = nameBuffer;
    delete[] nameBuffer;
    size_t deptSize;
    is.read(reinterpret_cast<char*>(&deptSize), sizeof(deptSize));
    char* deptBuffer = new char[deptSize + 1];
    is.read(deptBuffer, deptSize);
    deptBuffer[deptSize] = '\0';
    s.department = deptBuffer;
    delete[] deptBuffer;
    is.read(reinterpret_cast<char*>(&s.cgpa), sizeof(s.cgpa));
    return is;
}

class StudentCRUD {
private:
    vector<Student> students;
    string filename;
    void loadFromFile() {
        try {
            ifstream inFile(filename, ios::binary);
            if (!inFile) {
                throw runtime_error("File not found or cannot be opened");
            }
            inFile.seekg(0, ios::end);
            if (inFile.tellg() == 0) {
                inFile.close();
                return;
            }
            inFile.seekg(0, ios::beg);

            Student s;
            while (inFile >> s) {
                students.push_back(s);
            }
            inFile.close();
        } catch (const exception& e) {
            cerr << "Error loading file: " << e.what() << endl;
        }
    }
    void saveToFile() {
        try {
            ofstream outFile(filename, ios::binary);
            if (!outFile) {
                throw runtime_error("Cannot open file for writing");
            }

            for (const auto& s : students) {
                outFile << s;
            }
            outFile.close();
        } catch (const exception& e) {
            cerr << "Error saving to file: " << e.what() << endl;
        }
    }

public:
    StudentCRUD(const string& file) : filename(file) {
        loadFromFile();
    }

    ~StudentCRUD() {
        saveToFile();
    }
    void addStudent() {
        Student s;
        int roll;
        string name, dept;
        float gpa;

        cout << "Enter Roll No: ";
        cin >> roll;
        cin.ignore(numeric_limits<streamsize>::max(), '\n');
        for (const auto& student : students) {
            if (student.getRollNo() == roll) {
                cout << "Student with this Roll No already exists!" << endl;
                return;
            }
        }

        cout << "Enter Name: ";
        getline(cin, name);

        cout << "Enter Department: ";
        getline(cin, dept);

        cout << "Enter CGPA: ";
        cin >> gpa;

        s.setRollNo(roll);
        s.setName(name);
        s.setDepartment(dept);
        s.setCGPA(gpa);

        students.push_back(s);
        cout << "Student added successfully!" << endl;
    }
    void viewStudents() const {
        if (students.empty()) {
            cout << "No student records found!" << endl;
            return;
        }

        cout << left << setw(10) << "Roll No" 
             << setw(25) << "Name" 
             << setw(15) << "Department" 
             << setw(10) << "CGPA" << endl;
        cout << string(60, '-') << endl;

        for (const auto& s : students) {
            s.display();
        }
    }

  
    void searchStudent() const {
        int roll;
        cout << "Enter Roll No to search: ";
        cin >> roll;

        bool found = false;
        for (const auto& s : students) {
            if (s.getRollNo() == roll) {
                cout << "\nStudent Found:\n";
                cout << left << setw(10) << "Roll No" 
                     << setw(25) << "Name" 
                     << setw(15) << "Department" 
                     << setw(10) << "CGPA" << endl;
                cout << string(60, '-') << endl;
                s.display();
                found = true;
                break;
            }
        }

        if (!found) {
            cout << "Student with Roll No " << roll << " not found!" << endl;
        }
    }

    void updateStudent() {
        int roll;
        cout << "Enter Roll No to update: ";
        cin >> roll;

        for (auto& s : students) {
            if (s.getRollNo() == roll) {
                string name, dept;
                float gpa;

                cin.ignore(numeric_limits<streamsize>::max(), '\n');
                cout << "Enter new Name (current: " << s.getName() << "): ";
                getline(cin, name);

                cout << "Enter new Department (current: " << s.getDepartment() << "): ";
                getline(cin, dept);

                cout << "Enter new CGPA (current: " << s.getCGPA() << "): ";
                cin >> gpa;

                s.setName(name);
                s.setDepartment(dept);
                s.setCGPA(gpa);

                cout << "Student record updated successfully!" << endl;
                return;
            }
        }

        cout << "Student with Roll No " << roll << " not found!" << endl;
    }

 
    void deleteStudent() {
        int roll;
        cout << "Enter Roll No to delete: ";
        cin >> roll;

        auto it = remove_if(students.begin(), students.end(), 
            [roll](const Student& s) { return s.getRollNo() == roll; });

        if (it != students.end()) {
            students.erase(it, students.end());
            cout << "Student record deleted successfully!" << endl;
        } else {
            cout << "Student with Roll No " << roll << " not found!" << endl;
        }
    }

    void sortByCGPA() {
        sort(students.begin(), students.end(), 
            [](const Student& a, const Student& b) { return a.getCGPA() > b.getCGPA(); });
        cout << "Students sorted by CGPA (highest to lowest)!" << endl;
    }
};

void displayMenu() {
    cout << "\nStudent Record CRUD System\n";
    cout << "1. Add Student\n";
    cout << "2. View All Students\n";
    cout << "3. Search Student\n";
    cout << "4. Update Student\n";
    cout << "5. Delete Student\n";
    cout << "6. Sort Students by CGPA\n";
    cout << "7. Exit\n";
    cout << "Enter your choice: ";
}

int main() {
    StudentCRUD crud("students.dat");

    int choice;
    do {
        displayMenu();
        cin >> choice;

        try {
            switch (choice) {
                case 1:
                    crud.addStudent();
                    break;
                case 2:
                    crud.viewStudents();
                    break;
                case 3:
                    crud.searchStudent();
                    break;
                case 4:
                    crud.updateStudent();
                    break;
                case 5:
                    crud.deleteStudent();
                    break;
                case 6:
                    crud.sortByCGPA();
                    break;
                case 7:
                    cout << "Exiting program. Goodbye!" << endl;
                    break;
                default:
                    cout << "Invalid choice! Please try again." << endl;
            }
        } catch (const exception& e) {
            cerr << "Error: " << e.what() << endl;
            cin.clear();
            cin.ignore(numeric_limits<streamsize>::max(), '\n');
        }
    } while (choice != 7);

    return 0;
}