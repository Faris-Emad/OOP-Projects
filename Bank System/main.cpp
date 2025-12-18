#include <iostream>
#include "clsBankClient.h"
#include "clsInputValidate.h"
using namespace std;



void ReadClientInfo(clsBankClient& Client)
{
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
}


int main() {
    UpdateClient();
    return 0;
}