#pragma onec
#include <iostream>
#include "clsScreen.h"
#include "clsBankClient.h"
#include <iomanip>
using namespace std;

class clsClientListScreen: protected clsScreen {
    private:

    public:
        static void ShowClientsList() {
            vector <clsBankClient> vClients = clsBankClient::GetClientsList();
        
            string Title = "\t Client List Screen";
            string SubTitle = "\t (" + to_string(vClients.size()) + ")Client(s)."; 
            _DrawScreenHeader(Title, SubTitle);
            cout << "\n_______________________________________________________________________________________________________________________\n";
                
            // Print table header
            cout << "| " << left << setw(15) << "Accout Number";
            cout << "| " << left << setw(20) << "Client Name";
            cout << "| " << left << setw(12) << "Phone";
            cout << "| " << left << setw(25) << "Email";
            cout << "| " << left << setw(10) << "Pin Code";
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
                    cout << "| " << setw(20) << left << client.FullName();
                    cout << "| " << setw(12) << left << client.Phone();
                    cout << "| " << setw(25) << left << client.Email();
                    cout << "| " << setw(10) << left << client.GetPinCode();
                    cout << "| " << setw(12) << left << client.AccountBalance();
                    cout << "|\n";
                }
            }
            cout << "_______________________________________________________________________________________________________________________\n";
        }
};

