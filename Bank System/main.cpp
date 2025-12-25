#include <iostream>
#include "clsBankClient.h"
#include "clsInputValidate.h"
#include "clsUtiliy.h"
#include "clsMainScreen.h"
using namespace std;



void ReadClientInfo(clsBankClient& Client){
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

void UpdateClient(){
    string AccountNumber = "";
    AccountNumber = clsInputValidate::ReadString("Please Enter Account Number: ");
    while (!clsBankClient::IsClientExist(AccountNumber))
    {
        cout << "\nAccount number is not found, choose another one: ";
        AccountNumber = clsInputValidate::ReadString();
    }
    clsBankClient Client1 = clsBankClient::Find(AccountNumber);
    Client1.PrintInfo();
    cout << "\n\nUpdate Client Info:";
    cout << "\n---------------------\n";
    ReadClientInfo(Client1);

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



void DeleteClient() {
    string AccountNumber = "";
    cout << "Please Enter Account Number: " ;
    AccountNumber = clsInputValidate::ReadString();
    while (!clsBankClient::IsClientExist(AccountNumber)) {
        cout << "Account Number Is Not Found, Choose another one: ";
        AccountNumber = clsInputValidate::ReadString();
    }
    clsBankClient Client = clsBankClient::Find(AccountNumber);
    Client.PrintInfo();
    cout << "\n Are you sure you want to delete this client y/n?";
    char Answer = 'n';
    cin >> Answer;
    if(Answer == 'y' || Answer == 'Y') {
        if(Client.Delete()) {
            cout << "\nClient Deleted Successfully\n";
            Client.PrintInfo();
        }
        else 
            cout << "\nError Client Was Not Deleted\n";
    }
}


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
            cout << "| " << setw(12) << left << client.GetAccountBalance();
            cout << "|\n";
            
        }
    }
    cout << "_______________________________________________________________________________________________________________________\n";
    cout << "\n\t\t\t\t\t   Total Balances = " << clsBankClient::GetTotalBalances() << endl;
    cout << "\n\t\t\t"<< clsUtiliy::NumberToText(clsBankClient::GetTotalBalances()) << endl;
}

int main() {
    //UpdateClient();
    //AddNewClient();
    //DeleteClient();
    //ShowClientsList();
    //ShowTotalBalances();

    clsMainScreen::ShowMainMenu();
    return 0;
}
