#include <iostream>
#include <fstream>
#include <cstring>
#include <cstdio>
#include<iomanip>
using namespace std;

const char* FILENAME = "inventory.dat";
const char* TEMP_FILENAME = "temp_inventory.dat";
const int MAX_ITEMS = 100;

struct Item {
    int id;
    char name[50];
    int quantity;
    float price;
};
void displayMenu();
void addItem();
void viewAllItems();
void searchItemByID();
void updateQuantity();
void deleteItem();
bool idExists(int id);
void saveItemToFile(const Item& item);
void rewriteFileAfterDeletion(int idToDelete);

int main() {
    int choice;
    
    do {
        displayMenu();
        cin >> choice;
        cin.ignore();
        
        switch(choice) {
            case 1:
                addItem();
                break;
            case 2:
                viewAllItems();
                break;
            case 3:
                searchItemByID();
                break;
            case 4:
                updateQuantity();
                break;
            case 5:
                deleteItem();
                break;
            case 6:
                cout << "Exiting program. Goodbye!\n";
                break;
            default:
                cout << "Invalid choice. Please try again.\n";
        }
    } while(choice != 6);
    
    return 0;
}

void displayMenu() {
    cout << "\nInventory Management System\n";
    cout << "1. Add Item\n";
    cout << "2. View All Items\n";
    cout << "3. Search by ID\n";
    cout << "4. Update Quantity\n";
    cout << "5. Delete Item\n";
    cout << "6. Exit\n";
    cout << "Enter your choice: ";
}

void addItem() {
    Item newItem;
    
    cout << "\nEnter Item ID: ";
    cin >> newItem.id;
    
    if(idExists(newItem.id)) {
        cout << "Error: Item with ID " << newItem.id << " already exists.\n";
        return;
    }
    
    cout << "Enter Item Name: ";
    cin.ignore();
    cin.getline(newItem.name, 50);
    
    cout << "Enter Quantity: ";
    cin >> newItem.quantity;
    
    cout << "Enter Price: ";
    cin >> newItem.price;
    
    saveItemToFile(newItem);
    cout << "Item added successfully!\n";
}

void viewAllItems() {
    ifstream file(FILENAME, ios::binary);
    
    if(!file) {
        cout << "No items in inventory.\n";
        return;
    }
    cout << "\n";
    cout << left <<setw(8) << "ID" 
         << left << setw(20) << "Name" 
         << right << setw(8) << "Qty" 
         << right << setw(12) << "Price" << "\n";
    cout << "----------------------------------------\n";
    
    Item currentItem;
    while(file.read((char*)&currentItem, sizeof(Item))) {
        cout << left << setw(8) << currentItem.id 
             << left << setw(20) << currentItem.name 
             << right << setw(8) << currentItem.quantity 
             << right << setw(12) << fixed << setprecision(2) << currentItem.price << "\n";
    }
    
    file.close();
}
void searchItemByID() {
    int searchId;
    cout << "Enter Item ID to search: ";
    cin >> searchId;
    
    ifstream file(FILENAME, ios::binary);
    bool found = false;
    Item currentItem;
    
    while(file.read((char*)&currentItem, sizeof(Item))) {
        if(currentItem.id == searchId) {
            cout << "\nItem Found:\n";
            cout << "ID: " << currentItem.id << "\n";
            cout << "Name: " << currentItem.name << "\n";
            cout << "Quantity: " << currentItem.quantity << "\n";
            cout << "Price: " << currentItem.price << "\n";
            found = true;
            break;
        }
    }
    
    if(!found) {
        cout << "Item with ID " << searchId << " not found.\n";
    }
    
    file.close();
}

void updateQuantity() {
    int itemId, newQuantity;
    cout << "Enter Item ID to update: ";
    cin >> itemId;
    
    if(!idExists(itemId)) {
        cout << "Item with ID " << itemId << " not found.\n";
        return;
    }
    
    cout << "Enter new quantity: ";
    cin >> newQuantity;
    
    if(newQuantity < 0) {
        cout << "Error: Quantity cannot be negative.\n";
        return;
    }
    
    fstream file(FILENAME, ios::binary | ios::in | ios::out);
    Item currentItem;
    streampos position;
    
    while(file.read((char*)&currentItem, sizeof(Item))) {
        if(currentItem.id == itemId) {
            position = file.tellg() - (streampos)sizeof(Item);
            currentItem.quantity = newQuantity;
            file.seekp(position);
            file.write((char*)&currentItem, sizeof(Item));
            cout << "Quantity updated successfully!\n";
            break;
        }
    }
    
    file.close();
}

void deleteItem() {
    int itemId;
    cout << "Enter Item ID to delete: ";
    cin >> itemId;
    
    if(!idExists(itemId)) {
        cout << "Item with ID " << itemId << " not found.\n";
        return;
    }
    
    rewriteFileAfterDeletion(itemId);
    cout << "Item deleted successfully!\n";
}

bool idExists(int id) {
    ifstream file(FILENAME, ios::binary);
    Item currentItem;
    
    while(file.read((char*)&currentItem, sizeof(Item))) {
        if(currentItem.id == id) {
            file.close();
            return true;
        }
    }
    
    file.close();
    return false;
}

void saveItemToFile(const Item& item) {
    ofstream file(FILENAME, ios::binary | ios::app);
    file.write((char*)&item, sizeof(Item));
    file.close();
}

void rewriteFileAfterDeletion(int idToDelete) {
    ifstream inFile(FILENAME, ios::binary);
    ofstream outFile(TEMP_FILENAME, ios::binary);
    Item currentItem;
    
    while(inFile.read((char*)&currentItem, sizeof(Item))) {
        if(currentItem.id != idToDelete) {
            outFile.write((char*)&currentItem, sizeof(Item));
        }
    }
    
    inFile.close();
    outFile.close();
    
    remove(FILENAME);
    rename(TEMP_FILENAME, FILENAME);
}