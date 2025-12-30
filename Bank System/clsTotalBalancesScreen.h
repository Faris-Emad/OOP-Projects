#pragma once
#include <iostream>
#include <iomanip>
#include "clsScreen.h"
#include "clsBankClient.h"
#include "clsUtility.h"
using namespace std;


class clsTotalBalancesScreen : protected clsScreen
{
    private:
        
    public:
        static void ShowTotalBalances() {
            vector <clsBankClient> vClients = clsBankClient::GetClientsList();
            
            cout << "\n\t\t\t\t\tBalances List (" << vClients.size() << ") Client(s).\n";
            cout << "\n_______________________________________________________________________________________________________________________\n";
            
            // Print table header
            cout << "| " << left << setw(15) << "Accout Number";
            cout << "| " << left << setw(40) << "Client Name";
            cout << "| " << left << setw(12) << "Balance";
            cout << "|\n_______________________________________________________________________________________________________________________\n";
            
            
            if(vClients.size() == 0) {
                cout << "\t\t\t\tNo Clients Available In the System!";
            }
            else {
                cout << fixed << setprecision(2);
                // Print client data rows
                for(clsBankClient& client : vClients) {
                    cout << "| " << setw(15) << left << client.AccountNumber();
                    cout << "| " << setw(40) << left << client.FullName();
                    cout << "| " << setw(12) << left << client.AccountBalance();
                    cout << "|\n";
                    
                }
            }
            cout << "_______________________________________________________________________________________________________________________\n";
            cout << "\n\t\t\t\t\t   Total Balances = " << clsBankClient::GetTotalBalances() << endl;
            cout << "\n\t\t\t"<< clsUtility::NumberToText(clsBankClient::GetTotalBalances()) << endl;
        }

};

