#include <iostream>
#include <fstream>
#include <vector>
#include <algorithm>
#include <string>
#include <iomanip>
#include <limits>

using namespace std;
class LibraryItem {
protected:
    string title;
    string author;
    int id;
    bool checkedOut;

public:
    LibraryItem(string t, string a, int i) : title(t), author(a), id(i), checkedOut(false) {}
    virtual ~LibraryItem() {}

    virtual void display() const = 0; 
    virtual string getType() const = 0;

    int getId() const { return id; }
    string getTitle() const { return title; }
    bool isCheckedOut() const { return checkedOut; }

    void checkOut() { checkedOut = true; }
    void checkIn() { checkedOut = false; }
};

class Book : public LibraryItem {
    int pages;

public:
    Book(string t, string a, int i, int p) : LibraryItem(t, a, i), pages(p) {}
    ~Book() {}

    void display() const override {
        cout << "ID: " << id << " | Type: Book | Title: " << title 
             << " | Author: " << author << " | Pages: " << pages 
             << " | Status: " << (checkedOut ? "Checked Out" : "Available") << endl;
    }

    string getType() const override { return "Book"; }
};

class DVD : public LibraryItem {
    int duration; 

public:
    DVD(string t, string a, int i, int d) : LibraryItem(t, a, i), duration(d) {}
    ~DVD() {}

    void display() const override {
        cout << "ID: " << id << " | Type: DVD | Title: " << title 
             << " | Author/Director: " << author << " | Duration: " << duration 
             << " min | Status: " << (checkedOut ? "Checked Out" : "Available") << endl;
    }

    string getType() const override { return "DVD"; }
};
class LibraryManager {
private:
    vector<LibraryItem*> items;
    int nextId;

    void saveToFile() {
        ofstream outFile("library_data.txt");
        if (!outFile) {
            cerr << "Error opening file for writing!" << endl;
            return;
        }

        for (const auto& item : items) {
            outFile << item->getType() << ","
                   << item->getId() << ","
                   << item->getTitle() << ","
                   << item->isCheckedOut() << "\n";
        }

        outFile.close();
    }

    void loadFromFile() {
        ifstream inFile("library_data.txt");
        if (!inFile) {
            return;
        }

        string line;
        while (getline(inFile, line)) {
            size_t pos1 = line.find(',');
            size_t pos2 = line.find(',', pos1 + 1);
            size_t pos3 = line.find(',', pos2 + 1);

            string type = line.substr(0, pos1);
            int id = stoi(line.substr(pos1 + 1, pos2 - pos1 - 1));
            string title = line.substr(pos2 + 1, pos3 - pos2 - 1);
            bool checkedOut = (line.substr(pos3 + 1) == "1");
            if (type == "Book") {
                items.push_back(new Book(title, "Unknown", id, 0));
            } else if (type == "DVD") {
                items.push_back(new DVD(title, "Unknown", id, 0));
            }

            if (checkedOut) {
                items.back()->checkOut();
            }

            if (id >= nextId) {
                nextId = id + 1;
            }
        }

        inFile.close();
    }

public:
    LibraryManager() : nextId(1) {
        loadFromFile();
    }

    ~LibraryManager() {
        saveToFile();
        for (auto item : items) {
            delete item;
        }
    }

    void addItem() {
        cout << "\nAdd New Item\n";
        cout << "1. Book\n2. DVD\nEnter choice: ";
        int choice;
        cin >> choice;
        cin.ignore();

        string title, author;
        cout << "Enter title: ";
        getline(cin, title);
        cout << "Enter author/director: ";
        getline(cin, author);

        if (choice == 1) {
            int pages;
            cout << "Enter number of pages: ";
            cin >> pages;
            items.push_back(new Book(title, author, nextId++, pages));
        } else if (choice == 2) {
            int duration;
            cout << "Enter duration in minutes: ";
            cin >> duration;
            items.push_back(new DVD(title, author, nextId++, duration));
        } else {
            cout << "Invalid choice!\n";
            return;
        }

        cout << "Item added successfully!\n";
    }

    void displayAllItems() const {
        if (items.empty()) {
            cout << "No items in the library.\n";
            return;
        }

        cout << "\nLibrary Items:\n";
        for (const auto& item : items) {
            item->display();
        }
    }

    void checkoutItem() {
        int id;
        cout << "Enter item ID to checkout: ";
        cin >> id;

        auto it = find_if(items.begin(), items.end(), 
            [id](const LibraryItem* item) { return item->getId() == id; });

        if (it != items.end()) {
            if ((*it)->isCheckedOut()) {
                cout << "Item is already checked out.\n";
            } else {
                (*it)->checkOut();
                cout << "Item checked out successfully.\n";
            }
        } else {
            cout << "Item not found.\n";
        }
    }

    void returnItem() {
        int id;
        cout << "Enter item ID to return: ";
        cin >> id;

        auto it = find_if(items.begin(), items.end(), 
            [id](const LibraryItem* item) { return item->getId() == id; });

        if (it != items.end()) {
            if (!(*it)->isCheckedOut()) {
                cout << "Item was not checked out.\n";
            } else {
                (*it)->checkIn();
                cout << "Item returned successfully.\n";
            }
        } else {
            cout << "Item not found.\n";
        }
    }

    void sortItemsByTitle() {
        sort(items.begin(), items.end(), 
            [](const LibraryItem* a, const LibraryItem* b) {
                return a->getTitle() < b->getTitle();
            });
        cout << "Items sorted by title.\n";
    }
};

void displayMenu() {
    cout << "\nLibrary Management System\n";
    cout << "1. Add New Item\n";
    cout << "2. Display All Items\n";
    cout << "3. Check Out Item\n";
    cout << "4. Return Item\n";
    cout << "5. Sort Items by Title\n";
    cout << "6. Exit\n";
    cout << "Enter your choice: ";
}

int main() {
    LibraryManager library;
    int choice;

    do {
        displayMenu();
        cin >> choice;
        cin.ignore();

        switch (choice) {
            case 1:
                library.addItem();
                break;
            case 2:
                library.displayAllItems();
                break;
            case 3:
                library.checkoutItem();
                break;
            case 4:
                library.returnItem();
                break;
            case 5:
                library.sortItemsByTitle();
                break;
            case 6:
                cout << "Exiting...\n";
                break;
            default:
                cout << "Invalid choice. Please try again.\n";
        }
    } while (choice != 6);

    return 0;
}