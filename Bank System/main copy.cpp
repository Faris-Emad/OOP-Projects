#include <iostream>
#include <fstream>
#include <string>
#include <vector>
#include <iomanip>
#include <limits>
#include <cstdlib>
using namespace std;




/**
 * Bank Management System
 * A comprehensive C++ application for managing bank client data
 * Features: Add, Delete, Update, Find clients, and handle transactions
 * Data is stored in text files with custom delimiter separation
 * 
 * Features:
 * - User management system with permissions
 * - Client data management
 * - Financial transactions
 * - File-based data persistence
 */

/* 
    Bank Extension 2 (Requirements):
        1- User management system with different permission levels
        2- User authentication
        3- Financial transaction management (deposits and withdrawals)
        4- Client data management
*/

/**
 * System constants for file management and data separation
 */
namespace Constants {
    const string CLIENTS_FILE = "Clients.txt";  // File name for storing client data
    const string SEPARATOR = "#//#";            // Delimiter used in file for data separation
    const string USERS = "users.txt";           // File name for storing user data
}

/**
 * System utility functions for screen management and navigation
 */
namespace SystemUtils {
    /**
     * Clears the console screen - works on both Windows and Linux/Mac
     * Uses system-specific commands for cross-platform compatibility
     */
    void clearScreen() {
        #ifdef _WIN32
            system("cls");   // Windows command
        #else
            system("clear"); // Linux/Mac command
        #endif
    }

    /**
     * Handles navigation back to main menu or program exit
     * @return true to continue to main menu, false to exit program
     */
    bool goBackOrExit(string messages = "\n\nPress [Enter] to go back to Main Menu: ") {
        cout << messages;
        string input;
        getline(cin, input);
        if (input == "x" || input == "X") {
            return false; // Exit program
        }
        return true; // Return to menu
    }
}

/**
 * Data structure to represent a bank client
 */
struct ClientData {
    string AccountNumber;           // Unique account identifier
    string PinCode;                 // Client's PIN code for security
    string Name;                    // Client's full name
    string Phone;                   // Client's phone number
    double AccountBalance;          // Current account balance
    bool MarkForDelete = false;     // Internal flag for deletion operations
};


/**
 * Enumeration for different user permission levels in the system
 * Binary values are used to allow combining permissions using bitwise operations
 */
enum UserAccess {
    ShowClientList = 1,    // View client list
    AddNewClient = 2,      // Add new client
    DeleteClient = 4,      // Delete client
    UpdateClient = 8,      // Update client information
    FindClient = 16,       // Find client
    Transactions = 32,     // Perform financial transactions
    ManageUsers = 64       // Manage users
};

/**
 * Data structure to represent a system user
 */
struct UserDate {
    string userName;       // Username
    string Password;       // Password
    int userPermission = 0;// User permissions (using UserAccess)
    bool MarkForDelete = false;  // Flag for deletion
};



// String manipulation utilities
namespace StringUtils {
    /**
     * Splits a string into vector of substrings based on delimiter
     * @param text The input string to split
     * @param delimiter The delimiter to split by
     * @return Vector of string tokens
     */
    vector<string> splitString(string text, string delimiter) {
        vector<string> result;
        short pos = 0;
        string word;

        // Find delimiter and split the text
        while ((pos = text.find(delimiter)) != string::npos) {
            word = text.substr(0, pos);
            if (word != "") {
                result.push_back(word);
            }
            text.erase(0, pos + delimiter.length());
        }

        // Add the last part of the text
        if (text != "") {
            result.push_back(text);
        }

        return result;
    }
}

/**
 * File management operations for client and user data persistence
 * Contains functions to convert data between structures and strings for file storage
 */
namespace FileManager {
    /**
     * Converts client data structure to a formatted string line for file storage
     * @param client The client data to convert
     * @return Formatted string with client data separated by delimiters
     */
    string convertClientToLine(ClientData client) {
        string clientRecord = "";
        clientRecord += client.AccountNumber + Constants::SEPARATOR;
        clientRecord += client.PinCode + Constants::SEPARATOR;
        clientRecord += client.Name + Constants::SEPARATOR;
        clientRecord += client.Phone + Constants::SEPARATOR;
        clientRecord += to_string(client.AccountBalance);
        return clientRecord;
    }

    string convertUserToLine(UserDate user) {
        string userRecord = "";
        userRecord += user.userName + Constants::SEPARATOR;
        userRecord += user.Password + Constants::SEPARATOR;
        userRecord += to_string(user.userPermission);
        return userRecord;
    }

    /**
     * Converts a formatted string line back to client data structure
     * @param line The string line from file
     * @return ClientData structure populated with data from the line
     */
    ClientData convertLineToClient(string line) {
        ClientData client;
        vector<string> clientData = StringUtils::splitString(line, Constants::SEPARATOR);

        // Ensure all required data fields are present
        if (clientData.size() >= 5) {
            client.AccountNumber = clientData[0];
            client.PinCode = clientData[1];
            client.Name = clientData[2];
            client.Phone = clientData[3];
            client.AccountBalance = stod(clientData[4]); // Convert string to double
        }
        return client;
    }
    UserDate convertLineToUser(string line) {
        UserDate user;
        vector<string> userData = StringUtils::splitString(line, Constants::SEPARATOR);
        // Ensure all required data fields are present
        if (userData.size() >= 3) {
            user.userName = userData[0];
            user.Password = userData[1];
            user.userPermission = stoi(userData[2]); // Convert string to integer
        }
        return user;
    }

    /**
     * Loads all client data from the file into memory
     * @return Vector containing all client records from file
     */
    vector<ClientData> loadClientsFromFile() {
        vector<ClientData> clients;
        fstream file;
        file.open(Constants::CLIENTS_FILE, ios::in); // Open file for reading

        if (file.is_open()) {
            string line;
            ClientData client;

            // Read each line from the file
            while (getline(file, line)) {
                client = convertLineToClient(line);
                clients.push_back(client);
            }
            file.close();
        }
        return clients;
    }

    vector<UserDate> loadUsersFromFile() {
        vector<UserDate> users;
        fstream file;
        file.open(Constants::USERS, ios::in); // Open file for reading users
        if (file.is_open()) {
            string line;
            UserDate user;
            // Read each line from the file
            while (getline(file, line)) {
                user = convertLineToUser(line);
                users.push_back(user);  // Push the user object, not the vector
            }
            file.close();
        }
        return users;
    }


    /**
     * Saves all client data from memory to file
     * Excludes clients marked for deletion
     * @param clients Vector of client data to save
     * @return Updated vector of clients after save operation
     */
    vector<ClientData> saveClientsToFile(vector<ClientData> clients) {
        fstream file;
        file.open(Constants::CLIENTS_FILE, ios::out); // Open file for writing (overwrites existing)

        string dataLine;
        if (file.is_open()) {
            // Save only clients not marked for deletion
            for (ClientData client : clients) {
                if (client.MarkForDelete == false) {
                    dataLine = convertClientToLine(client);
                    file << dataLine << endl;
                }
            }
            file.close();
        }

        // Reload data from file to ensure consistency
        return loadClientsFromFile();
    }

    vector<UserDate> saveUsersToFile(vector<UserDate> Users) {
        fstream file;
        file.open(Constants::USERS, ios::out); // Open file for writing (overwrites existing)

        string dataLine;
        if (file.is_open()) {
            // Save only clients not marked for deletion
            for (UserDate user : Users) {
                if (user.MarkForDelete == false) {
                    dataLine = convertUserToLine(user);
                    file << dataLine << endl;
                }
            }
            file.close();
        }

        // Reload data from file to ensure consistency
        return loadUsersFromFile();
    }

    /**
     * Appends a new data line to the end of the file
     * @param dataLine Formatted client data string to append
     */
    void addLineToClientsFile(string dataLine) {
        fstream file;
        file.open(Constants::CLIENTS_FILE, ios::out | ios::app); // Open for appending

        if (file.is_open()) {
            file << dataLine << endl;
            file.close();
        }
    }
    void addLineToUsersFile(string dataLine) {
        fstream file;
        file.open(Constants::USERS, ios::out | ios::app); // Open for appending

        if (file.is_open()) {
            file << dataLine << endl;
            file.close();
        }
    }
}

/**
 * Input management for user data entry
 * Contains functions for reading and validating input from the user
 */
namespace InputManager {
    /**
     * Reads a string input from user with a custom message
     * @param message Prompt message to display
     * @return User input string
     */
    string readString(string message) {
        string input;
        cout << message;
        getline(cin, input);
        return input;
    }

    /**
     * Reads account number from user input
     * @return Account number as string
     */
    string readAccountNumber() {
        string accountNumber = "";
        cout << "\nPlease enter Account Number? ";
        cin >> accountNumber;
        cin.ignore(numeric_limits<streamsize>::max(), '\n');
        return accountNumber;
    }
    string readUserName() {
        string userName = "";
        cout << "User Name: ";
        cin >> userName;
        cin.ignore(numeric_limits<streamsize>::max(), '\n');
        return userName;
    }

    string readUserPassword() {
        string userPassword = "";
        cout << "User Password: ";
        cin >> userPassword;
        cin.ignore(numeric_limits<streamsize>::max(), '\n');
        return userPassword;
    }


    /**
     * Reads deposit amount from user input
     * @return Deposit amount as double
     */
    double readDeposit() {
        double deposit;
        cout << "\nPlease enter deposit amount: ";
        cin >> deposit;
        cin.ignore(numeric_limits<streamsize>::max(), '\n');
        return deposit;
    }

    /**
     * Collects all data for a new client from user input
     * @return Complete ClientData structure with user-provided information
     */
    ClientData inputNewClient() {
        ClientData client;
        cout << endl;
        client.AccountNumber = readString("Enter Account Number? ");
        cout << endl;
        client.PinCode = readString("Enter PinCode? ");
        cout << endl;
        client.Name = readString("Enter Name? ");
        cout << endl;
        client.Phone = readString("Enter Phone? ");
        cout << endl;
        cout << "Enter Balance? ";
        cin >> client.AccountBalance;
        cin.ignore();
        return client;
    }

    UserDate inputNewUser() {
        UserDate user;
        UserAccess eUser;
        cout << endl;
        user.userName = readUserName();
        user.Password = readUserPassword();
        
        char answer = 'n';
        cout << "Do you want to give full access? y/n ";
        cin >> answer;
        cin.ignore(numeric_limits<streamsize>::max(), '\n');
        
        if (answer == 'y' || answer == 'Y') {
            user.userPermission= -1;
        }
        else {
            cout << "\nDo you want to give access to the following? (y/n)\n";
            char p = 'n';
            
            cout << "Show Client List? y/n: ";
            cin >> p; 
            if (p == 'y' || p == 'Y') user.userPermission |= UserAccess::ShowClientList;
            cin.ignore(numeric_limits<streamsize>::max(), '\n');
            
            cout << "Add New Client? y/n: ";
            cin >> p; 
            if (p == 'y' || p == 'Y') user.userPermission |= UserAccess::AddNewClient; 
            cin.ignore(numeric_limits<streamsize>::max(), '\n');
            
            cout << "Delete Client? y/n: ";
            cin >> p; 
            if (p == 'y' || p == 'Y') user.userPermission |= UserAccess::DeleteClient;
            cin.ignore(numeric_limits<streamsize>::max(), '\n');
            
            cout << "Update Client? y/n: ";
            cin >> p; 
            if (p == 'y' || p == 'Y') user.userPermission |= UserAccess::UpdateClient;
            cin.ignore(numeric_limits<streamsize>::max(), '\n');
            
            cout << "Find Client? y/n: ";
            cin >> p; 
            if (p == 'y' || p == 'Y') user.userPermission |= UserAccess::FindClient;
            cin.ignore(numeric_limits<streamsize>::max(), '\n');
            
            cout << "Transactions? y/n: ";
            cin >> p; 
            if (p == 'y' || p == 'Y') user.userPermission |= UserAccess::Transactions;
            cin.ignore(numeric_limits<streamsize>::max(), '\n');
            
            cout << "Manage Users? y/n: ";
            cin >> p; 
            if (p == 'y' || p == 'Y') user.userPermission |= UserAccess::ManageUsers;
            cin.ignore(numeric_limits<streamsize>::max(), '\n');
        }
        
        return user;
    }

    /**
     * Updates client data while preserving the account number
     * @param accountNumber The account number to keep unchanged
     * @return Updated ClientData structure
     */
    ClientData inputClientUpdate(string accountNumber) {
        ClientData client;
        client.AccountNumber = accountNumber;
        cout << endl;
        client.PinCode = readString("Enter PinCode? ");
        cout << endl;
        client.Name = readString("Enter Name? ");
        cout << endl;
        client.Phone = readString("Enter Phone? ");
        cout << endl;
        cout << "Enter Balance? ";
        cin >> client.AccountBalance;
        cin.ignore(numeric_limits<streamsize>::max(), '\n');
        return client;
    }
    UserDate inputUserUpdate(string userName) {
        UserDate user;
        char answer = 'n';
        
        // تغيير الاسم
        cout << "Do you want to change the user name? y/n: ";
        cin >> answer;
        cin.ignore(numeric_limits<streamsize>::max(), '\n');
        
        if (answer == 'y' || answer == 'Y') {
            user.userName = readUserName();
        } else {
            user.userName = userName;  // خلي الاسم القديم
        }
        
        // تغيير كلمة المرور
        cout << endl;
        user.Password = readUserPassword();
        
        // الصلاحيات
        cout << "Do you want to give full access? y/n: ";
        cin >> answer;
        cin.ignore(numeric_limits<streamsize>::max(), '\n');
        
        if (answer == 'y' || answer == 'Y') {
            user.userPermission = -1;  // ✅ صححت من userName إلى userPermission
        } else {
            user.userPermission = 0;
            
            cout << "\nDo you want to give access to the following? (y/n)\n";
            char p = 'n';
            
            cout << "Show Client List? y/n: ";
            cin >> p; 
            if (p == 'y' || p == 'Y') user.userPermission |= UserAccess::ShowClientList;
            cin.ignore(numeric_limits<streamsize>::max(), '\n');
            
            cout << "Add New Client? y/n: ";
            cin >> p; 
            if (p == 'y' || p == 'Y') user.userPermission |= UserAccess::AddNewClient;
            cin.ignore(numeric_limits<streamsize>::max(), '\n');
            
            cout << "Delete Client? y/n: ";
            cin >> p; 
            if (p == 'y' || p == 'Y') user.userPermission |= UserAccess::DeleteClient;
            cin.ignore(numeric_limits<streamsize>::max(), '\n');
            
            cout << "Update Client? y/n: ";
            cin >> p; 
            if (p == 'y' || p == 'Y') user.userPermission |= UserAccess::UpdateClient;
            cin.ignore(numeric_limits<streamsize>::max(), '\n');
            
            cout << "Find Client? y/n: ";
            cin >> p; 
            if (p == 'y' || p == 'Y') user.userPermission |= UserAccess::FindClient;
            cin.ignore(numeric_limits<streamsize>::max(), '\n');
            
            cout << "Transactions? y/n: ";
            cin >> p; 
            if (p == 'y' || p == 'Y') user.userPermission |= UserAccess::Transactions;
            cin.ignore(numeric_limits<streamsize>::max(), '\n');
            
            cout << "Manage Users? y/n: ";
            cin >> p; 
            if (p == 'y' || p == 'Y') user.userPermission |= UserAccess::ManageUsers;
            cin.ignore(numeric_limits<streamsize>::max(), '\n');
        }
        
        return user;
    }
}

// Display and printing utilities for client information
/**
 * Display and printing utilities for client and user information
 * Includes functions to display data in different formats (cards, tables, lists)
 */
namespace DisplayManager {
    /**
     * Prints client data in a formatted card layout
     * @param client ClientData structure to display
     */

    void showUserPermissions(int permissions) {
        cout << "\nUser Permissions:\n";
        if (permissions == -1) {
            cout << "Full Access (All Permissions Granted)\n";
            return;
        }

        if (permissions & UserAccess::ShowClientList) cout << "- Show Client List\n";
        if (permissions & UserAccess::AddNewClient)   cout << "- Add New Client\n";
        if (permissions & UserAccess::DeleteClient)   cout << "- Delete Client\n";
        if (permissions & UserAccess::UpdateClient)   cout << "- Update Client\n";
        if (permissions & UserAccess::FindClient)     cout << "- Find Client\n";
        if (permissions & UserAccess::Transactions)   cout << "- Transactions\n";
        if (permissions & UserAccess::ManageUsers)    cout << "- Manage Users\n";
    }

    void printClientCard(ClientData client) {
        cout << "\nThe following are the client details:\n";
        cout << "___________________\n";
        cout << "Account Number  : " << client.AccountNumber << endl;
        cout << "Pin Code        : " << client.PinCode << endl;
        cout << "Name            : " << client.Name << endl;
        cout << "Phone           : " << client.Phone << endl;
        cout << fixed << setprecision(2);
        cout << "Account Balance : " << client.AccountBalance << endl;
        cout << "___________________\n";
    }
    void printUserCard(UserDate user) {
        cout << "\nThe following are the user details:\n";
        cout << "___________________\n";
        cout << "User Name      : " << user.userName << endl;
        cout << "Password       : " << user.Password << endl;
        cout << "Permission     : " << user.userPermission << endl;
        showUserPermissions(user.userPermission);
        cout << "___________________\n";
    }


    /**
     * Prints client data in a single table row format
     * @param client ClientData structure to display
     */
    void printClientRecord(ClientData client) {
        cout << "| " << setw(15) << left << client.AccountNumber;
        cout << "| " << setw(10) << left << client.PinCode;
        cout << "| " << setw(40) << left << client.Name;
        cout << "| " << setw(12) << left << client.Phone;
        cout << "| " << setw(12) << left << client.AccountBalance;
    }

    void printUserRecord(UserDate User) {
        cout << "| " << setw(15) << left << User.userName;
        cout << "| " << setw(10) << left << User.Password;
        cout << "| " << setw(40) << left << User.userPermission;
        cout << endl;
    }

    /**
     * Displays all clients in a formatted table
     * @param clients Vector of all client data to display
     */
    void printAllClients(vector<ClientData> clients) {
        cout << "\n\t\t\t\t\tClient List (" << clients.size() << ") Client(s).\n";
        cout << "______________________________________________________";
        cout << "___________________________________________\n" << endl;

        // Print table header
        cout << "| " << left << setw(15) << "Account Number";
        cout << "| " << left << setw(10) << "Pin Code";
        cout << "| " << left << setw(40) << "Client Name";
        cout << "| " << left << setw(12) << "Phone";
        cout << "| " << left << setw(12) << "Account Balance";
        cout << "\n______________________________________________________";
        cout << "___________________________________________\n" << endl;
        cout << fixed << setprecision(2);
        // Print client data rows
        for(ClientData client : clients) {
            printClientRecord(client);
            cout << endl;
        }

        cout << "______________________________________________________";
        cout << "___________________________________________\n" << endl;
    }

    void printAllUsers(vector<UserDate> users) {
        cout << "\n\t\t\t\t\tUser List (" << users.size() << ") User(s).\n";
        cout << "______________________________________________________";
        cout << "___________________________________________\n" << endl;

        // Print table header
        cout << "| " << left << setw(15) << "User Name";
        cout << "| " << left << setw(10) << "Password";
        cout << "| " << left << setw(40) << "Permission";
        cout << "\n______________________________________________________";
        cout << "___________________________________________\n" << endl;

        // Print user data rows
        for (UserDate user : users) {
            printUserRecord(user);
        }

        cout << "______________________________________________________";
        cout << "___________________________________________\n" << endl;
    }

    /**
     * Displays client balances table with total calculation
     * @param clients Vector of client data for balance display
     */
    void printTotalBalances(vector<ClientData> clients) {
        cout << "\n\t\t\t\t\tBalances List (" << clients.size() << ") Client(s).\n";
        cout << "______________________________________________________";
        cout << "___________________________________________\n" << endl;

        // Print table header
        cout << "| " << left << setw(15) << "Account Number";
        cout << "| " << left << setw(10) << "Pin Code";
        cout << "| " << left << setw(40) << "Client Name";
        cout << "| " << left << setw(12) << "Phone";
        cout << "| " << left << setw(12) << "Account Balance";
        cout << "\n______________________________________________________";
        cout << "___________________________________________\n" << endl;

        // Print client data rows
        for(ClientData client : clients) {
            printClientRecord(client);
            cout << endl;
        }

        cout << "______________________________________________________";
        cout << "___________________________________________\n" << endl;

        // Calculate and display total balances
        double totalBalances = 0;
        for (ClientData client : clients) {
            totalBalances += client.AccountBalance;
        }
        cout << fixed << setprecision(2);
        cout << "\n\t\t\t\t\tTotal Balances: " << totalBalances;
    }

    /**
     * Displays success message after adding a new client
     */
    void showAddClientSuccess() {
        cout << endl;
        cout << "====================================================\n";
        cout << "Client Added Successfully!\n";
        cout << "====================================================\n";
    }

    void showAddUserSuccess() {
        cout << endl;
        cout << "====================================================\n";
        cout << "User Added Successfully!\n";
        cout << "====================================================\n";
    }

    void printAccessDenied() {
        cout << endl;
        cout << "\n====================================================\n";
        cout << "Access Denied,\n";
        cout <<  "You dont Have Permission To Do this,\n" ;
        cout << "Please Conact Your Admin.";
        cout << "\n====================================================\n";
    }
}

// Search and retrieval operations for client data
/**
 * Helper functions for checking user permissions
 */
namespace PermissionManager {
    /**
     * Check if a user has a specific permission
     * @param user The user to check permissions for
     * @param permission The permission to check
     * @return true if user has permission, false otherwise
     */
    bool hasPermission(const UserDate& user, UserAccess permission) {
        // Using bitwise AND to check if permission bit is set
        return (user.userPermission & static_cast<int>(permission)) != 0;
    }
    
    /**
     * Check if a user has full access permissions
     * @param user The user to check
     * @return true if user has all permissions, false otherwise
     */
    bool hasFullAccess(const UserDate& user) {
        // Value -1 represents all permissions (all bits set to 1)
        return user.userPermission == -1;
    }
}

/**
 * Search and retrieval operations for client and user data
 */
namespace SearchManager {
    /**
     * Searches for a client in the provided vector by account number
     * @param accountNumber Account number to search for
     * @param clients Vector of clients to search in
     * @param foundClient Reference to store found client data
     * @return true if client found, false otherwise
     */
    bool findClientInVector(string accountNumber, vector<ClientData> clients, ClientData& foundClient) {
        for (ClientData client : clients) {
            if (client.AccountNumber == accountNumber) {
                foundClient = client; // Copy found client data
                return true;
            }
        }
        return false; // Client not found
    }

    bool findUserInVector(string userName, vector<UserDate> users, UserDate& foundUser) {
        for (UserDate user : users) {
            if (user.userName == userName) {
                foundUser = user;
                return true;
            }
        }
        return false; // Client not found
    }

    /**
     * Searches for a client directly in the file by account number
     * @param accountNumber Account number to search for
     * @param foundClient Reference to store found client data
     * @return true if client found, false otherwise
     */
    bool findClientInFile(string accountNumber, ClientData& foundClient) {
        vector<ClientData> clients = FileManager::loadClientsFromFile();
        for (ClientData client : clients) {
            if (client.AccountNumber == accountNumber) {
                foundClient = client;
                return true;
            }
        }
        return false;
    }

    bool findUserInFile(string userName, UserDate& foundUser) {
        vector<UserDate> users = FileManager::loadUsersFromFile();
        for (UserDate user : users) {
            if (user.userName == userName) {
                foundUser = user;
                return true;
            }
        }
        return false;
    }

    


    /**
     * Checks if a client exists with the given account number
     * @param accountNumber Account number to check
     * @return true if client exists, false otherwise
     */
    bool doesClientExist(string accountNumber) {
        ClientData dummy;
        return findClientInFile(accountNumber, dummy);
    }
    bool doesUserExist(string userName) {
        UserDate dummy;
        return findUserInFile(userName, dummy);
    }

    bool IsPasswordRight(string password, UserDate& foundUserPassword) {
        vector<UserDate> users = FileManager::loadUsersFromFile();
        for (UserDate user : users) {
            if (user.Password == password) {
                foundUserPassword = user;
                return true;
            }
        }
        return false;
    }
    bool doesUserPasswordExist(string password) {
        UserDate dummy;
        return IsPasswordRight(password, dummy);
    }

    UserDate ReturnUserFormFile(string userName, string password, UserDate& foundUser) {
        vector<UserDate> users = FileManager::loadUsersFromFile();
        for (UserDate user : users) {
            if (user.userName == userName && user.Password == password) {
                foundUser = user;
            }
        }
        return foundUser;
    }

}

// Client management operations (add, delete, update, transactions)
/**
 * Client management operations (add, delete, update, transactions)
 * Handles all operations related to client data manipulation
 */
namespace ClientManager {
    /**
     * Marks a client for deletion by setting the delete flag
     * @param accountNumber Account number of client to mark
     * @param clients Reference to vector of clients
     * @return true if client found and marked, false otherwise
     */
    bool markClientForDelete(string accountNumber, vector<ClientData>& clients) {
        for (ClientData& client : clients) {
            if (client.AccountNumber == accountNumber) {
                client.MarkForDelete = true;
                return true;
            }
        }
        return false;
    }

    /**
     * Deletes a client after user confirmation
     * @param accountNumber Account number of client to delete
     * @param clients Reference to vector of clients
     * @return true if client was deleted, false otherwise
     */
    bool deleteClient(string accountNumber, vector<ClientData>& clients) {
        ClientData client;
        char answer = 'n';

        // Search for the client
        if (SearchManager::findClientInVector(accountNumber, clients, client)) {
            // Display client data
            DisplayManager::printClientCard(client);

            // Request confirmation
            cout << "\n\nAre you sure you want to delete this user? y/n ? ";
            cin >> answer;

            if (answer == 'y' || answer == 'Y') {
                // Mark client for deletion and save changes
                markClientForDelete(accountNumber, clients);
                clients = FileManager::saveClientsToFile(clients);
                cout << "\n\nClient Deleted Successfully.";
                return true;
            }
        } else {
            cout << "\nClient with Account Number (" << accountNumber << ") is Not Found!";
        }
        return false;
    }

    /**
     * Updates client information after user confirmation
     * @param accountNumber Account number of client to update
     * @param clients Reference to vector of clients
     * @return true if client was updated, false otherwise
     */
    bool updateClient(string accountNumber, vector<ClientData>& clients) {
        ClientData client;
        char answer = 'n';

        // Search for the client
        if (SearchManager::findClientInVector(accountNumber, clients, client)) {
            // Display current client data
            DisplayManager::printClientCard(client);

            // Request confirmation
            cout << "\n\nAre you sure you want to update this client? y/n ? ";
            cin >> answer;
            cin.ignore(numeric_limits<streamsize>::max(), '\n');

            if (answer == 'y' || answer == 'Y') {
                // Update client data
                for (ClientData& c : clients) {
                    if (c.AccountNumber == accountNumber) {
                        c = InputManager::inputClientUpdate(accountNumber);
                        break;
                    }
                }

                // Save changes
                FileManager::saveClientsToFile(clients);
                cout << "\n\nClient Updated Successfully.";
                return true;
            }
        } else {
            cout << "\nClient with Account Number (" << accountNumber << ") is Not Found!";
        }
        return false;
    }

    /**
     * Handles deposit operation for a client account
     * @param accountNumber Account number for deposit
     * @param clients Reference to vector of clients
     * @return true if deposit was successful, false otherwise
     */
    bool depositClient(string accountNumber, vector<ClientData>& clients) {
        ClientData client;
        char answer = 'n';

        // Search for the client
        if (SearchManager::findClientInVector(accountNumber, clients, client)) {
            // Display current client data
            DisplayManager::printClientCard(client);

            // Request confirmation
            cout << "\n\nAre you sure you want to deposit? y/n ? ";
            cin >> answer;
            cin.ignore(numeric_limits<streamsize>::max(), '\n');

            if (answer == 'y' || answer == 'Y') {
                // Process deposit
                for (ClientData& c : clients) {
                    if (c.AccountNumber == accountNumber) {
                        c.AccountBalance += InputManager::readDeposit();
                        break;
                    }
                }
                // Save changes
                FileManager::saveClientsToFile(clients);
                cout << "\n\nDeposit Successful.";
                return true;
            }
        } else {
            cout << "\nClient with Account Number (" << accountNumber << ") is Not Found!";
        }
        return false;
    }

    /**
     * Handles withdrawal operation for a client account with balance validation
     * @param accountNumber Account number for withdrawal
     * @param clients Reference to vector of clients
     * @return true if withdrawal was successful, false otherwise
     */
    bool withdrawClient(string accountNumber, vector<ClientData>& clients) {
        ClientData client;
        char answer = 'n';

        // Search for the client
        if (SearchManager::findClientInVector(accountNumber, clients, client)) {
            // Display current client data
            DisplayManager::printClientCard(client);

            // Request confirmation
            cout << "\n\nAre you sure you want to withdraw? y/n ? ";
            cin >> answer;
            cin.ignore(numeric_limits<streamsize>::max(), '\n');

            if (answer == 'y' || answer == 'Y') {
                double withdrawAmount;
                cout << "\nPlease enter withdraw amount: ";
                cin >> withdrawAmount;
                cin.ignore(numeric_limits<streamsize>::max(), '\n');

                // Validate sufficient balance
                while (withdrawAmount > client.AccountBalance) {
                    cout << "\nAmount exceeds the balance! Available: " << client.AccountBalance;
                    cout << "\nPlease enter another amount: ";
                    cin >> withdrawAmount;
                    cin.ignore(numeric_limits<streamsize>::max(), '\n');
                }

                // Process withdrawal
                for (ClientData& c : clients) {
                    if (c.AccountNumber == accountNumber) {
                        c.AccountBalance -= withdrawAmount;
                        cout << "\n\nWithdraw Successful. New balance: " << c.AccountBalance;
                        break;
                    }
                }

                FileManager::saveClientsToFile(clients);
                return true;
            }
        } else {
            cout << "\nClient with Account Number (" << accountNumber << ") is Not Found!";
        }
        return false;
    }

    /**
     * Adds a new client to the system after validation
     */
    void addNewClient() {
        vector<ClientData> clients = FileManager::loadClientsFromFile();
        cout << "Adding New Client:\n";

        ClientData newClient = InputManager::inputNewClient();

        // Check if client with same account number already exists
        ClientData existingClient;
        if (SearchManager::findClientInVector(newClient.AccountNumber, clients, existingClient)) {
            cout << "\nClient with Account Number (" << newClient.AccountNumber << ") already exists.\n";
        } else {
            // Add the new client
            FileManager::addLineToClientsFile(FileManager::convertClientToLine(newClient));
            DisplayManager::showAddClientSuccess();
        }
        cout << endl;
    }

    /**
     * Handles adding multiple clients in sequence
     */
    void addMultipleClients() {
        char choice;
        do {
            cout << "Do you want to add more clients? (y/n): ";
            cin >> choice;
            cin.ignore(numeric_limits<streamsize>::max(), '\n');

            // Validate input
            while (tolower(choice) != 'y' && tolower(choice) != 'n') {
                cout << "Invalid input! Please enter (y/n): ";
                cin >> choice;
                cin.ignore(numeric_limits<streamsize>::max(), '\n');
            }

            if (tolower(choice) == 'y') {
                addNewClient();
            }
        } while (tolower(choice) == 'y');
    }
}

/**
 * User management operations
 * Handles user creation, deletion, updates and permission management
 */
namespace UserManager {
    /**
     * Marks a user for deletion by setting the delete flag
     * @param UserName Username of the user to mark for deletion
     * @param Users Reference to vector of users
     * @return true if user found and marked, false otherwise
     */
    bool markUserForDelete(string UserName, vector<UserDate> &Users) {
        for (UserDate& user : Users) {
            if (user.userName == UserName) {
                user.MarkForDelete = true;
                return true;
            }
        }
        return false;
    }

    /**
     * Adds a new user to the system
     * Validates that the username doesn't already exist
     */
    void addNewUser() {
        vector<UserDate> users = FileManager::loadUsersFromFile();
        cout << "Adding New User:\n";

        UserDate newUser = InputManager::inputNewUser();

        // Check if client with same account number already exists
        UserDate existingUser;
        if (SearchManager::findUserInVector(newUser.userName, users, existingUser)) {
            cout << "\nUser with user name (" << newUser.userName<< ") already exists.\n";
        } else {
            // Add the new client
            FileManager::addLineToUsersFile(FileManager::convertUserToLine(newUser));
            DisplayManager::showAddUserSuccess();
        }
        cout << endl;
    }

    /**
     * Handles adding multiple users in sequence
     * Continues asking the user if they want to add more users
     */
    void addMultipleUsers() {
        char choice;
        do {
            cout << "Do you want to add more users? (y/n): ";
            cin >> choice;
            cin.ignore(numeric_limits<streamsize>::max(), '\n');

            // Validate input
            while (tolower(choice) != 'y' && tolower(choice) != 'n') {
                cout << "Invalid input! Please enter (y/n): ";
                cin >> choice;
                cin.ignore(numeric_limits<streamsize>::max(), '\n');
            }

            if (tolower(choice) == 'y') {
                addNewUser();
            }
        } while (tolower(choice) == 'y');
    }

    /**
     * Deletes a user after confirmation
     * @param UserName Username of the user to delete
     * @param Users Reference to vector of users
     * @return true if user was deleted, false otherwise
     */
    bool deleteUser(string UserName, vector<UserDate> &Users) {
        UserDate User;
        char answer = 'n';

        // Search for the user
        if (SearchManager::findUserInVector(UserName, Users, User)) {
            
            if(UserName == "Admin")
                cout << "you can't delete this user !!!" << endl;
            else {
                // Display client data
                DisplayManager::printUserCard(User);
                // Request confirmation
                cout << "\n\nAre you sure you want to delete this user? y/n ? ";
                cin >> answer;

                if (answer == 'y' || answer == 'Y') {
                    // Mark client for deletion and save changes
                    markUserForDelete(UserName, Users);
                    Users = FileManager::saveUsersToFile(Users);
                    cout << "\n\nClient Deleted Successfully.";
                    return true;
                }
            }


        } else {
            cout << "\nuser with Account Number (" << UserName << ") is Not Found!";
        }
        return false;
    }

    /**
     * Updates user information after confirmation
     * @param UserName Username of the user to update
     * @param Users Reference to vector of users
     * @return true if user was updated, false otherwise
     */
    bool updateUser(string UserName, vector<UserDate> &Users) {
        UserDate User;
        char answer = 'n';
        if(UserName == "Admin") {
            cout << "Cannot modify Admin account!\n";
            return false;
        }
        // Search for the client
        if (SearchManager::findUserInVector(UserName, Users, User)) {
            // Display current client data
            DisplayManager::printUserCard(User);
   

            // Request confirmation
            cout << "\n\nAre you sure you want to update this user? y/n ? ";
            cin >> answer;
            cin.ignore(numeric_limits<streamsize>::max(), '\n');

            if (answer == 'y' || answer == 'Y') {
                // Update client data
                for (UserDate& u : Users) {
                    if (u.userName == UserName) {
                        u = InputManager::inputUserUpdate(UserName);
                        break;
                    }
                }

                // Save changes
                FileManager::saveUsersToFile(Users);
                cout << "\n\nuser Updated Successfully.";
                return true;
            }
        } else {
            cout << "\nuser with Account Number (" << UserName << ") is Not Found!";
        }
        return false;
    }

}

// Transaction-specific application screens and operations
/**
 * Transaction-specific application screens and operations
 * Handles deposit, withdrawal and balance checking functionality
 */
namespace TransactionsApps {
    /**
     * Handles the deposit transaction screen
     * Allows adding funds to a client account
     */
    void Deposit() {
        ClientData Client;
        cout << "\n\n====================================================\n";
        cout << "\t\t\t Deposit Screen\n";
        cout << "====================================================\n";
        string AccountNumber = InputManager::readAccountNumber();
        vector<ClientData> clients = FileManager::loadClientsFromFile();
        ClientManager::depositClient(AccountNumber, clients);
    }

    /**
     * Handles the withdrawal transaction screen
     * Allows removing funds from a client account with balance validation
     */
    void Withdraw() {
        ClientData Client;
        cout << "\n\n====================================================\n";
        cout << "\t\t\t Withdraw Screen\n";
        cout << "====================================================\n";
        string AccountNumber = InputManager::readAccountNumber();
        vector<ClientData> clients = FileManager::loadClientsFromFile();
        ClientManager::withdrawClient(AccountNumber, clients);
    }

    /**
     * Displays total balances of all clients
     * Shows a summary table and calculates the sum of all account balances
     */
    void TotalBalances() {
        SystemUtils::clearScreen();
        vector<ClientData> clients = FileManager::loadClientsFromFile();
        DisplayManager::printTotalBalances(clients);
    }
}


/**
 * User management application screens and operations
 * Provides functionality for user listing, creation, deletion, and updates
 */
namespace ManageUsersMenuApps {
    /**
     * Displays a list of all users in the system
     */
    void ListUsers() {
        SystemUtils::clearScreen();
        vector<UserDate> Users = FileManager::loadUsersFromFile();
        DisplayManager::printAllUsers(Users);
    }
    /**
     * Handles the process of adding a new user to the system
     */
    void AddNewUser() {
        SystemUtils::clearScreen();
        cout << "====================================================\n";
        cout << "\t\t Add New User Screen\n";
        cout << "====================================================\n";
        UserManager::addNewUser();
        UserManager::addMultipleUsers();
    }
    /**
     * Handles the process of deleting a user from the system
     */
    void DeleteUser() {
        SystemUtils::clearScreen();
        vector<UserDate> Users = FileManager::loadUsersFromFile();
        string UserName = InputManager::readUserName();
        UserManager::deleteUser(UserName, Users);
    }

    /**
     * Handles the process of updating user information
     */
    void UpdateUser() {
        SystemUtils::clearScreen();
        vector<UserDate> Users = FileManager::loadUsersFromFile();
        string UserName = InputManager::readUserName();
        UserManager::updateUser(UserName, Users);
    }

    /**
     * Searches for a specific user by username
     */
    void FindUser() {
        SystemUtils::clearScreen();
        UserDate user;
        string UserName = InputManager::readUserName();

        if (SearchManager::findUserInFile(UserName, user)) {
            DisplayManager::printUserCard(user);
        } else {
            cout << "\nClient with Account Number (" << UserName << ") Not Found!\n";
        }
    }

}

/**
 * Extensions for additional functionality
 * Provides extended menus and specialized screens
 */
namespace Extensions {
    /**
     * Displays and manages the transactions menu
     * Allows access to deposit, withdrawal and balance operations
     */
    void showTransactionsMenu() {
        int choice = 0;
        bool running = true;
        while (running) {
            // Display menu options
            cout << "====================================================\n";
            cout << "\t\t\t Transactions Menu\n";
            cout << "====================================================\n";
            cout << "\t\t[1] Deposit.\n";
            cout << "\t\t[2] Withdraw.\n";
            cout << "\t\t[3] Total Balances.\n";
            cout << "\t\t[4] Main Menu.\n";
            cout << "====================================================\n";
            cout << "Choose what you want to do? [1 to 4]: ";
            cin >> choice;
            cin.ignore(numeric_limits<streamsize>::max(), '\n');

            // Execute selected option
            switch (choice) {
                case 1:
                    TransactionsApps::Deposit();
                    running = SystemUtils::goBackOrExit("\n\nPress [Enter] to go back to Transactions Main: ");
                    break;
                case 2:
                    TransactionsApps::Withdraw();
                    running = SystemUtils::goBackOrExit("\n\nPress [Enter] to go back to Transactions Main: ");
                    break;
                case 3:
                    TransactionsApps::TotalBalances();
                    running = SystemUtils::goBackOrExit("\n\nPress [Enter] to go back to Transactions Main: ");
                    break;
                case 4:
                    running = false;
                    break;
                default:
                    cout << "Invalid choice, try again.\n";
                    break;
            }
        }
    }

    /**
     * Displays and manages the user management menu
     * Provides access to user listing, creation, deletion, and update operations
     */
    void showManageUsersMenu() {
        int choice = 0;
        bool run = true;
        while (run) {
            // Display menu options
            cout << "====================================================\n";
            cout << "\t\t\t Manage Users Menu Screen\n";
            cout << "====================================================\n";
            cout << "\t\t[1] List Users.\n";
            cout << "\t\t[2] Add New User.\n";
            cout << "\t\t[3] Delete User.\n";
            cout << "\t\t[4] Update User.\n";
            cout << "\t\t[5] Find User.\n";
            cout << "\t\t[6] Main Menu.\n";
            cout << "====================================================\n";
            cout << "Choose what you want to do? [1 to 6]: ";
            cin >> choice;
            cin.ignore(numeric_limits<streamsize>::max(), '\n');
            switch (choice) {
                case 1:
                    // List Users functionality should go here
                    ManageUsersMenuApps::ListUsers();
                    run = SystemUtils::goBackOrExit("\n\nPress [Enter] to go back to Manage Users Main: ");
                    break;
                case 2:
                    // Add New User functionality should go here
                    ManageUsersMenuApps::AddNewUser();
                    run = SystemUtils::goBackOrExit("\n\nPress [Enter] to go back to Manage Users Main: ");
                    break;
                case 3:
                    // Delete User functionality should go here
                    ManageUsersMenuApps::DeleteUser();
                    run = SystemUtils::goBackOrExit("\n\nPress [Enter] to go back to Manage Users Main: ");
                    break;
                case 4:
                    // Update User functionality should go here
                    ManageUsersMenuApps::UpdateUser();
                    run = SystemUtils::goBackOrExit("\n\nPress [Enter] to go back to Manage Users Main: ");
                    break;
                case 5:
                    // Find User functionality should go here
                    ManageUsersMenuApps::FindUser();
                    run = SystemUtils::goBackOrExit("\n\nPress [Enter] to go back to Manage Users Main: ");
                    break;
                case 6:
                    run = false;
                    break;
                default:
                    cout << "Invalid choice, try again.\n";
                    break;
            }
        }
    }
}
// Main application screens for different functionalities
/**
 * Main application screens for different functionalities
 * Provides the primary user interface screens for the application
 */
namespace AppScreens {
    /**
     * Screen to display all clients in the system
     * Shows a formatted table with all client information
     */
    void showAllClients() {
        SystemUtils::clearScreen();
        vector<ClientData> clients = FileManager::loadClientsFromFile();
        DisplayManager::printAllClients(clients);
    }

    /**
     * Screen to add new clients to the system
     */
    void showAddClientScreen() {
        SystemUtils::clearScreen();
        cout << "====================================================\n";
        cout << "\t\t Add New Client Screen\n";
        cout << "====================================================\n";
        ClientManager::addNewClient();
        ClientManager::addMultipleClients();
    }

    /**
     * Screen to delete existing clients from the system
     */
    void showDeleteClientScreen() {
        SystemUtils::clearScreen();
        vector<ClientData> clients = FileManager::loadClientsFromFile();
        string accountNumber = InputManager::readAccountNumber();
        ClientManager::deleteClient(accountNumber, clients);
    }

    /**
     * Screen to update existing client information
     */
    void showUpdateClientScreen() {
        SystemUtils::clearScreen();
        vector<ClientData> clients = FileManager::loadClientsFromFile();
        string accountNumber = InputManager::readAccountNumber();
        ClientManager::updateClient(accountNumber, clients);
    }

    /**
     * Screen to search and find specific clients
     */
    void showFindClientScreen() {
        SystemUtils::clearScreen();
        ClientData client;
        string accountNumber = InputManager::readAccountNumber();

        if (SearchManager::findClientInFile(accountNumber, client)) {
            DisplayManager::printClientCard(client);
        } else {
            cout << "\nClient with Account Number (" << accountNumber << ") Not Found!\n";
        }
    }

    /**
     * Screen to access transactions menu
     */
    void showTransactionsScreen() {
        SystemUtils::clearScreen();
        Extensions::showTransactionsMenu();
    }

    void showManageUsers() {
        SystemUtils::clearScreen();
        Extensions::showManageUsersMenu();
    }
}

/**
 * Main menu system - central hub for all application features
 * Handles user navigation between different system functionalities
 */
/**
 * Displays the main menu based on user permissions
 * Shows only the menu options that the user has access to
 * @param user The authenticated user with permission settings
 */
void showMainMenu(UserDate user) {
    int choice = 0;
    bool running = true;

    while (running) {
        // Display main menu options
        cout << "====================================================\n";
        cout << "\t\t\t Main Menu Screen\n";
        cout << "====================================================\n";
        cout << "\t\t[1] Show Client List.\n";
        cout << "\t\t[2] Add New Client.\n";
        cout << "\t\t[3] Delete Client.\n";
        cout << "\t\t[4] Update Client.\n";
        cout << "\t\t[5] Find Client.\n";
        cout << "\t\t[6] Transactions.\n";
        cout << "\t\t[7] Manage Users.\n";
        cout << "\t\t[8] Logout.\n";
        cout << "====================================================\n";
        cout << "Choose what you want to do? [1 to 7]: ";
        cin >> choice;
        cin.ignore(numeric_limits<streamsize>::max(), '\n');

        // Execute selected menu option
        switch (choice) {
            case 1:
                if(user.userPermission == -1 || (user.userPermission & UserAccess::ShowClientList)) {
                    
                    AppScreens::showAllClients();
                    running = SystemUtils::goBackOrExit();
                }
                else{
                    DisplayManager::printAccessDenied();
                    running = SystemUtils::goBackOrExit();
                }
                break;
            case 2:
                if(user.userPermission == -1 || (user.userPermission & UserAccess::AddNewClient)) {
                    AppScreens::showAddClientScreen();
                    running = SystemUtils::goBackOrExit();
                }
                else{
                    DisplayManager::printAccessDenied();
                    running = SystemUtils::goBackOrExit();
                }
                
                break;
            case 3:
                if(user.userPermission == -1 || (user.userPermission & UserAccess::DeleteClient)) {
                    AppScreens::showDeleteClientScreen();
                    running = SystemUtils::goBackOrExit();
                }
                else{
                    DisplayManager::printAccessDenied();
                    running = SystemUtils::goBackOrExit();
                }
                break;
            case 4:
                if(user.userPermission == -1 || (user.userPermission & UserAccess::UpdateClient)) {
                    AppScreens::showUpdateClientScreen();
                    running = SystemUtils::goBackOrExit();
                }
                else{
                    DisplayManager::printAccessDenied();
                    running = SystemUtils::goBackOrExit();
                }
                break;
            case 5:
                if(user.userPermission == -1 || (user.userPermission & UserAccess::FindClient)) {
                    AppScreens::showFindClientScreen();
                    running = SystemUtils::goBackOrExit();
                }
                else{
                    DisplayManager::printAccessDenied();
                    running = SystemUtils::goBackOrExit();
                }
                break;
            case 6:
                if(user.userPermission == -1 || (user.userPermission & UserAccess::Transactions)) {
                    AppScreens::showTransactionsScreen();
                    running = SystemUtils::goBackOrExit();
                }
                else{
                    DisplayManager::printAccessDenied();
                    running = SystemUtils::goBackOrExit();
                }
               
                break;
            case 7:
                if(user.userPermission == -1 || (user.userPermission & UserAccess::ManageUsers)) {
                    AppScreens::showManageUsers();
                    running = SystemUtils::goBackOrExit();
                }
                else{
                    DisplayManager::printAccessDenied();
                    running = SystemUtils::goBackOrExit();
                }
               
                break;// بسبب دي انا  ضيعت اكتر من 5 ساعات
            case 8:
                running = false;
                break;
            default:
                cout << "Invalid choice, try again.\n";
                break;
        }
    }
    
}



/**
 * Handles the user authentication process
 * Validates username and password against stored credentials
 */
void login() {
    string userNmae;
    string password;
    UserDate user;
    bool running = true;
    while (running)
    {
        cout << endl;
        cout << "====================================================\n";
        cout << "\t\tLogin Screen\n";
        cout << "====================================================\n";
        userNmae = InputManager::readUserName();
        password = InputManager::readUserPassword();
        if(SearchManager::doesUserExist(userNmae) && SearchManager::doesUserPasswordExist(password)) {
            user = SearchManager::ReturnUserFormFile(userNmae, password ,user);
            showMainMenu(user);
            running = SystemUtils::goBackOrExit("\n\nPress [Enter] to go back to Login: ");
        }
        else {
            cout <<" \ntry again.";
        }
    }  
}

/**
 * Main entry point of the Bank Management System
 * Initializes the application and starts the main menu
 * @return 0 on successful program termination
 */
/**
 * Main entry point of the application
 * Initializes the system and starts the login process
 * @return 0 on successful completion
 */
int main() {
    login();
    
    return 0;
}
