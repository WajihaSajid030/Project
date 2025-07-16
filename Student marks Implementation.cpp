#include <iostream>
#include <string>
#include <algorithm>
#include <limits>
#include <vector> 

using namespace std;

class Student {
private:
    int rollNumber;
    string name;
    float marks[3];
    float total;
    float average;

public:
    Student(int roll, string studentName, float m1, float m2, float m3) {
        rollNumber = roll;
        name = studentName;
        marks[0] = m1;
        marks[1] = m2;
        marks[2] = m3;
        total = m1 + m2 + m3;
        average = total / 3.0f;
    }
    Student() : rollNumber(0), name(""), total(0), average(0) {
        marks[0] = marks[1] = marks[2] = 0;
    }
    void display() const {
        cout << "\nRoll Number: " << rollNumber << endl;
        cout << "Name: " << name << endl;
        cout << "Marks: " << marks[0] << ", " << marks[1] << ", " << marks[2] << endl;
        cout << "Total: " << total << endl;
        cout << "Average: " << average << endl;
        cout << "-------------------------" << endl;
    }
    float getTotal() const {
        return total;
    }
    int getRollNumber() const {
        return rollNumber;
    }
};
bool compareStudents(const Student &a, const Student &b) {
    return a.getTotal() > b.getTotal();
}
int getValidInt(const string& prompt) {
    int value;
    while (true) {
        cout << prompt;
        cin >> value;
        if (cin.fail()) {
            cin.clear();
            cin.ignore(numeric_limits<streamsize>::max(), '\n');
            cout << "Invalid input. Please enter a number.\n";
        } else {
            cin.ignore(numeric_limits<streamsize>::max(), '\n');
            return value;
        }
    }
}
float getValidFloat(const string& prompt) {
    float value;
    while (true) {
        cout << prompt;
        cin >> value;
        if (cin.fail()) {
            cin.clear();
            cin.ignore(numeric_limits<streamsize>::max(), '\n');
            cout << "Invalid input. Please enter a number.\n";
        } else {
            cin.ignore(numeric_limits<streamsize>::max(), '\n');
            return value;
        }
    }
}

int main() {
    int numStudents;
    
    cout << "STUDENT RESULT SYSTEM\n";
    cout << "=====================\n\n";
    numStudents = getValidInt("Enter number of students: ");
    vector<Student> students;
    students.reserve(numStudents);
    for (int i = 0; i < numStudents; ++i) {
        cout << "\nEnter details for Student " << i + 1 << ":\n";
        
        int roll = getValidInt("Roll Number: ");
        
        cout << "Name: ";
        string name;
        getline(cin, name);
        
        float m1 = getValidFloat("Mark for Subject 1: ");
        float m2 = getValidFloat("Mark for Subject 2: ");
        float m3 = getValidFloat("Mark for Subject 3: ");
        
        students.emplace_back(roll, name, m1, m2, m3);
    }

    cout << "\nOriginal Student List:";
    cout << "\n======================";
    for (const auto& student : students) {
        student.display();
    }
    sort(students.begin(), students.end(), compareStudents);

    cout << "\nStudents Sorted by Total Marks (Descending Order):";
    cout << "\n=============================================";
    for (const auto& student : students) {
        student.display();
    }

    return 0;
}