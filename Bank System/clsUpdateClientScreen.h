#pragma once
#include <iostream>
#include "clsScreen.h"
#include "clsBankClient.h"
#include <iomanip>
#include "clsInputValidate.h"
using namespace std;



class clsUpdateClientScreen : protected clsScreen {
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
        
        static void UpdateClient() {
            if(!CheckAccessRights(clsUser::UserAccess::UpdateClient))
                return;
            _DrawScreenHeader("\tUpdate Client Screen");
            string AccountNumber = "";
            AccountNumber = clsInputValidate::ReadString("Please Enter Account Number: ");
            while (!clsBankClient::IsClientExist(AccountNumber))
            {
                cout << "\nAccount number is not found, choose another one: ";
                AccountNumber = clsInputValidate::ReadString();
            }
            clsBankClient Client1 = clsBankClient::Find(AccountNumber);
            _PrintClient(Client1);
            cout << "\n\nUpdate Client Info:";
            cout << "\n---------------------\n";
            _ReadClientInfo(Client1);

            clsBankClient::enSaveResults SaveResult;
            SaveResult = Client1.Save();

            switch (SaveResult)
            {
                case clsBankClient::enSaveResults::svSucceeded:
                {
                    cout << "\nAccount Updated Successfully :-)\n";
                    Client1.PrintInfo();
                    break;
                }
                case clsBankClient::enSaveResults::svFaildEmptyObject:
                {
                    cout << "\nError account was not saved because it's Empty";
                    break;
                }
            }
        }


};

