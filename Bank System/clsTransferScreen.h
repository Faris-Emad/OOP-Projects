#pragma once
#include <iostream>
#include <iomanip>
#include "clsScreen.h"
#include "clsBankClient.h"
#include "clsUtility.h"
#include "clsInputValidate.h"


class clsTransferScreen : protected clsScreen {
    private:
        
    public:
        
        static void ShowTransfer() {
            _DrawScreenHeader("Transfer Screen");
            cout << "Please Enter Account Number to Transfer From: ";
            string AccountNumberFrom  = clsInputValidate::ReadString();
            while (!clsBankClient::IsClientExist(AccountNumberFrom)) {
                cout << "Account Number Is Not Found, Choose another one: ";
                AccountNumberFrom  = clsInputValidate::ReadString();
            }
            clsBankClient Client = clsBankClient::Find(AccountNumberFrom);
            string AccountNumberTo = "";
            Client.PrintCard();
           do
            {
                cout << "\nPlease Enter Account Number to Transfer To: ";
                AccountNumberTo = clsInputValidate::ReadString();
            
                if (AccountNumberTo == AccountNumberFrom) {
                    cout << "Cannot transfer to the same account!";
                    continue;
                }
                if (!clsBankClient::IsClientExist(AccountNumberTo)) {
                    cout << "Account not found!";
                    continue;
                }
                break;
            } while (true);
            clsBankClient Client2 =  clsBankClient::Find(AccountNumberTo);
            Client2.PrintCard();
            cout << "Enter Transfer Amount: ";
            double  Amount = clsInputValidate::ReadDblNumber();
            while(Amount > Client.AccountBalance()) {
                cout << "Amount Exceeds the available Balance(" << Client.AccountBalance() << ")\n";
                cout << "Enter another Amount: ";
                Amount = clsInputValidate::ReadDblNumber();
            }
            cout << "\nYou are about to transfer $" << Amount 
                    << " from " << AccountNumberFrom 
                    << " to " << AccountNumberTo << endl;
            if(clsInputValidate::AskYesNo("Are You Sure?") == 'y') {
                Client.Withdraw(Amount);
                Client2.Deposit(Amount);
                cout << "\nTransfer completed successfully!\n";
                cout << "\nUpdated Account Details:\n";
                cout << "\n";
                Client.PrintCard();
                Client2.PrintCard();
            }else {
                
                cout << "\nOperation Cancelled.\n";
            }
        }
};


