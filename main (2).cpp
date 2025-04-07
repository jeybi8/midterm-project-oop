#include <iostream>
#include <vector>
#include <iomanip>

using namespace std;

class Item {
private:
    int id;
    string name;
    int quantity;
    float price;
    string category;

public:
    Item(int id, string name, int quantity, float price, string category)
        : id(id), name(name), quantity(quantity), price(price), category(category) {}

    int getId() const { return id; }
    string getName() const { return name; }
    int getQuantity() const { return quantity; }
    float getPrice() const { return price; }
    string getCategory() const { return category; }

    void updateQuantity(int newQuantity) { quantity = newQuantity; }
    void updatePrice(float newPrice) { price = newPrice; }

    void display() const {
        cout << left << setw(5) << id
             << setw(20) << name
             << setw(8) << quantity
             << "$" << right << setw(9) << fixed << setprecision(2) << price
             << "  " << left << setw(15) << category
             << "\n";
    }
};

class Inventory {
private:
    vector<Item> items;
    int nextID = 1;

public:
    void addItem() {
        string name, category;
        int quantity;
        float price;

        cout << "Enter item details:\n";
        cout << "Name: "; cin >> name;
        cout << "Quantity: "; cin >> quantity;
        cout << "Price: "; cin >> price;
        cout << "Category: "; cin >> category;

        items.push_back(Item(nextID++, name, quantity, price, category));
        cout << "Item added successfully!\n";
    }

    void updateItem() {
        int id;
        cout << "Enter item ID to update: "; cin >> id;
        
        for (auto &item : items) {
            if (item.getId() == id) {
                int choice;
                cout << "What would you like to update?\n";
                cout << "1 - Quantity\n2 - Price\nChoice: "; cin >> choice;

                if (choice == 1) {
                    int newQuantity;
                    cout << "New Quantity: "; cin >> newQuantity;
                    item.updateQuantity(newQuantity);
                    cout << "Quantity updated successfully!\n";
                } else if (choice == 2) {
                    float newPrice;
                    cout << "New Price: "; cin >> newPrice;
                    item.updatePrice(newPrice);
                    cout << "Price updated successfully!\n";
                } else {
                    cout << "Invalid choice!\n";
                }
                return;
            }
        }
        cout << "Item not found!\n";
    }

    void removeItem() {
        int id;
        cout << "Enter item ID to remove: "; cin >> id;

        auto it = items.begin();
        while (it != items.end()) {
            if (it->getId() == id) {
                items.erase(it);
                cout << "Item removed successfully!\n";
                return;
            }
            ++it;
        }
        cout << "Item not found!\n";
    }

    void displayAllItems() const {
        if (items.empty()) {
            cout << "Inventory is empty.\n";
            return;
        }

        cout << left << setw(5) << "ID"
             << setw(20) << "Name"
             << setw(8) << "Qty"
             << setw(10) << "Price"
             << setw(15) << "Category" << "\n";

        cout << string(58, '-') << "\n";

        for (const auto &item : items) item.display();
    }

    void searchItem() const {
        int id;
        cout << "Enter item ID to search: "; cin >> id;

        for (const auto &item : items) {
            if (item.getId() == id) {
                cout << "Found: " << item.getName() << " | Qty: " << item.getQuantity() 
                     << " | Price: $" << fixed << setprecision(2) << item.getPrice() << "\n";
                return;
            }
        }
        cout << "Item not found!\n";
    }

    void displayLowStock() const {
        cout << "\nLow Stock Items (Qty ≤ 5):\n";
        for (const auto &item : items) {
            if (item.getQuantity() <= 5) {
                cout << "ID: " << item.getId() << " | Name: " << item.getName() 
                     << " | Qty: " << item.getQuantity() << "\n";
            }
        }
    }

    void sortItems() {
        int option, order;
        cout << "Sort by: 1-Quantity 2-Price: ";
        cin >> option;
        cout << "Order: 1-Ascending 2-Descending: ";
        cin >> order;

        if (option == 1) {
            for (size_t i = 0; i < items.size() - 1; ++i) {
                for (size_t j = i + 1; j < items.size(); ++j) {
                    if ((order == 1 && items[i].getQuantity() > items[j].getQuantity()) || 
                        (order == 2 && items[i].getQuantity() < items[j].getQuantity())) {
                        swap(items[i], items[j]);
                    }
                }
            }
        }
        else if (option == 2) {
            for (size_t i = 0; i < items.size() - 1; ++i) {
                for (size_t j = i + 1; j < items.size(); ++j) {
                    if ((order == 1 && items[i].getPrice() > items[j].getPrice()) || 
                        (order == 2 && items[i].getPrice() < items[j].getPrice())) {
                        swap(items[i], items[j]);
                    }
                }
            }
        } else {
            cout << "Invalid option!\n";
            return;
        }
        cout << "Items sorted successfully!\n";
    }
};

int main() {
    Inventory store;
    int choice;
    do {
        cout << "\nMenu\n";
        cout << "1 - Add Item\n";
        cout << "2 - Update Item\n";
        cout << "3 - Remove Item\n";
        cout << "4 - Display All Items\n";
        cout << "5 - Search Item\n";
        cout << "6 - Sort Items\n";
        cout << "7 - Display Low Stock Items\n";
        cout << "8 - Exit\n";
        cout << "Choice: ";
        cin >> choice;

        switch (choice) {
            case 1: store.addItem(); break;
            case 2: store.updateItem(); break;
            case 3: store.removeItem(); break;
            case 4: store.displayAllItems(); break;
            case 5: store.searchItem(); break;
            case 6: store.sortItems(); break;
            case 7: store.displayLowStock(); break;
            case 8: 
                cout << "Exiting the program...\n";
                break;
            default: cout << "Invalid choice!\n";
        }
    } while (choice != 8);

    return 0;
}
