#pragma once
#include <iostream>
#include "clsScreen.h"
#include "clsBankClient.h"
#include <iomanip>
#include "clsInputValidate.h"


class clsFindClientScreen : protected clsScreen {
    private:
        static void _PrintClient(clsBankClient Client) {
            cout << "==================================================\n";
            cout << "              Client Card\n";
            cout << "==================================================\n";
            cout << "First Name : " << Client.FirstName() << endl;
            cout << "Last Name  : " << Client.LastName() << endl;
            cout << "Full Name  : " << Client.FullName() << endl;
            cout << "Email      : " << Client.Email() << endl;
            cout << "Phone      : " << Client.Phone() << endl;
            cout << "Acc.Number : " << Client.AccountNumber() << endl;
            cout << "Password   : " << Client.GetPinCode() << endl;
            cout << "Balance    : " << Client.AccountBalance() << endl;
        }
        
    public:
        static void ShowFindClientScreen() {
            if(!CheckAccessRights(clsUser::UserAccess::FindClient))
                return;
            _DrawScreenHeader("\t Find Client Screen");
            string AccountNumber = "";
            AccountNumber = clsInputValidate::ReadString("Please Enter Account Number: ");
            while (!clsBankClient::IsClientExist(AccountNumber))
            {
                cout << "\nAccount number is not found, choose another one: ";
                AccountNumber = clsInputValidate::ReadString();
            }
            clsBankClient Client1 = clsBankClient::Find(AccountNumber);
            if(!Client1.IsEmpty()) {
                cout << "Client found ;)" << endl;
            }
            _PrintClient(Client1);

        }
        
};

