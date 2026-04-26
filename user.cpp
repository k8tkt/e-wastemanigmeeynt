#include "globals.h"
#include "functions.h"

void userMenu() {
    int choice;
    while (true) {
        cout << "\n===== USER MENU =====" << endl;
        cout << "1. Create Account" << endl;
        cout << "2. Log In" << endl;
        cout << "3. Back" << endl;
        cout << "Enter choice: ";
        cin >> choice;

        if      (choice == 1) createAccount();
        else if (choice == 2) userLogin();
        else if (choice == 3) return;  // exits back to main menu
        else cout << "Invalid choice. Try again." << endl;
    }
}