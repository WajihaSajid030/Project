#include <iostream>
#include <limits>
#include <fstream>
#include <stdexcept>
#include <string>
#include <ctime>


class DivisionByZeroException : public std::runtime_error {
public:
    DivisionByZeroException() : std::runtime_error("Error: Division by zero is not allowed.") {}
};

class InvalidInputException : public std::runtime_error {
public:
    InvalidInputException() : std::runtime_error("Error: Invalid input. Please enter numeric values.") {}
};

class OverflowException : public std::runtime_error {
public:
    OverflowException() : std::runtime_error("Error: Arithmetic overflow occurred.") {}
};
void logException(const std::string& error) {
    std::ofstream logFile("calculator_log.txt", std::ios::app);
    if (logFile.is_open()) {
        std::time_t now = std::time(nullptr);
        std::string timeStr = std::ctime(&now);
        timeStr.erase(timeStr.find_last_not_of("\n") + 1); 
        
        logFile << "[" << timeStr << "] " << error << std::endl;
        logFile.close();
    }
}
template <typename T>
void checkOverflow(T a, T b, char op) {
    if (op == '+') {
        if (a > 0 && b > std::numeric_limits<T>::max() - a) throw OverflowException();
        if (a < 0 && b < std::numeric_limits<T>::min() - a) throw OverflowException();
    } else if (op == '-') {
        if (a < 0 && b > std::numeric_limits<T>::max() + a) throw OverflowException();
        if (a > 0 && b < std::numeric_limits<T>::min() + a) throw OverflowException();
    } else if (op == '*') {
        if (a > 0) {
            if (b > 0 && a > std::numeric_limits<T>::max() / b) throw OverflowException();
            if (b < 0 && b < std::numeric_limits<T>::min() / a) throw OverflowException();
        } else if (a < 0) {
            if (b > 0 && a < std::numeric_limits<T>::min() / b) throw OverflowException();
            if (b < 0 && a < std::numeric_limits<T>::max() / b) throw OverflowException();
        }
    }
}
void calculator() {
    double num1, num2;
    char op;
    
    std::cout << "Robust Calculator with Exception Handling\n";
    std::cout << "Supported operations: +, -, *, /\n";
    std::cout << "Enter expression (e.g., 5 + 3): ";
    
    try {
        if (!(std::cin >> num1 >> op >> num2)) {
            std::cin.clear(); 
            std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
            throw InvalidInputException();
        }

        if (op == '/' && num2 == 0) {
            throw DivisionByZeroException();
        }
        checkOverflow(num1, num2, op);
        
        double result;
        switch (op) {
            case '+':
                result = num1 + num2;
                break;
            case '-':
                result = num1 - num2;
                break;
            case '*':
                result = num1 * num2;
                break;
            case '/':
                result = num1 / num2;
                break;
            default:
                throw InvalidInputException();
        }
        
        std::cout << "Result: " << num1 << " " << op << " " << num2 << " = " << result << std::endl;
        
    } catch (const DivisionByZeroException& e) {
        std::cerr << e.what() << std::endl;
        logException(e.what());
    } catch (const InvalidInputException& e) {
        std::cerr << e.what() << std::endl;
        logException(e.what());
    } catch (const OverflowException& e) {
        std::cerr << e.what() << std::endl;
        logException(e.what());
    } catch (...) {
        std::cerr << "Error: An unexpected error occurred." << std::endl;
        logException("Unexpected error occurred");
    }
}

int main() {
    char choice;
    
    do {
        calculator();
        std::cout << "Do you want to perform another calculation? (y/n): ";
        std::cin >> choice;
        std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
    } while (choice == 'y' || choice == 'Y');
    
    std::cout << "Thank you for using the calculator. Goodbye!\n";
    return 0;
}