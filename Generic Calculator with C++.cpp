#include <iostream>
#include <stdexcept>
#include <limits>
#include <typeinfo>
#include <cassert>

using namespace std;

template <typename T>
T add(T a, T b) {
    return a + b;
}

template <typename T>
T subtract(T a, T b) {
    return a - b;
}

template <typename T>
T multiply(T a, T b) {
    return a * b;
}
template <typename T>
T divide(T a, T b) {
    if (b == 0) {
        throw runtime_error("Division by zero error");
    }
    return a / b;
}
template <>
float divide<float>(float a, float b) {
    if (abs(b) < numeric_limits<float>::epsilon()) {
        throw runtime_error("Division by zero (float)");
    }
    return a / b;
}

template <>
double divide<double>(double a, double b) {
    if (abs(b) < numeric_limits<double>::epsilon()) {
        throw runtime_error("Division by zero (double)");
    }
    return a / b;
}
template <typename T>
class Calculator {
private:
    T last_result;
public:
    Calculator() : last_result(0) {}
    
    T get_last_result() const { return last_result; }
    
    T add(T a, T b) {
        last_result = ::add(a, b);
        return last_result;
    }
    
    T subtract(T a, T b) {
        last_result = ::subtract(a, b);
        return last_result;
    }
    
    T multiply(T a, T b) {
        last_result = ::multiply(a, b);
        return last_result;
    }
    
    T divide(T a, T b) {
        last_result = ::divide(a, b);
        return last_result;
    }
};

int display_menu() {
    int choice;
    cout << "\nCalculator Menu:\n";
    cout << "1. Add\n";
    cout << "2. Subtract\n";
    cout << "3. Multiply\n";
    cout << "4. Divide\n";
    cout << "5. Exit\n";
    cout << "Enter your choice (1-5): ";
    cin >> choice;
    return choice;
}
int get_calculator_type() {
    int type;
    cout << "\nSelect data type:\n";
    cout << "1. Integer\n";
    cout << "2. Float\n";
    cout << "3. Double\n";
    cout << "Enter your choice (1-3): ";
    cin >> type;
    return type;
}
void run_tests() {
    assert(add<int>(2, 3) == 5);
    assert(add<float>(2.5f, 3.5f) == 6.0f);
    assert(add<double>(2.5, 3.5) == 6.0);
    assert(subtract<int>(5, 3) == 2);
    assert(subtract<float>(5.5f, 2.5f) == 3.0f);
    assert(multiply<int>(4, 3) == 12);
    assert(multiply<double>(2.5, 4.0) == 10.0);
    assert(divide<int>(10, 2) == 5);
    assert(divide<double>(10.0, 4.0) == 2.5);
    Calculator<int> intCalc;
    assert(intCalc.add(2, 3) == 5);
    assert(intCalc.subtract(5, 3) == 2);
    
    Calculator<double> doubleCalc;
    assert(doubleCalc.multiply(2.5, 4.0) == 10.0);
    
    cout << "All tests passed successfully!\n";
}
int main() {
    cout << "Generic Calculator using Templates\n";
    
    while (true) {
        int calc_type = get_calculator_type();
        if (calc_type < 1 || calc_type > 3) {
            cout << "Invalid choice. Please try again.\n";
            continue;
        }
        
        int choice = display_menu();
        if (choice == 5) {
            break;
        }
        
        try {
            if (calc_type == 1) { 
                Calculator<int> calc;
                int a, b;
                cout << "Enter two integers: ";
                cin >> a >> b;
                
                switch (choice) {
                    case 1: cout << "Result: " << calc.add(a, b); break;
                    case 2: cout << "Result: " << calc.subtract(a, b); break;
                    case 3: cout << "Result: " << calc.multiply(a, b); break;
                    case 4: cout << "Result: " << calc.divide(a, b); break;
                    default: cout << "Invalid choice!"; break;
                }
            }
            else if (calc_type == 2) {
                Calculator<float> calc;
                float a, b;
                cout << "Enter two floats: ";
                cin >> a >> b;
                
                switch (choice) {
                    case 1: cout << "Result: " << calc.add(a, b); break;
                    case 2: cout << "Result: " << calc.subtract(a, b); break;
                    case 3: cout << "Result: " << calc.multiply(a, b); break;
                    case 4: cout << "Result: " << calc.divide(a, b); break;
                    default: cout << "Invalid choice!"; break;
                }
            }
            else if (calc_type == 3) { 
                Calculator<double> calc;
                double a, b;
                cout << "Enter two doubles: ";
                cin >> a >> b;
                
                switch (choice) {
                    case 1: cout << "Result: " << calc.add(a, b); break;
                    case 2: cout << "Result: " << calc.subtract(a, b); break;
                    case 3: cout << "Result: " << calc.multiply(a, b); break;
                    case 4: cout << "Result: " << calc.divide(a, b); break;
                    default: cout << "Invalid choice!"; break;
                }
            }
        }
        catch (const exception& e) {
            cerr << "Error: " << e.what() << endl;
        }
        
        cout << "\n";
    }
    
    cout << "Thank you for using the Generic Calculator!\n";
    return 0;
}