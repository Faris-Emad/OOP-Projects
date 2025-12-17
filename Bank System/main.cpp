#include <iostream>
#include "clsBankClient.h"
#include "clsInputValidate.h"
using namespace std;



void ReadClientInfo(clsBankClient& Client) {
        Client.SetPinCode(clsInputValidate::ReadString("Enter PinCode? "));
        cout << endl;
        cout << "Enter Account Balnce: ";
        cin >> Client.SetAccountBalance(clsInputValidate::ReadDblNumber("Error"))
        cin.ignore(numeric_limits<streamsize>::max(), '\n');

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