#pragma once
#include <iostream>
#include <iomanip>
#include "clsScreen.h"
#include "clsBankClient.h"
#include "clsInputValidate.h"
using namespace std;


class clsWithdrawScreen : protected clsScreen
{
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
            cout << "Balance    : " << Client.AccountBalance() << endl;
        }
    public:
       static void ShowWithdrawScreen() {
            _DrawScreenHeader("Withdraw Screen");
            cout << "Enter Account Number:";
            string AccountNumber = clsInputValidate::ReadString();
            while (!clsBankClient::IsClientExist(AccountNumber)) {
                cout << "\nClient with [" << AccountNumber << "] does not exist.\n";
                AccountNumber = clsInputValidate::ReadString();
            }
            clsBankClient Client = clsBankClient::Find(AccountNumber);
            _PrintClient(Client);
            cout << endl;
            double Withdraw = 0;
            cout << "\nPlease enter withdraw amount: ";
            Withdraw = clsInputValidate::ReadDblNumber();

            char Answer = 'n';
            cout << "\n\nAre you sure you want to withdraw? y/n ? ";
            Answer = clsInputValidate::ReadChar();
            if(Answer == 'Y' || Answer == 'y') {
                
                if(Client.Withdraw(Withdraw)) {
                    cout << "\nAmount withdraw Successful.\n";
                    cout << "\nNew Balance Is: " << Client.AccountBalance();
                    cout << endl;
                }
                else {
                    
                    cout << "Can not withdraw, insuffecient Balance!\n";
                    cout << "Amout to withdraw is : " << Withdraw << endl;
                    cout << "Your Balance is : " << Client.AccountBalance();
                }
               
            }
            else {
                cout << "\nOperation was cancelled.\n";
            }
       }
};

