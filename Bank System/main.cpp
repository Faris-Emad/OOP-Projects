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


void AddNewClient() {
    string AccountNumber = "";
    cout << "Please Enter Account Number: " ;
    AccountNumber = clsInputValidate::ReadString();
    while (clsBankClient::IsClientExist(AccountNumber)) {
        cout << "Account Number Is Already Used, Choose another one: ";
        AccountNumber = clsInputValidate::ReadString();
    }
    clsBankClient NewClient = clsBankClient::GetAddNewClientObject(AccountNumber);
    ReadClientInfo(NewClient);
    clsBankClient::enSaveResults SaveResult;

    SaveResult = NewClient.Save();
        switch (SaveResult)
    {
        case clsBankClient::enSaveResults::svSucceeded:{
            cout << "\nAccount Add Successfully :-)\n";
            NewClient.PrintInfo();
            break;
        }
        case clsBankClient::enSaveResults::svFaildEmptyObject: {
            cout << "\nError account was not saved because it's Empty";
            break;
        }
        case clsBankClient::enSaveResults::svFaildAccountNumberExists:{
            cout << "\nError account was not saved because already is Exists";
            break;
        }
    }
}

int main() {
    //UpdateClient();
    AddNewClient();
    return 0;
}