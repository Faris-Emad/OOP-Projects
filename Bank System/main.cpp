#include <iostream>
#include "clsBankClient.h"
#include "clsInputValidate.h"
#include "clsUtiliy.h"
#include "clsMainScreen.h"
using namespace std;

void ShowTotalBalances() {
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
    cout << "\n\t\t\t"<< clsUtiliy::NumberToText(clsBankClient::GetTotalBalances()) << endl;
}

int main() {
    
    clsMainScreen::ShowMainMenu();
    return 0;
}
