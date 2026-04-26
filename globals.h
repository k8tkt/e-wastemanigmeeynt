#ifndef GLOBALS_H
#define GLOBALS_H

#include <iostream>
#include <vector>
#include <string>
using namespace std;

// PRODUCTS
extern vector<int>    productID;
extern vector<string> productName;
extern vector<string> productDescription;
extern vector<string> productBarangay;
extern vector<string> productCity;
extern vector<string> productProvince;
extern vector<string> productItemType;
extern vector<string> productClassification;
extern vector<string> productPriority;
extern vector<string> productOwner;
extern vector<string> productAssignedTo;
extern vector<string> productStatus;

// USERS
extern vector<string> userName;
extern vector<string> userPassword;

// EMPLOYEES
extern vector<string> employeeID;
extern vector<string> employeeName;

// ACTIVITY LOG
extern vector<string> activityLog;

#endif