#pragma onec
#include <iostream>
#include "clsScreen.h"
#include "clsBankClient.h"
#include <iomanip>
#include "clsInputValidate.h"
using namespace std;


class clsDeleteClientScreen : protected clsScreen {
    private:
            static void _PrintClient(clsBankClient Client) {
            cout << "==================================================\n";
            cout << "              Clinet Card\n";
            cout << "==================================================\n";
            cout << "First Name : " << Client.FirstName() << endl;
            cout << "Last Name  : " << Client.LastName() << endl;
            cout << "Full Name  : " << Client.FullName() << endl;
            cout << "Email      : " << Client.Email() << endl;
            cout << "Phone      : " << Client.Phone() << endl;
            cout << "Acc.Number : " << Client.AccountNumber() << endl;
            cout << "Password   : " << Client.GetPinCode() << endl;
            cout << "Balance    : " << Client.GetAccountBalance() << endl;
        }
    public:
        static void DeleteClient() {
            string AccountNumber = "";
            cout << "Please Enter Account Number: " ;
            AccountNumber = clsInputValidate::ReadString();
            while (!clsBankClient::IsClientExist(AccountNumber)) {
                cout << "Account Number Is Not Found, Choose another one: ";
                AccountNumber = clsInputValidate::ReadString();
            }
            clsBankClient Client = clsBankClient::Find(AccountNumber);
            _PrintClient(Client);
            cout << "\n Are you sure you want to delete this client y/n?";
            char Answer = 'n';
            cin >> Answer;
            if(Answer == 'y' || Answer == 'Y') {
                if(Client.Delete()) {
                    cout << "\nClient Deleted Successfully\n";
                    _PrintClient(Client);
                }
                else 
                    cout << "\nError Client Was Not Deleted\n";
            }
        }
};
