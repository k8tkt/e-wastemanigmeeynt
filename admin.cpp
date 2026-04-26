#include "globals.h"
#include "functions.h"
#include <limits>

namespace {
    const string ADMIN_USERNAME = "admin";
    const string ADMIN_PASSWORD = "admin123";

    void clearInputLine() {
        cin.clear();
        cin.ignore(numeric_limits<streamsize>::max(), '\n');
    }

    int findProductIndexByID(int id) {
        for (int i = 0; i < static_cast<int>(productID.size()); i++) {
            if (productID[i] == id) {
                return i;
            }
        }
        return -1;
    }

    int findEmployeeIndexByID(const string& id) {
        for (int i = 0; i < static_cast<int>(employeeID.size()); i++) {
            if (employeeID[i] == id) {
                return i;
            }
        }
        return -1;
    }

    int findUserIndexByName(const string& username) {
        for (int i = 0; i < static_cast<int>(userName.size()); i++) {
            if (userName[i] == username) {
                return i;
            }
        }
        return -1;
    }

    string getLocationText(int i) {
        return productBarangay[i] + ", " + productCity[i] + ", " + productProvince[i];
    }

    string getAssignedDisplay(int i) {
        if (productAssignedTo[i].empty()) {
            return "Unassigned";
        }
        return productAssignedTo[i];
    }

    void printProductHeader() {
        cout << "\n===== PRODUCT LIST =====" << endl;
        cout << "ID\tName\tType\tClassification\tPriority\tStatus\tOwner\tAssigned To\tLocation" << endl;
    }

    void printSingleProduct(int i) {
        cout << productID[i] << '\t'
             << productName[i] << '\t'
             << productItemType[i] << '\t'
             << productClassification[i] << '\t'
             << productPriority[i] << '\t'
             << productStatus[i] << '\t'
             << productOwner[i] << '\t'
             << getAssignedDisplay(i) << '\t'
             << getLocationText(i) << endl;
    }

    void printUserList() {
        cout << "\n===== USER ACCOUNTS =====" << endl;
        if (userName.empty()) {
            cout << "No user accounts found." << endl;
            return;
        }

        for (int i = 0; i < static_cast<int>(userName.size()); i++) {
            cout << i + 1 << ". " << userName[i] << endl;
        }
    }

    void printEmployeeList() {
        cout << "\n===== EMPLOYEE LIST =====" << endl;
        if (employeeID.empty()) {
            cout << "No employees found." << endl;
            return;
        }

        for (int i = 0; i < static_cast<int>(employeeID.size()); i++) {
            cout << i + 1 << ". " << employeeID[i] << " - " << employeeName[i] << endl;
        }
    }
}

void adminLogin() {
    string username, password;

    cout << "\n===== ADMIN LOGIN =====" << endl;
    cout << "Username: ";
    cin >> username;
    cout << "Password: ";
    cin >> password;

    if (username == ADMIN_USERNAME && password == ADMIN_PASSWORD) {
        logActivity("Admin logged in");
        cout << "Login successful." << endl;
        adminDashboard();
        return;
    }

    cout << "Invalid admin credentials." << endl;
}

void adminDashboard() {
    int choice;

    while (true) {
        cout << "\n===== ADMIN DASHBOARD =====" << endl;
        cout << "1. View All Products" << endl;
        cout << "2. Assign Products" << endl;
        cout << "3. View Product Status" << endl;
        cout << "4. Search Products" << endl;
        cout << "5. Manage Employees" << endl;
        cout << "6. Manage Users" << endl;
        cout << "7. View Reports" << endl;
        cout << "8. View Activity Logs" << endl;
        cout << "9. Back" << endl;
        cout << "Enter choice: ";

        if (!(cin >> choice)) {
            clearInputLine();
            cout << "Invalid input. Try again." << endl;
            continue;
        }

        if (choice == 1) viewAllProducts();
        else if (choice == 2) assignProducts();
        else if (choice == 3) viewProductStatus();
        else if (choice == 4) searchProducts();
        else if (choice == 5) manageEmployees();
        else if (choice == 6) manageUsers();
        else if (choice == 7) viewReports();
        else if (choice == 8) viewActivityLogs();
        else if (choice == 9) return;
        else cout << "Invalid choice. Try again." << endl;
    }
}

void viewAllProducts() {
    if (productID.empty()) {
        cout << "\nNo products found." << endl;
        return;
    }

    printProductHeader();
    for (int i = 0; i < static_cast<int>(productID.size()); i++) {
        printSingleProduct(i);
    }
}

void assignProducts() {
    int id;
    string empID;

    if (productID.empty()) {
        cout << "\nNo products available for assignment." << endl;
        return;
    }

    if (employeeID.empty()) {
        cout << "\nNo employees available. Add employees first." << endl;
        return;
    }

    viewAllProducts();
    printEmployeeList();

    cout << "\nEnter product ID to assign: ";
    if (!(cin >> id)) {
        clearInputLine();
        cout << "Invalid product ID." << endl;
        return;
    }

    int productIndex = findProductIndexByID(id);
    if (productIndex == -1) {
        cout << "Product ID not found." << endl;
        return;
    }

    if (productStatus[productIndex] == "Recycled" || productStatus[productIndex] == "Rejected") {
        cout << "This product can no longer be assigned." << endl;
        return;
    }

    cout << "Enter employee ID: ";
    cin >> empID;

    int employeeIndex = findEmployeeIndexByID(empID);
    if (employeeIndex == -1) {
        cout << "Employee ID not found." << endl;
        return;
    }

    productAssignedTo[productIndex] = employeeID[employeeIndex];
    productStatus[productIndex] = "Assigned";

    logActivity("Admin assigned product ID " + to_string(id) + " to employee " + empID);
    cout << "Product assigned successfully." << endl;
}

void viewProductStatus() {
    if (productID.empty()) {
        cout << "\nNo product records found." << endl;
        return;
    }

    cout << "\n===== PRODUCT STATUS =====" << endl;
    for (int i = 0; i < static_cast<int>(productID.size()); i++) {
        cout << "Product ID: " << productID[i]
             << " | Name: " << productName[i]
             << " | Status: " << productStatus[i]
             << " | Assigned To: " << getAssignedDisplay(i)
             << endl;
    }
}

void searchProducts() {
    string keyword;
    bool found = false;

    if (productID.empty()) {
        cout << "\nNo products found." << endl;
        return;
    }

    clearInputLine();
    cout << "\nEnter product name, owner, or status to search: ";
    getline(cin, keyword);

    printProductHeader();
    for (int i = 0; i < static_cast<int>(productID.size()); i++) {
        if (to_string(productID[i]) == keyword ||
            productName[i] == keyword ||
            productOwner[i] == keyword ||
            productStatus[i] == keyword) {
            printSingleProduct(i);
            found = true;
        }
    }

    if (!found) {
        cout << "No matching product found." << endl;
    }
}

void manageEmployees() {
    int choice;

    while (true) {
        cout << "\n===== MANAGE EMPLOYEES =====" << endl;
        cout << "1. View Employees" << endl;
        cout << "2. Add Employee" << endl;
        cout << "3. Remove Employee" << endl;
        cout << "4. Back" << endl;
        cout << "Enter choice: ";

        if (!(cin >> choice)) {
            clearInputLine();
            cout << "Invalid input. Try again." << endl;
            continue;
        }

        if (choice == 1) {
            printEmployeeList();
        } else if (choice == 2) {
            string id, name;

            cout << "Enter employee ID: ";
            cin >> id;
            clearInputLine();
            cout << "Enter employee name: ";
            getline(cin, name);

            if (id.empty() || name.empty()) {
                cout << "Fields cannot be empty." << endl;
                continue;
            }

            if (findEmployeeIndexByID(id) != -1) {
                cout << "Employee ID already exists." << endl;
                continue;
            }

            employeeID.push_back(id);
            employeeName.push_back(name);
            logActivity("Admin added employee: " + id + " - " + name);
            cout << "Employee added successfully." << endl;
        } else if (choice == 3) {
            string id;

            if (employeeID.empty()) {
                cout << "No employees to remove." << endl;
                continue;
            }

            printEmployeeList();
            cout << "Enter employee ID to remove: ";
            cin >> id;

            int index = findEmployeeIndexByID(id);
            if (index == -1) {
                cout << "Employee ID not found." << endl;
                continue;
            }

            for (int i = 0; i < static_cast<int>(productAssignedTo.size()); i++) {
                if (productAssignedTo[i] == employeeID[index]) {
                    productAssignedTo[i] = "Unassigned";
                    productStatus[i] = "Pending";
                }
            }

            string removedName = employeeName[index];
            employeeID.erase(employeeID.begin() + index);
            employeeName.erase(employeeName.begin() + index);

            logActivity("Admin removed employee: " + id + " - " + removedName);
            cout << "Employee removed successfully." << endl;
        } else if (choice == 4) {
            return;
        } else {
            cout << "Invalid choice. Try again." << endl;
        }
    }
}

void manageUsers() {
    int choice;

    while (true) {
        cout << "\n===== MANAGE USERS =====" << endl;
        cout << "1. View Users" << endl;
        cout << "2. Remove User" << endl;
        cout << "3. Back" << endl;
        cout << "Enter choice: ";

        if (!(cin >> choice)) {
            clearInputLine();
            cout << "Invalid input. Try again." << endl;
            continue;
        }

        if (choice == 1) {
            printUserList();
        } else if (choice == 2) {
            string username;

            if (userName.empty()) {
                cout << "No users to remove." << endl;
                continue;
            }

            printUserList();
            cout << "Enter username to remove: ";
            cin >> username;

            int index = findUserIndexByName(username);

            if (index == -1) {
                cout << "Username not found." << endl;
                continue;
            }

            userName.erase(userName.begin() + index);
            userPassword.erase(userPassword.begin() + index);

            logActivity("Admin removed user account: " + username);
            cout << "User removed successfully." << endl;
        } else if (choice == 3) {
            return;
        } else {
            cout << "Invalid choice. Try again." << endl;
        }
    }
}

void viewReports() {
    int pendingCount = 0;
    int assignedCount = 0;
    int inspectedCount = 0;
    int recycledCount = 0;
    int rejectedCount = 0;

    for (int i = 0; i < static_cast<int>(productStatus.size()); i++) {
        if (productStatus[i] == "Pending") pendingCount++;
        else if (productStatus[i] == "Assigned") assignedCount++;
        else if (productStatus[i] == "Inspected") inspectedCount++;
        else if (productStatus[i] == "Recycled") recycledCount++;
        else if (productStatus[i] == "Rejected") rejectedCount++;
    }

    cout << "\n===== REPORTS =====" << endl;
    cout << "Total Products : " << productID.size() << endl;
    cout << "Pending        : " << pendingCount << endl;
    cout << "Assigned       : " << assignedCount << endl;
    cout << "Inspected      : " << inspectedCount << endl;
    cout << "Recycled       : " << recycledCount << endl;
    cout << "Rejected       : " << rejectedCount << endl;
    cout << "Total Users    : " << userName.size() << endl;
    cout << "Total Employees: " << employeeID.size() << endl;
}

void viewActivityLogs() {
    cout << "\n===== ACTIVITY LOGS =====" << endl;

    if (activityLog.empty()) {
        cout << "No activity logs available." << endl;
        return;
    }

    for (int i = 0; i < static_cast<int>(activityLog.size()); i++) {
        cout << i + 1 << ". " << activityLog[i] << endl;
    }
}
