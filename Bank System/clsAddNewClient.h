#pragma once
#include <iostream>
#include "clsScreen.h"
#include "clsBankClient.h"
#include <iomanip>
#include "clsInputValidate.h"
using namespace std;

class clsAddNewClient : protected clsScreen
{
private:
        
    static void _ReadClientInfo(clsBankClient& Client){
        cout << "\nEnter FirstName: ";
        Client.SetFirstName(clsInputValidate::ReadString());

        cout << "\nEnter LastName: ";
        Client.SetLastName(clsInputValidate::ReadString());

        cout << "\nEnter Email: ";
        Client.SetEmail(clsInputValidate::ReadString());

        cout << "\nEnter Phone: ";
        Client.SetPhone(clsInputValidate::ReadString());

        cout << "\nEnter PinCode: ";
        Client.SetPinCode(clsInputValidate::ReadString());

        cout << "\nEnter Account Balance: ";
        Client.SetAccountBalance(clsInputValidate::ReadDblNumber());
    }

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
        cout << "Balance    : " << Client.AccountBalance() << endl;
    }

public:
    static void AddNewClient() {
        _DrawScreenHeader("Add New Client Screen");
        string AccountNumber = "";
        cout << "Please Enter Account Number: " ;
        AccountNumber = clsInputValidate::ReadString();
        while (clsBankClient::IsClientExist(AccountNumber)) {
            cout << "Account Number Is Already Used, Choose another one: ";
            AccountNumber = clsInputValidate::ReadString();
        }
        clsBankClient NewClient = clsBankClient::GetAddNewClientObject(AccountNumber);
        _ReadClientInfo(NewClient);
        clsBankClient::enSaveResults SaveResult;

        SaveResult = NewClient.Save();
        switch (SaveResult) {
            case clsBankClient::enSaveResults::svSucceeded:{
                cout << "\nAccount Add Successfully :-)\n\n";
                _PrintClient(NewClient);
                break;
            }
            case clsBankClient::enSaveResults::svFaildEmptyObject: {
                cout << "\nError account was not saved because it's Empty";
                break;
            }
            case clsBankClient::enSaveResults::svFaildAccountNumberExists:{
                cout << "\nError account was not saved because already is Exists";
                break;
            }
        }
    }

};

