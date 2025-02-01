#include <iostream>
#include <map>
#include <vector>
#include <ctime>

using namespace std;

struct Product {
    string name;
    string category;
    double price;
    int stock;
    string expiryDate;
};

map<int, Product> inventory;
double totalRevenue = 0.0;

void addProduct() {
    int id;
    string name, category, expiryDate;
    double price;
    int stock;
    
    cout << "Enter Product ID: ";
    cin >> id;
    cout << "Enter Product Name: ";
    cin >> name;
    cout << "Enter Category: ";
    cin >> category;
    cout << "Enter Price: ";
    cin >> price;
    cout << "Enter Stock: ";
    cin >> stock;
    cout << "Enter Expiry Date (DD/MM/YYYY): ";
    cin >> expiryDate;

    if (inventory.find(id) != inventory.end()) {
        cout << "Product ID already exists!\n";
        return;
    }

    inventory[id] = {name, category, price, stock, expiryDate};
    cout << "Product added successfully!\n";
}

void viewProducts() {
    if (inventory.empty()) {
        cout << "No products available.\n";
        return;
    }
    
    for (auto& item : inventory) {
        cout << "ID: " << item.first << " | Name: " << item.second.name 
             << " | Category: " << item.second.category 
             << " | Price: $" << item.second.price 
             << " | Stock: " << item.second.stock 
             << " | Expiry: " << item.second.expiryDate << "\n";
    }
}

void searchProduct() {
    int id;
    cout << "Enter Product ID to search: ";
    cin >> id;

    if (inventory.find(id) == inventory.end()) {
        cout << "Product not found!\n";
        return;
    }

    Product p = inventory[id];
    cout << "Name: " << p.name << " | Category: " << p.category 
         << " | Price: $" << p.price << " | Stock: " << p.stock 
         << " | Expiry Date: " << p.expiryDate << "\n";
}

void updateProduct() {
    int id;
    cout << "Enter Product ID to update: ";
    cin >> id;

    if (inventory.find(id) == inventory.end()) {
        cout << "Product not found!\n";
        return;
    }

    double newPrice;
    int newStock;
    cout << "Enter New Price: ";
    cin >> newPrice;
    cout << "Enter New Stock: ";
    cin >> newStock;

    inventory[id].price = newPrice;
    inventory[id].stock = newStock;

    cout << "Product updated successfully!\n";
}

void sellProduct() {
    int id, quantity;
    cout << "Enter Product ID to sell: ";
    cin >> id;

    if (inventory.find(id) == inventory.end()) {
        cout << "Product not found!\n";
        return;
    }

    cout << "Enter Quantity to sell: ";
    cin >> quantity;

    if (quantity > inventory[id].stock) {
        cout << "Not enough stock!\n";
        return;
    }

    double discount = 0.0;
    if (quantity >= 10) discount = 0.10;
    else if (quantity >= 20) discount = 0.20;

    double totalPrice = inventory[id].price * quantity;
    totalPrice -= totalPrice * discount;

    inventory[id].stock -= quantity;
    totalRevenue += totalPrice;

    cout << "Sold " << quantity << " of " << inventory[id].name 
         << " | Total: $" << totalPrice << " (Discount Applied: " << discount * 100 << "%)\n";
}

void removeProduct() {
    int id;
    cout << "Enter Product ID to remove: ";
    cin >> id;

    if (inventory.erase(id)) {
        cout << "Product removed successfully.\n";
    } else {
        cout << "Product not found!\n";
    }
}

void restockProducts() {
    for (auto& item : inventory) {
        if (item.second.stock < 5) {
            item.second.stock += 10;
            cout << "Restocked " << item.second.name << " | New Stock: " << item.second.stock << "\n";
        }
    }
}

void salesReport() {
    cout << "Total Revenue: $" << totalRevenue << "\n";
}

bool adminLogin() {
    string username, password;
    cout << "Enter Admin Username: ";
    cin >> username;
    cout << "Enter Password: ";
    cin >> password;
    return (username == "admin" && password == "1234");
}

bool cashierLogin() {
    string username, password;
    cout << "Enter Cashier Username: ";
    cin >> username;
    cout << "Enter Password: ";
    cin >> password;
    return (username == "cashier" && password == "5678");
}

void adminPanel() {
    if (!adminLogin()) {
        cout << "Incorrect login credentials!\n";
        return;
    }

    int choice;
    do {
        cout << "\n--- Admin Panel ---\n";
        cout << "1. Add Product\n2. View Products\n3. Update Product\n4. Remove Product\n5. Restock Products\n6. View Sales Report\n7. Logout\nEnter choice: ";
        cin >> choice;

        if (choice == 1) addProduct();
        else if (choice == 2) viewProducts();
        else if (choice == 3) updateProduct();
        else if (choice == 4) removeProduct();
        else if (choice == 5) restockProducts();
        else if (choice == 6) salesReport();

    } while (choice != 7);
}

void cashierPanel() {
    if (!cashierLogin()) {
        cout << "Incorrect login credentials!\n";
        return;
    }

    int choice;
    do {
        cout << "\n--- Cashier Panel ---\n";
        cout << "1. View Products\n2. Search Product\n3. Sell Product\n4. Logout\nEnter choice: ";
        cin >> choice;

        if (choice == 1) viewProducts();
        else if (choice == 2) searchProduct();
        else if (choice == 3) sellProduct();

    } while (choice != 4);
}

int main() {
    int choice;
    do {
        cout << "\n1. Admin Login\n2. Cashier Login\n3. Exit\nEnter choice: ";
        cin >> choice;

        if (choice == 1) adminPanel();
        else if (choice == 2) cashierPanel();

    } while (choice != 3);

    return 0;
}