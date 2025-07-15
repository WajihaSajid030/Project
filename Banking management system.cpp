#include <iostream>
#include <fstream>
#include <vector>
#include <string>
#include <iomanip>

using namespace std;

class BankAccount {
private:
    string accountNumber;
    string accountHolderName;
    double balance;

public:
    BankAccount(string num = "", string name = "", double bal = 0.0) 
        : accountNumber(num), accountHolderName(name), balance(bal) {}

   
    void deposit(double amount) {
        if (amount > 0) {
            balance += amount;
            cout << "Deposit successful. New balance: $" << fixed << setprecision(2) << balance << endl;
        } else {
            cout << "Invalid deposit amount." << endl;
        }
    }

   
    void withdraw(double amount) {
        if (amount > 0 && amount <= balance) {
            balance -= amount;
            cout << "Withdrawal successful. New balance: $" << fixed << setprecision(2) << balance << endl;
        } else {
            cout << "Invalid withdrawal amount or insufficient funds." << endl;
        }
    }
    void display() const {
        cout << "\nAccount Number: " << accountNumber << endl;
        cout << "Account Holder: " << accountHolderName << endl;
        cout << "Balance: $" << fixed << setprecision(2) << balance << endl;
    }

    string getAccountNumber() const { return accountNumber; }
    string getAccountHolderName() const { return accountHolderName; }
    double getBalance() const { return balance; }
    void setAccountHolderName(string name) { accountHolderName = name; }

    void saveToFile(ofstream &outFile) const {
        outFile << accountNumber << "," << accountHolderName << "," << balance << endl;
    }
};

vector<BankAccount> loadAccountsFromFile(const string &filename) {
    vector<BankAccount> accounts;
    ifstream inFile(filename);
    string line;

    if (inFile.is_open()) {
        while (getline(inFile, line)) {
            size_t pos1 = line.find(',');
            size_t pos2 = line.find(',', pos1 + 1);

            if (pos1 != string::npos && pos2 != string::npos) {
                string accNum = line.substr(0, pos1);
                string accName = line.substr(pos1 + 1, pos2 - pos1 - 1);
                double balance = stod(line.substr(pos2 + 1));

                accounts.emplace_back(accNum, accName, balance);
            }
        }
        inFile.close();
    }

    return accounts;
}
void saveAllAccountsToFile(const string &filename, const vector<BankAccount> &accounts) {
    ofstream outFile(filename);
    if (outFile.is_open()) {
        for (const auto &account : accounts) {
            account.saveToFile(outFile);
        }
        outFile.close();
    }
}

BankAccount* searchAccount(vector<BankAccount> &accounts, const string &accNumber) {
    for (auto &account : accounts) {
        if (account.getAccountNumber() == accNumber) {
            return &account;
        }
    }
    return nullptr;
}
void displayMenu() {
    cout << "\nBank Account Management System" << endl;
    cout << "1. Create New Account" << endl;
    cout << "2. Deposit Money" << endl;
    cout << "3. Withdraw Money" << endl;
    cout << "4. Display Account Information" << endl;
    cout << "5. Search Account by Number" << endl;
    cout << "6. Exit" << endl;
    cout << "Enter your choice: ";
}

int main() {
    const string filename = "bank_accounts.txt";
    vector<BankAccount> accounts = loadAccountsFromFile(filename);
    int choice;
    string accNumber, accName;
    double amount;

    do {
        displayMenu();
        cin >> choice;
        cin.ignore();

        switch (choice) {
            case 1: { 
                cout << "Enter Account Number: ";
                getline(cin, accNumber);
                if (searchAccount(accounts, accNumber) != nullptr) {
                    cout << "Account with this number already exists." << endl;
                    break;
                }
                
                cout << "Enter Account Holder Name: ";
                getline(cin, accName);
                
                accounts.emplace_back(accNumber, accName, 0.0);
                saveAllAccountsToFile(filename, accounts);
                cout << "Account created successfully!" << endl;
                break;
            }
            case 2: { 
                cout << "Enter Account Number: ";
                getline(cin, accNumber);
                
                BankAccount* account = searchAccount(accounts, accNumber);
                if (account != nullptr) {
                    cout << "Enter Deposit Amount: $";
                    cin >> amount;
                    account->deposit(amount);
                    saveAllAccountsToFile(filename, accounts);
                } else {
                    cout << "Account not found." << endl;
                }
                break;
            }
            case 3: {
                cout << "Enter Account Number: ";
                getline(cin, accNumber);
                
                BankAccount* account = searchAccount(accounts, accNumber);
                if (account != nullptr) {
                    cout << "Enter Withdrawal Amount: $";
                    cin >> amount;
                    account->withdraw(amount);
                    saveAllAccountsToFile(filename, accounts);
                } else {
                    cout << "Account not found." << endl;
                }
                break;
            }
            case 4: { 
                cout << "Enter Account Number: ";
                getline(cin, accNumber);
                
                BankAccount* account = searchAccount(accounts, accNumber);
                if (account != nullptr) {
                    account->display();
                } else {
                    cout << "Account not found." << endl;
                }
                break;
            }
            case 5: { 
                cout << "Enter Account Number to search: ";
                getline(cin, accNumber);
                
                BankAccount* account = searchAccount(accounts, accNumber);
                if (account != nullptr) {
                    cout << "Account found:" << endl;
                    account->display();
                } else {
                    cout << "Account not found." << endl;
                }
                break;
            }
            case 6: 
                cout << "Exiting program. All data saved." << endl;
                break;
            default:
                cout << "Invalid choice. Please try again." << endl;
        }
    } while (choice != 6);

    return 0;
}