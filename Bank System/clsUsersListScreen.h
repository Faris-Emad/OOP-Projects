#pragma onec
#include <iomanip>
#include <iostream>
#include "clsScreen.h"
#include "clsUsers.h"
using namespace std;

class clsUsersListScreen : protected clsScreen
{
    private:

    public:
        static void ShowUsersList() {
            vector <clsUser> vUsers = clsUser::GetUsersList();
        
            string Title = "\t User List Screen";
            string SubTitle = "\t (" + to_string(vUsers.size()) + ") User(s)."; 
            _DrawScreenHeader(Title, SubTitle);
            cout << "\n_______________________________________________________________________________________________________________________\n";
                
            // Print table header
            cout << "| " << left << setw(15) << "Username";
            cout << "| " << left << setw(20) << "Full Name";
            cout << "| " << left << setw(12) << "Phone";
            cout << "| " << left << setw(25) << "Email";
            cout << "| " << left << setw(10) << "Password";
            cout << "| " << left << setw(12) << "Permissions";
            cout << "|\n_______________________________________________________________________________________________________________________\n";
                
            if(vUsers.size() == 0) {
                cout << "\t\t\t\tNo Users Available In the System!";
            }
            else {
                // Print user data rows
                for(clsUser& user : vUsers) {
                    cout << "| " << setw(15) << left << user.GetUserName();
                    cout << "| " << setw(20) << left << user.FullName();
                    cout << "| " << setw(12) << left << user.Phone();
                    cout << "| " << setw(25) << left << user.Email();
                    cout << "| " << setw(10) << left << user.GetPassword();
                    cout << "| " << setw(12) << left << user.GetPermissions();
                    cout << "|\n";
                }
            }
            cout << "_______________________________________________________________________________________________________________________\n";
        }
};

