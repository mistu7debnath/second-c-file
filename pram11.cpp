//Design a c++ class to manage a shopping list, allowing addition, removal and display of items along with total cost calculation
#include <iostream>
#include <vector>
#include <string>
#include <sstream>  
using namespace std;
struct Item {
    string name;
    int quantity;
    double price_per_unit;

    // Constructor
    Item(string n, int q, double p) : name(n), quantity(q), price_per_unit(p) {}
};

class ShoppingList {
private:
    vector<Item> items;  // A vector to store the items in the shopping list

    // Helper function to format a double value to 2 decimal places
    string formatPrice(double value) const {
        ostringstream stream;
        stream.precision(2);  // Set precision to 2 decimal places
        stream << fixed << value;
        return stream.str();
    }

public:
    // Function to add an item to the list
    void addItem(const string& name, int quantity, double price_per_unit) {
        items.push_back(Item(name, quantity, price_per_unit));
    }

    // Function to remove an item by name
    void removeItem(const string& name) {
        for (auto it = items.begin(); it != items.end(); ++it) {
            if (it->name == name) {
                items.erase(it);
                cout << "Item removed: " << name << endl;
                return;
            }
        }
        cout << "Item not found: " << name << endl;
    }

    // Function to display the shopping list
    void displayList() const {
        if (items.empty()) {
            cout << "Shopping list is empty." << endl;
            return;
        }

        cout << "Item               Quantity    Price/unit   Total Price" << endl;
        cout << "---------------------------------------------------------" << endl;

        for (const auto& item : items) {
            // Display in a simple tabular format with manual spacing
            cout << item.name << string(20 - item.name.length(), ' ')  // Adjust spacing
                 << item.quantity << string(12, ' ')                   // Static spacing for quantity
                 << formatPrice(item.price_per_unit) << string(7, ' ')  // Static spacing for price per unit
                 << formatPrice(item.quantity * item.price_per_unit) << endl;
        }
    }

    // Function to calculate the total cost of the shopping list
    double calculateTotalCost() const {
        double total = 0;
        for (const auto& item : items) {
            total += item.quantity * item.price_per_unit;
        }
        return total;
    }
};

// Test the ShoppingList class
int main() {
    ShoppingList shoppingList;
    
    shoppingList.addItem("Apple", 3, 0.99);
    shoppingList.addItem("Bread", 2, 2.50);
    shoppingList.addItem("Milk", 1, 1.20);

    cout << "Shopping List:" << endl;
    shoppingList.displayList();

    cout << "Total Cost: $" << shoppingList.calculateTotalCost() << endl;

    shoppingList.removeItem("Bread");

    cout << "\nUpdated Shopping List:" << endl;
    shoppingList.displayList();

    cout << "Updated Total Cost: $" << shoppingList.calculateTotalCost() << endl;

    return 0;
}
