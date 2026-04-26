#include "globals.h"
#include "functions.h"

//utility
void logActivity(string message) {
    activityLog.push_back(message);
}

//user menu
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
        else if (choice == 3) return;  // exits back to main menu
        else cout << "Invalid choice. Try again." << endl;
    }
}

//account creation func
void createAccount() {
    string newUsername, newPassword;

    cout << "\nEnter username: ";
    cin >> newUsername;
    cout << "Enter password: ";
    cin >> newPassword;

    //checks if fields are empty
    if (newUsername == "" || newPassword == "") {
        cout << "Fields cannot be empty" << endl;
        return;
    }

    //checks if username is already taken
    for (int i = 0; i < userName.size(); i++) {
        if (userName[i] == newUsername) {
            cout << "Username already exists. Try a different one" << endl;
            return;
        }
    }

    //Saves the new account
    userName.push_back(newUsername);
    userPassword.push_back(newPassword);

    logActivity("New account created: " + newUsername);
    cout << "Account created successfully! You can now log in." << endl;
}



void saveAllData() { 
    //saves users
    ofstream userFile("users.txt");
    for(int i = 0; i < userName.size(); i++) {
        userFile << userName[i] << " " << userPassword[i] << endl;
    }
    userFile.close();
}

void loadAllData() {
    ifstream userFile("users.txt");
    if(userFile.is_open()) {
        string name, pass;
        while(userFile >> name >> pass) {
            userName.push_back(name);
            userPassword.push_back(pass);
        }
        userFile.close();
    }
}





//testing if it works
int main() {
    loadAllData();

    cout << "===== TESTING USER MODULE =====" << endl;
    userMenu();
    cout << "\nTest complete. Goodbye!" << endl;
    
    saveAllData();
    cout << "\nhehe ty" << endl;


    return 0;
}