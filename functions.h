#ifndef FUNCTIONS_H
#define FUNCTIONS_H

#include "globals.h"

// UTILITY
void logActivity(string message);

// ADMIN
void adminLogin();
void adminDashboard();
void viewAllProducts();
void assignProducts();
void viewProductStatus();
void searchProducts();
void manageEmployees();
void manageUsers();
void viewReports();
void viewActivityLogs();

// USER
void userMenu();
void createAccount();
void userLogin();
void userDashboard(string currentUser);
void listEWaste(string currentUser);
void viewMyProducts(string currentUser);
void trackProductStatus(string currentUser);
void updateAccount(string currentUser);
void deleteProductListing(string currentUser);

// EMPLOYEE
void employeeLogin();
void employeeDashboard(string currentEmpID);
void viewAssignedProducts(string currentEmpID);
void inspectProduct(string currentEmpID);
void updateToRecycled(string currentEmpID);
void searchAssignedProducts(string currentEmpID);
void viewTaskSummary(string currentEmpID);

#endif