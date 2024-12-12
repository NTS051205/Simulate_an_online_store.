#include <iostream>
#include <vector>
#include <string>
#include <fstream>
#include <algorithm>
#include <unordered_map>

using namespace std;

class Product {
private:
    int id;
    string name;
    double price;
    int stock;
    vector<pair<string,int>> reviews;

public:
    Product(int id, const string& name, double price, int stock)
        : id(id), name(name), price(price), stock(stock) {}

    int getId() const { return id; }
    string getName() const { return name; }
    double getPrice() const { return price; }
    int getStock() const { return stock; }
    
    void setStock(int newStock) { stock = newStock; }
    
    void addReview(const string &username,int rating){
        reviews.push_back({username,rating});}
    
    const vector<pair<string,int>> &getReviews() const {
        return reviews;
    }
    void displayReviews() const {
        if (reviews.empty()) {
            cout << "No reviews yet.\n";
        } else {
            cout << "\n--- Reviews for " << name << " ---\n";
            for (const auto& review : reviews) {
                cout << "User: " << review.first << " | Rating: " << review.second << "\n";
            }
        }
    }
};
class Promotion {
private:
    int promotionId;
    string description;
    double discountPercentage;
    vector<int> applicableProductIds;

public:
    Promotion(int id, const string& desc, double discount, const vector<int>& productIds)
        : promotionId(id), description(desc), discountPercentage(discount), applicableProductIds(productIds) {}

    double getDiscount() const { return discountPercentage; }
    
    bool isApplicable(int productId) const {
        return find(applicableProductIds.begin(), applicableProductIds.end(), productId) != applicableProductIds.end();
    }

    string getDescription() const { return description; }

    int getId() const { return promotionId; }

    const vector<int>& getApplicableProducts() const { return applicableProductIds; }
};
class Customer {
private:
    string username;
    string password;
    string email;

public:
    Customer(const string& username, const string& password, const string& email)
        : username(username), password(password), email(email) {}

    string getUsername() const { return username; }
    string getPassword() const { return password; }
    string getEmail() const { return email; }
};

class Cart {
private:
    vector<pair<Product, int>> items; 

public:
    void addProduct(const Product& product, int quantity) {
        for (auto& item : items) {
            if (item.first.getId() == product.getId()) {
                item.second += quantity;
                return;
            }
        }
        items.push_back({product, quantity});
    }

    void removeProduct(int productId) {
        items.erase(
            remove_if(items.begin(), items.end(), [productId](const pair<Product, int>& item) {
                return item.first.getId() == productId;
            }),
            items.end());
    }
    double calculateTotal(const vector<Promotion>& promotions) const {
        double total = 0.0;
        for (const auto& item : items) {
            double discount = 0.0;
            for (const auto& promo : promotions) {
                if (promo.isApplicable(item.first.getId())) {
                    discount = promo.getDiscount();
                    break;
                }
            }
            total += item.first.getPrice() * item.second * (1 - discount / 100);
        }
        return total;
    }
    void viewCart() const {
        cout << "\n--- Cart ---\n";
        for (const auto& item : items) {
            cout << "Product: " << item.first.getName() << " | Quantity: " << item.second
                 << " | Price: " << item.first.getPrice() << "\n";
        }
    }

    const vector<pair<Product, int>>& getItems() const {
        return items;
    }
    void clearCart() { items.clear(); }

};

// class Order {
// private:
//     int orderId;
//     Customer customer;
//     vector<pair<Product, int>> items;
//     double totalAmount;

// public:
//     Order(int orderId, const Customer& customer, const vector<pair<Product, int>>& items)
//         : orderId(orderId), customer(customer), items(items), totalAmount(0.0) {
//         for (const auto& item : items) {
//             totalAmount += item.first.getPrice() * item.second;
//         }
//     }

//     void viewOrder() const {
//         cout << "\n--- Order Summary ---\n";
//         cout << "Order ID: " << orderId << "\n";
//         cout << "Customer: " << customer.getUsername() << " (" << customer.getEmail() << ")\n";
//         for (const auto& item : items) {
//             cout << "Product: " << item.first.getName() << " | Quantity: " << item.second
//                  << " | Price: " << item.first.getPrice() << "\n";
//         }
//         cout << "Total Amount: " << totalAmount << "\n";
//     }
// };

class Order {
private:
    int orderId;
    string customerUsername;
    vector<pair<Product, int>> items;
    double totalAmount;

public:
    Order(int orderId, const string& username, const vector<pair<Product, int>>& items, double total)
        : orderId(orderId), customerUsername(username), items(items), totalAmount(total) {}

    void viewOrder() const {
        cout << "\n--- Order Summary ---\n";
        cout << "Order ID: " << orderId << "\n";
        cout << "Customer: " << customerUsername << "\n";
        for (const auto& item : items) {
            cout << "Product: " << item.first.getName() << " | Quantity: " << item.second
                 << " | Price: " << item.first.getPrice() << "\n";
        }
        cout << "Total Amount: " << totalAmount << "\n";
    }
     const vector<pair<Product, int>>& getItems() const {
        return items;
    }
};

struct User {
    string username;
    string password;
};
/*
bool login(vector<User>& users, const string& filename, string& loggedInUser) {
    int choice;
    cout << "\n--- Login Menu ---\n";
    cout << "1. Register\n2. Login\nEnter your choice: ";
    cin >> choice;

    if (choice == 1) {
        User newUser;
        cout << "Enter Username: ";
        cin >> newUser.username;
        cout << "Enter Password: ";
        cin >> newUser.password;

        users.push_back(newUser);
        ofstream outFile(filename, ios::app);
        outFile << newUser.username << "," << newUser.password << "\n";
        outFile.close();

        loggedInUser = newUser.username;
        cout << "Registration successful!\n";
        return true;
    } else if (choice == 2) {
        string username, password;
        cout << "Enter Username: ";
        cin >> username;
        cout << "Enter Password: ";
        cin >> password;

        for (const auto& user : users) {
            if (user.username == username && user.password == password) {
                loggedInUser = username;
                cout << "Login successful!\n";
                return true;
            }
        }
        cout << "Invalid username or password!\n";
        return false;
    }
    return false;
}
*/
bool login(vector<User>& users, const string& filename, string& loggedInUser) {
    int choice;
    do {
        system("cls"); 
        cout << "\n--- Login Menu ---\n";
        cout << "1. Register\n2. Login\n3. Exit\nEnter your choice: ";
        cin >> choice;

        if (choice == 1) {
            system("cls");
            User newUser;
            cout << "--- Register ---\n";
            cout << "Enter Username: ";
            cin >> newUser.username;
            cout << "Enter Password: ";
            cin >> newUser.password;

            users.push_back(newUser);
            ofstream outFile(filename, ios::app);
            outFile << newUser.username << "," << newUser.password << "\n";
            outFile.close();

            loggedInUser = newUser.username;
            cout << "Registration successful! Please log in.\n";
            system("pause");
        } else if (choice == 2) {
            string username, password;
            do {
                system("cls");
                cout << "--- Login ---\n";
                cout << "Enter Username: ";
                cin >> username;
                cout << "Enter Password: ";
                cin >> password;
                bool isValid = false;
                for (const auto& user : users) {
                    if (user.username == username && user.password == password) {
                        loggedInUser = username;
                        cout << "Login successful! Welcome, " << loggedInUser << ".\n";
                        system("pause");
                        return true; 
                    }
                }

                cout << "Invalid username or password. Please try again.\n";
                system("pause");

            } while (true);

        } else if (choice == 3) {
            cout << "Exiting login menu.\n";
            return false; 
        } else {
            cout << "Invalid choice. Please try again.\n";
            system("pause");
        }
    } while (true); 
}

vector<User> loadUsersFromFile(const string& filename) {
    vector<User> users;
    ifstream inFile(filename);
    string line;
    while (getline(inFile, line)) {
        User user;
        size_t pos = line.find(',');
        user.username = line.substr(0, pos);
        line.erase(0, pos + 1);
        user.password = line;
        users.push_back(user);
    }
    inFile.close();
    return users;
}

void saveUsersToFile(const vector<User>& users, const string& filename) {
    ofstream outFile(filename);
    for (const auto& user : users) {
        outFile << user.username << "," << user.password << "\n";
    }
    outFile.close();
}

unordered_map<string, string> loadAdminCredentials(const string& filename) {
    unordered_map<string, string> credentials;
    ifstream inFile(filename);
    string line;
    while (getline(inFile, line)) {
        size_t pos = line.find(',');
        string username = line.substr(0, pos);
        string password = line.substr(pos + 1);
        credentials[username] = password;
    }
    inFile.close();
    return credentials;
}
void savePromotionsToFile(const vector<Promotion>& promotions, const string& filename) {
    ofstream outFile(filename);
    for (const auto& promo : promotions) {
        outFile << promo.getId() << "," << promo.getDescription() << "," << promo.getDiscount();
        for (const auto& productId : promo.getApplicableProducts()) {
            outFile << "," << productId;
        }
        outFile << "\n";
    }
    outFile.close();
}

vector<Promotion> loadPromotionsFromFile(const string& filename) {
    vector<Promotion> promotions;
    ifstream inFile(filename);
    string line;
    while (getline(inFile, line)) {
        int promoId;
        string description;
        double discount;
        vector<int> productIds;

        size_t pos = 0;
        pos = line.find(',');
        promoId = stoi(line.substr(0, pos));
        line.erase(0, pos + 1);

        pos = line.find(',');
        description = line.substr(0, pos);
        line.erase(0, pos + 1);

        pos = line.find(',');
        discount = stod(line.substr(0, pos));
        line.erase(0, pos + 1);

        while ((pos = line.find(',')) != string::npos) {
            productIds.push_back(stoi(line.substr(0, pos)));
            line.erase(0, pos + 1);
        }
        productIds.push_back(stoi(line));

        promotions.emplace_back(promoId, description, discount, productIds);
    }
    inFile.close();
    return promotions;
}
void saveProductsToFile(const vector<Product>& products, const string& filename) {
    ofstream outFile(filename);
    for (const auto& product : products) {
        outFile << product.getId() << "," << product.getName() << "," << product.getPrice()
                << "," << product.getStock() << "\n";
    }
    outFile.close();
}

// void saveReviewsToFile(const vector<Product>& products, const string& filename) {
//     ofstream outFile(filename);
//     for (const auto& product : products) {
//         for (const auto& review : product.getReviews()) {
//             outFile << product.getId() << "," << review.first << "," << review.second << "\n";
//         }
//     }
//     outFile.close();
// }
void saveReviewsToFile(const vector<Product>& products, const string& filename) {
    ofstream outFile(filename, ios::app); // Open in append mode
    for (const auto& product : products) {
        for (const auto& review : product.getReviews()) {
            outFile << product.getId() << "," << product.getName() << "," << review.first << "," << review.second << "\n";
        }
    }
    outFile.close();
}
vector<Product> loadProductsFromFile(const string& filename) {
    vector<Product> products;
    ifstream inFile(filename);
    string line;
    while (getline(inFile, line)) {
        int id, stock;
        double price;
        string name;
        
        size_t pos = 0;

        pos = line.find(',');
        id = stoi(line.substr(0, pos));
        line.erase(0, pos + 1);

        pos = line.find(',');
        name = line.substr(0, pos);
        line.erase(0, pos + 1);

        pos = line.find(',');
        price = stod(line.substr(0, pos));
        line.erase(0, pos + 1);

        stock = stoi(line);

        products.emplace_back(id, name, price, stock);
    }
    inFile.close();
    return products;
}

void managerMenu(vector<Product>& products, vector<Promotion>& promotions, vector<User>& users, const string& userFile) {
    const string adminUsername = "nguyentienson0512@gmail.com";
    const string adminPassword = "son05122005";

    cout << "\n--- Admin Login ---\n";
    string username, password;
    cout << "Username: ";
    cin >> username;
    cout << "Password: ";
    cin >> password;

    if (username == adminUsername && password == adminPassword) {
        int choice;
        do {
            system("cls");
            cout << "\n--- Admin Menu ---\n";
            cout << "1. Add Product\n2. Edit Product\n3. Delete Product\n4. View Products\n5. Add Promotion\n";
            cout << "6. View Promotions\n7. View Users\n8. Edit Users\n9. Delete Users\n10. Exit\n";
            cout << "Enter your choice: ";
            cin >> choice;
            system("cls");
            switch (choice) {
                case 1: { 
                    cout << "--- Add Product ---\n";
                    int id, stock;
                    double price;
                    string name;
                    cout << "Enter Product ID: ";
                    cin >> id;
                    cout << "Enter Product Name: ";
                    cin.ignore();
                    getline(cin, name);
                    cout << "Enter Product Price: ";
                    cin >> price;
                    cout << "Enter Stock Quantity: ";
                    cin >> stock;
                    products.emplace_back(id, name, price, stock);
                    saveProductsToFile(products, "admin.txt");
                    cout << "Product added successfully!\n";
                    system("pause"); 
                    break;
                }
                case 2: { 
                    cout << "--- Edit Product ---\n";
                    int id;
                    cout << "Enter Product ID to Edit: ";
                    cin >> id;
                    for (auto& product : products) {
                        if (product.getId() == id) {
                            double price;
                            int stock;
                            string name;
                            cout << "Enter New Product Name: ";
                            cin.ignore();
                            getline(cin, name);
                            cout << "Enter New Product Price: ";
                            cin >> price;
                            cout << "Enter New Stock Quantity: ";
                            cin >> stock;
                            product = Product(id, name, price, stock);
                            saveProductsToFile(products, "admin.txt");
                            cout << "Product updated successfully.\n";
                            break;
                        }
                    }
                    system("pause");
                    break;
                }
                case 3: { 
                    cout << "--- Delete Product ---\n";
                    int id;
                    cout << "Enter Product ID to Delete: ";
                    cin >> id;
                    products.erase(remove_if(products.begin(), products.end(), [id](const Product& p) {
                        return p.getId() == id;
                    }), products.end());
                    saveProductsToFile(products, "admin.txt");
                    cout << "Product deleted successfully.\n";
                    system("pause");
                    break;
                }
                case 4: { 
                    cout << "--- View Products ---\n";
                    for (const auto& product : products) {
                        cout << "ID: " << product.getId() << " | Name: " << product.getName()
                             << " | Price: " << product.getPrice() << " | Stock: " << product.getStock() << "\n";
                    }
                    system("pause");
                    break;
                }
                case 5: { 
                    cout << "--- Add Promotion ---\n";
                    int promoId;
                    string description;
                    double discount;
                    int productId;
                    cout << "Enter Promotion ID: ";
                    cin >> promoId;
                    cout << "Enter Description: ";
                    cin.ignore();
                    getline(cin, description);
                    cout << "Enter Discount Percentage: ";
                    cin >> discount;
                    cout << "Enter Product ID to Apply Promotion: ";
                    cin >> productId;
                    promotions.emplace_back(promoId, description, discount, vector<int>{productId});
                    savePromotionsToFile(promotions, "admin1.txt");
                    cout << "Promotion added successfully.\n";
                    system("pause");
                    break;
                }
                case 6: { 
                    cout << "--- View Promotions ---\n";
                    promotions = loadPromotionsFromFile("admin1.txt");
                    for (const auto& promo : promotions) {
                        cout << "Promotion ID: " << promo.getId() << " | Description: " << promo.getDescription()
                             << " | Discount: " << promo.getDiscount() << "%\n";
                    }
                    system("pause");
                    break;
                }
                case 7: { 
                    cout << "--- View Users ---\n";
                    for (const auto& user : users) {
                        cout << "Username: " << user.username << "\n";
                    }
                    system("pause");
                    break;
                }
                case 8: { 
                    cout << "--- Edit Users ---\n";
                    string editUsername;
                    cout << "Enter the username to edit: ";
                    cin >> editUsername;
                    auto it = find_if(users.begin(), users.end(), [&](const User& u) {
                        return u.username == editUsername;
                    });
                    if (it != users.end()) {
                        cout << "Enter new password for " << editUsername << ": ";
                        cin >> it->password;
                        saveUsersToFile(users, userFile);
                        cout << "Password updated successfully!\n";
                    } else {
                        cout << "User not found!\n";
                    }
                    system("pause");
                    break;
                }
                case 9: { 
                    cout << "--- Delete Users ---\n";
                    string deleteUsername;
                    cout << "Enter the username to delete: ";
                    cin >> deleteUsername;
                    auto it = remove_if(users.begin(), users.end(), [&](const User& u) {
                        return u.username == deleteUsername;
                    });
                    if (it != users.end()) {
                        users.erase(it, users.end());
                        saveUsersToFile(users, userFile);
                        cout << "User deleted successfully!\n";
                    } else {
                        cout << "User not found!\n";
                    }
                    system("pause");
                    break;
                }
                case 10: {
                    cout << "Exiting Admin Menu...\n";
                    break;
                }
                default: {
                    cout << "Invalid choice. Please try again.\n";
                    system("pause");
                    break;
                }
            }
        } while (choice != 10);
    } else {
        cout << "Invalid admin credentials!\n";
    }
};
/*
void managerMenu(vector<Product>& products,vector<Promotion>& promotions,vector<User>& users, const string& userFile) {
    const string adminUsername = "nguyentienson0512@gmail.com";
    const string adminPassword = "son05122005";

    cout << "\n--- Admin Login ---\n";
    string username, password;
    cout << "Username: ";
    cin >> username;
    cout << "Password: ";
    cin >> password;

    if (username == adminUsername && password == adminPassword) {
        int choice;
        do {
            system("cls");
            cout << "\n--- Admin Menu ---\n";
            cout << "1. Add Product\n2. Edit Product\n3. Delete Product\n4. View Products\n5.Add Promotio\n6.View Promotion\n7.View Users\n8.Edit Users\n9.Delete Users\n10. Exit\n";
            cout << "Enter your choice: ";
            cin >> choice;
            system("cls");
            if (choice == 1) {
                int id, stock;
                double price;
                string name;
                cout << "Enter Product ID: ";
                cin >> id;
                cout << "Enter Product Name: ";
                cin.ignore();
                getline(cin, name);
                cout << "Enter Product Price: ";
                cin >> price;
                cout << "Enter Stock Quantity: ";
                cin >> stock;
                products.emplace_back(id, name, price, stock);
                saveProductsToFile(products, "admin.txt");
                cout<<"Product added successfully";
               
            } else if (choice == 2) {
                int id;
                cout << "Enter Product ID to Edit: ";
                cin >> id;
                for (auto& product : products) {
                    if (product.getId() == id) {
                        double price;
                        int stock;
                        string name;
                        cout << "Enter New Product Name: ";
                        cin.ignore();
                        getline(cin, name);
                        cout << "Enter New Product Price: ";
                        cin >> price;
                        cout << "Enter New Stock Quantity: ";
                        cin >> stock;
                        product = Product(id, name, price, stock);
                        saveProductsToFile(products, "admin.txt");
                        cout << "Product updated successfully.\n";
                        break;
                    }
                }
            } else if (choice == 3) {
                int id;
                cout << "Enter Product ID to Delete: ";
                cin >> id;
                products.erase(remove_if(products.begin(), products.end(), [id](const Product& p) {
                    return p.getId() == id;
                }), products.end());
                saveProductsToFile(products, "admin.txt");
                cout << "Product deleted successfully.\n";
            } else if (choice == 4) {
                for (const auto& product : products) {
                    cout << "ID: " << product.getId() << " | Name: " << product.getName()
                         << " | Price: " << product.getPrice() << " | Stock: " << product.getStock() << "\n";
                }
            } else if( choice ==5)
            {
                int promoId;
                string description;
                double discount;
                int productId;
                cout <<"Enter Promotion ID: ";
                cin>>promoId;
                cout << "Enter Description: ";
                cin.ignore();
                getline(cin, description);
                cout << "Enter Discount Percentage: ";
                cin >> discount;
                cout << "Enter Product ID to Apply Promotion: ";
                cin >> productId;
                promotions.emplace_back(promoId, description, discount, vector<int>{productId});
                savePromotionsToFile(promotions, "admin1.txt");
                cout << "Promotion added successfully.\n";
            } else if (choice == 6) {
                    products = loadProductsFromFile("admin.txt");
                    promotions = loadPromotionsFromFile("admin1.txt");
                    for (const auto& promo : promotions) {
                cout << "Promotion ID: " << promo.getId() << " | Description: " << promo.getDescription()
                     << " | Discount: " << promo.getDiscount() << " | Applicable Product: \n";
                for (const auto& productId : promo.getApplicableProducts()) {
                   auto it = find_if(products.begin(), products.end(), [productId](const Product& p) {
                        return p.getId() == productId;
                    });
                    if (it != products.end()) {
                        cout << "  - ID: " << it->getId() << " | Name: " << it->getName()
                             << " | Price: " << it->getPrice() << " | Stock: " << it->getStock() << "\n";
                    }
                }
                cout << "\n";
            }
        } else if( choice ==7 ){
            cout << "\n--- Registered Users ---\n";
                for (const auto& user : users) {
                    cout << "Username: " << user.username << "\n";
                }
        } else if( choice ==8){
            string editUsername;
            cout<<"Enter the username to edit: ";
            cin>>editUsername;
            auto it = find_if(users.begin(),users.end(),[&](const User &u){
                return u.username==editUsername;

            }); 
            if(it!=users.end()){
                cout<<"Enter new password for "<< editUsername<<":";
                cin>>it->password;
                saveUsersToFile(users,userFile);
                cout<<"Password updated successfully!\n";
            } else {
                cout<<"User not found!\n";
            }
        } else if(choice==9){
            string deleteUsername;
                cout << "Enter the username to delete: ";
                cin >> deleteUsername;

                auto it = remove_if(users.begin(), users.end(), [&](const User& u) {
                    return u.username == deleteUsername;
                });

                if (it != users.end()) {
                    users.erase(it, users.end());
                    saveUsersToFile(users, userFile);
                    cout << "User deleted successfully!\n";
                } else {
                    cout << "User not found!\n";
                }
        }
    } while (choice != 10);
    } else {
        cout << "Invalid admin credentials!\n";
    }
};*/
void customerMenu(vector<Product>& products, vector<Promotion>& promotions, vector<Order>& orders) {
    string username;
    cout << "Enter Username: ";
    cin >> username;

    Cart cart;
    int choice;
    do {
        system("cls"); 
        cout << "\n--- Customer Menu ---\n";
        cout << "1. View Products\n2. Add to Cart\n3. Remove from Cart\n4. View Cart\n";
        cout << "5. Checkout\n6. View Order History\n7. Leave a Review\n8. Exit\n";
        cout << "Enter your choice: ";
        cin >> choice;

        system("cls");
        switch (choice) {
            case 1: {
                cout << "--- Available Products ---\n";
                for (const auto& product : products) {
                    cout << "ID: " << product.getId() << " | Name: " << product.getName()
                         << " | Price: " << product.getPrice() << " | Stock: " << product.getStock() << "\n";
                }
                system("pause"); 
                break;
            }
            case 2: { 
                cout << "--- Add to Cart ---\n";
                cout << "\n--- Available Products ---\n";
                for (const auto& product : products) {
                    cout << "ID: " << product.getId() << " | Name: " << product.getName()
                         << " | Price: " << product.getPrice() << " | Stock: " << product.getStock() << "\n";
                }
                int id, quantity;
                cout << "Enter Product ID: ";
                cin >> id;
                cout << "Enter Quantity: ";
                cin >> quantity;
                for (auto& product : products) {
                    if (product.getId() == id) {
                        cart.addProduct(product, quantity);
                        cout << "Product added to cart.\n";
                        break;
                    }
                }
                system("pause");
                break;
            }
            case 3: {
                cout << "--- Remove from Cart ---\n";
                int id;
                cout << "Enter Product ID to remove: ";
                cin >> id;
                cart.removeProduct(id);
                cout << "Product removed from cart.\n";
                system("pause");
                break;
            }
            case 4: { 
                cout << "--- View Cart ---\n";
                cart.viewCart();
                system("pause");
                break;
            }
            case 5: { 
                cout << "--- Checkout ---\n";
                double total = cart.calculateTotal(promotions);
                cout << "\nTotal Amount: " << total << "\nConfirm Checkout? (y/n): ";
                char confirm;
                cin >> confirm;
                if (confirm == 'y' || confirm == 'Y') {
                    static int orderId = 1;
                    orders.emplace_back(orderId++, username, cart.getItems(), total);
                    for (const auto& item : cart.getItems()) {
                        for (auto& product : products) {
                            if (product.getId() == item.first.getId()) {
                                product.setStock(product.getStock() - item.second);
                            }
                        }
                    }
                    saveProductsToFile(products, "admin.txt");
                    saveReviewsToFile(products, "review.txt");

                    cart.clearCart();
                    cout << "Checkout successful!\n";
                }
                system("pause");
                break;
            }
            case 6: { 
                cout << "--- Order History ---\n";
                for (const auto& order : orders) {
                    order.viewOrder();
                }
                system("pause");
                break;
            }
            case 7: { 
                cout << "--- Leave a Review ---\n";
                int id, rating;
                cout << "Enter Product ID to review: ";
                cin >> id;
                cout << "Enter Rating (1-5): ";
                cin >> rating;
                for (auto& product : products) {
                    if (product.getId() == id) {
                        product.addReview(username, rating);
                        saveReviewsToFile(products, "review.txt");
                        cout << "Review added successfully!\n";
                        break;
                    }
                }
                system("pause");
                break;
            }
            case 8: {
                cout << "Exiting Customer Menu...\n";
                break;
            }
            default: {
                cout << "Invalid choice. Please try again.\n";
                system("pause");
                break;
            }
        }
    } while (choice != 8);
}
/*
void customerMenu(vector<Product>& products, vector<Promotion>& promotions, vector<Order>& orders) {
    string username;
    cout << "Enter Username: ";
    cin >> username;

    Cart cart;
    int choice;
    do {
        cout << "\n--- Customer Menu ---\n";
        cout << "1. View Products\n2. Add to Cart\n3. Remove from Cart\n4. View Cart\n5. Checkout\n6. View Order History\n7. Leave a Review\n8. Exit\n";
        cout << "Enter your choice: ";
        cin >> choice;

        if (choice == 1) {
            for (const auto& product : products) {
                cout << "ID: " << product.getId() << " | Name: " << product.getName()
                     << " | Price: " << product.getPrice() << " | Stock: " << product.getStock() << "\n";
            }
        } else if (choice == 2) {
             cout << "\n--- Available Products ---\n";
            for (const auto& product : products) {
                cout << "ID: " << product.getId() << " | Name: " << product.getName()
                     << " | Price: " << product.getPrice() << " | Stock: " << product.getStock() << "\n";
            }
            int id, quantity;
            cout << "Enter Product ID: ";
            cin >> id;
            cout << "Enter Quantity: ";
            cin >> quantity;
            for (auto& product : products) {
                if (product.getId() == id) {
                    cart.addProduct(product, quantity);
                    break;
                }
            }
        } else if (choice == 3) {
            int id;
            cout << "Enter Product ID to remove: ";
            cin >> id;
            cart.removeProduct(id);
        } else if (choice == 4) {
            cart.viewCart();
        } else if (choice == 5) {
            // double total = cart.calculateTotal(promotions);
            double total = cart.calculateTotal(promotions);
            cout << "\nTotal Amount: " << total << "\nConfirm Checkout? (y/n): ";
            char confirm;
            cin >> confirm;
            if (confirm == 'y' || confirm == 'Y') {
                static int orderId = 1;
                orders.emplace_back(orderId++, username, cart.getItems(), total);

                for (const auto& item : cart.getItems()) {
                    for (auto& product : products) {
                        if (product.getId() == item.first.getId()) {
                            product.setStock(product.getStock() - item.second);
                        }
                    }
                }

                // saveProductsToFile(products, "products1.txt");
                saveProductsToFile(products, "admin.txt");
                saveReviewsToFile(products, "review.txt");

                cart.clearCart();
                cout << "Checkout successful!\n";
            }
        } else if (choice == 6) {
            for (const auto& order : orders) {
                order.viewOrder();
            }
        }  else if (choice == 7) {
            int id, rating;
            cout << "Enter Product ID to review: ";
            cin >> id;
            cout << "Enter Rating (1-5): ";
            cin >> rating;
            for (auto& product : products) {
                if (product.getId() == id) {
                    product.addReview(username, rating);
                    saveReviewsToFile(products, "review.txt");
                    break;
                }
            }
        }
    } while (choice != 8);
}
*/
int main() {
    vector<User> users = loadUsersFromFile("login.txt");
    vector<Product> products = loadProductsFromFile("admin.txt");
    vector<Promotion> promotions; 
    vector<Order> orders;    
    string loggedInUser;    
    
    int userType;
    do {
        cout << "\n--- Main Menu ---\n";
        cout << "1. Manager\n2. Customer\n3. Exit\n";
        cout << "Enter your choice: ";
        cin >> userType;

        if (userType == 1) {
if (userType == 1) {
    managerMenu(products, promotions, users, "login.txt");
}
        } else if (userType == 2) {
            if (!login(users, "login.txt", loggedInUser)) {
                cout << "Exiting program.\n";
            return 0;
          }
            customerMenu(products, promotions, orders);
        }
    } while (userType != 3);

    return 0;
}
