#include <iostream>
#include <string>

using namespace std;

class Vehicle {
private:
    string company;
    string model;
    int year;
    static int count; 

public:

    Vehicle() : company("Unknown"), model("Unknown"), year(0) {
        count++;
        cout << "Default constructor called. Total vehicles: " << count << endl;
    }
    Vehicle(const string& comp, const string& mdl, int yr) 
        : company(comp), model(mdl), year(yr) {
        count++;
        cout << "Parameterized constructor called. Total vehicles: " << count << endl;
    }

    
    ~Vehicle() {
        count--;
        cout << "Destructor called for " << company << " " << model << ". ";
        cout << "Remaining vehicles: " << count << endl;
    }

    static int getCount() {
        return count;
    }
    void displayInfo() const {
        cout << "Company: " << company << endl;
        cout << "Model: " << model << endl;
        cout << "Year: " << year << endl;
    }
};
int Vehicle::count = 0;

int main() {
    cout << "=== Vehicle Info Manager ===" << endl;
    cout << "Initial vehicle count: " << Vehicle::getCount() << endl << endl;
    Vehicle car1; 
    car1.displayInfo();
    cout << endl;

    Vehicle car2("Toyota", "Corolla", 2020);
    car2.displayInfo();
    cout << endl;

    Vehicle car3("Honda", "Civic", 2018);
    car3.displayInfo();
    cout << endl;

    cout << "Current vehicle count before destruction: " << Vehicle::getCount() << endl << endl;

   
    return 0;
}