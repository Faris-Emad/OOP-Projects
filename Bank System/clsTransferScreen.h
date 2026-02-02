#pragma once
#include <iostream>
#include <iomanip>
#include "clsScreen.h"
#include "clsBankClient.h"
#include "clsUtility.h"
#include "clsInputValidate.h"


class clsTransferScreen : protected clsScreen {
    private:
        
        static string _ReadAccountNumber(string massage) {
            cout << massage << endl;
            string AccountNumber  = clsInputValidate::ReadString();
            return AccountNumber;
        }
        static bool IsAccountNumberFound(string& AccountNumber) {
            while (true) {
                // Check cancellation FIRST
                if (AccountNumber == "cancel" || AccountNumber == "0") {
                    return false;
                }
                
                // Check if exists
                if (clsBankClient::IsClientExist(AccountNumber)) {
                    return true;
                }
                
                // Not found - prompt again
                cout << "Account Number Is Not Found, Choose another one (or '0' to cancel): ";
                AccountNumber = clsInputValidate::ReadString();
            }
        }
        static bool verifyRecipientAccountNumber(string& RecipientAccount, string& SenderAccount) {
            while (true) {
                // ✅ ADD: Check cancellation
                if (RecipientAccount == "cancel" || RecipientAccount == "0") {
                    return false;
                }
                
                if (RecipientAccount == SenderAccount) {
                    cout << "Cannot transfer to the same account! Enter another (or '0' to cancel): ";
                    RecipientAccount = clsInputValidate::ReadString();
                    continue;
                }
                
                if (!clsBankClient::IsClientExist(RecipientAccount)) {
                    cout << "Account not found! Enter another (or '0' to cancel): ";
                    RecipientAccount = clsInputValidate::ReadString();
                    continue;
                }
                
                return true; 
            }
        }
        static bool ValidateAmount(clsBankClient& Sender, double& Amount) {
            while (Amount <= 0 || Amount > Sender.AccountBalance()) {
                if(Amount <= 0 && Amount != -1) {  // -1 = cancel signal
                    cout << "Amount must be positive!!\n";
                }
                else if (Amount > Sender.AccountBalance()) {
                    cout << "Insufficient balance! Available: " << Sender.AccountBalance() << "\n";
                }
                
                cout << "Enter Transfer Amount (or 0 to cancel): ";
                Amount = clsInputValidate::ReadDblNumber();
                
                // ✅ Check for cancellation
                if (Amount == 0) {
                    return false;  // User cancelled
                }
            }
            
            return true;  // Validation passed
        }
        static void confirmAndProcessMoneyTransfer(clsBankClient& Sender, clsBankClient& Recipient, double Amount) {
            // ✅ Check if validation succeeded
            if (!ValidateAmount(Sender, Amount)) {
                cout << "\nOperation cancelled by user.\n";
                return;  // Exit early
            }
            
            cout << "\nYou are about to transfer $" << Amount 
                << " from " << Sender.FullName() 
                << " to " << Recipient.FullName() << endl;
                
            if(clsInputValidate::AskYesNo("Are You Sure?") == 'y') {
                if(Sender.Transfer(Amount, Recipient)) {
                    cout << "\nTransfer completed successfully!\n\n";
                    Sender.PrintCard();
                    Recipient.PrintCard();
                } else {
                    cout << "\nTransfer failed! Please contact support.\n";
                }
            } else {
                cout << "\nOperation cancelled by user.\n";
            }
        }
        
        static double ReadAmount() {  
            cout << "Enter Transfer Amount: ";
            return clsInputValidate::ReadDblNumber();
        }
        
    public:
        
        static void ShowTransfer() {
            _DrawScreenHeader("Transfer Screen");
            string AccountNumberFrom  = _ReadAccountNumber("Please Enter Account Number to Transfer From: ");

            if(IsAccountNumberFound(AccountNumberFrom)){
                clsBankClient Sender = clsBankClient::Find(AccountNumberFrom);
                Sender.PrintCard();
                string AccountNumberTo = _ReadAccountNumber("\nPlease Enter Account Number to Transfer To: "); 
                if(verifyRecipientAccountNumber(AccountNumberTo, AccountNumberFrom)) {
                    clsBankClient Recipient =  clsBankClient::Find(AccountNumberTo);
                    Recipient.PrintCard();
                    double Amount = ReadAmount();
                    confirmAndProcessMoneyTransfer(Sender,Recipient,Amount);
                }
            }
        }
};


