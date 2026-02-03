#pragma once
#include <iostream>
#include <fstream>
#include <string>
#include <vector>
#include "clsString.h"
#include "clsPerson.h"
#include "Global.h"
using namespace std;



class clsBankClient : public clsPerson
{
private:
    static inline string SEPARATOR = "#//#";
    enum enMode {EmptyMode = 0, UpdateMode = 1, AddNewMode = 2};
    enMode _Mode;
    string _AccountNumber;
    string _PinCode;
    double _AccountBalance;
    bool _MarkForDelete = false;
    static clsBankClient _ConvertLineToClientObject(string line) {
        vector<string> vClientData = clsString::SplitString(line, SEPARATOR);
        return clsBankClient(enMode::UpdateMode, vClientData[0], vClientData[1],vClientData[2],
            vClientData[3],vClientData[4],vClientData[5],stod(vClientData[6]));
    }
    static string _ConverClientObjectToLine(clsBankClient Client) {
            string DataLine = "";
            DataLine += Client.FirstName() + SEPARATOR;
            DataLine += Client. LastName() + SEPARATOR;
            DataLine += Client.Email() + SEPARATOR;
            DataLine += Client.Phone() + SEPARATOR;
            DataLine += Client. AccountNumber() + SEPARATOR;
            DataLine += Client.GetPinCode() + SEPARATOR;
            DataLine += to_string(Client.AccountBalance());
            return DataLine;
    }
    static clsBankClient _GetEmptyClientObject() {
        return clsBankClient(enMode::EmptyMode, "", "", "", "", "","", 0);
    }

    static vector<clsBankClient>  _LoadClientsDataFromFile() {
        vector<clsBankClient> _vClients;
        fstream MyFile;
        MyFile.open("Clients.txt", ios::in);
        if(MyFile.is_open()) {
            string Line;
            while (getline(MyFile, Line)) {
                clsBankClient Client = _ConvertLineToClientObject(Line);
                _vClients.push_back(Client);
            }
            MyFile.close();

        }
        return _vClients;
    }

    static void _SaveClientsDataToFile(vector<clsBankClient> _vClients) {
        fstream MyFile;
        MyFile.open("Clients.txt", ios::out); // Open file for writing (overwrites existing)
        string DataLine;
        if(MyFile.is_open()) {
            for(clsBankClient& C : _vClients) {
                if(C._MarkForDelete == false) {
                    DataLine = _ConverClientObjectToLine(C);
                    MyFile << DataLine << endl;
                }

            }
            MyFile.close();
        }
    }

    void _Update() {
        vector<clsBankClient> _vClients;
        _vClients = _LoadClientsDataFromFile();
        for(clsBankClient& C : _vClients) {
            if(C.AccountNumber() == AccountNumber()){
                C = *this;
                break;
            }
        }
        _SaveClientsDataToFile(_vClients);
    }
    void _AddNew() {
        _AddDateLineToFile(_ConverClientObjectToLine(*this));
    }

    void _AddDateLineToFile(string stDateLine) {
        fstream MyFile;
        MyFile.open("Clients.txt", ios::out | ios::app); 
        if(MyFile.is_open()) {
            MyFile << stDateLine << endl;
            MyFile.close();
        }
    }
    static  string _PrepareLogInRecord(string SourceAccount, string DestAccount, double Amount,     double SourceBalanceAfter,
        double DestBalanceAfter, string Username) {
        string LogRecord = "";
        LogRecord += clsDate::GetSystemDateTimeString() + SEPARATOR;
        LogRecord += SourceAccount + SEPARATOR;
        LogRecord += DestAccount + SEPARATOR;
        LogRecord += to_string(Amount) + SEPARATOR;
        LogRecord += to_string(SourceBalanceAfter) + SEPARATOR;
        LogRecord += to_string(DestBalanceAfter) + SEPARATOR;
        LogRecord += Username;
        return LogRecord;
    }
    void _SaveTransferLog(string SourceAccount, string DestAccount, double Amount,     double SourceBalanceAfter,
        double DestBalanceAfter, string Username){
        string stDataLine = _PrepareLogInRecord(SourceAccount, DestAccount, Amount, 
                SourceBalanceAfter, DestBalanceAfter, Username);
        fstream MyFile;
        MyFile.open("TransferLogs.txt", ios::out | ios::app);
        if(MyFile.is_open()) {
            MyFile << stDataLine << endl;
            MyFile.close();
        }
    }


public:
    clsBankClient(enMode Mode, string FirstName, string LastName,
                 string Email, string Phone, string AccountNumber, string PinCode,
                  float AccountBalance) : clsPerson(FirstName, LastName, Email,Phone) {
        _Mode = Mode;
        _PinCode = PinCode;
        _AccountNumber = AccountNumber;
        _AccountBalance = AccountBalance;

    };
    bool IsEmpty() {
        return(_Mode == enMode::EmptyMode);
    }
    string AccountNumber() {
        return _AccountNumber;
    }
    void SetAccountBalance(float AccountBalance) {
        _AccountBalance = AccountBalance;
    }
    double AccountBalance() {
        return _AccountBalance;
    }
    void SetPinCode(string PinCode) {
        _PinCode = PinCode;
    }
    string GetPinCode() {
        return _PinCode;
    }
    
    static clsBankClient Find(string AccountNumber) {
        vector <clsBankClient> vClient;
        fstream MyFile;
        MyFile.open("Clients.txt", ios::in);
        if(MyFile.is_open()) {
            string Line;
            while (getline(MyFile, Line)) {
                clsBankClient Client = _ConvertLineToClientObject(Line);
                if(Client.AccountNumber() == AccountNumber) {
                    MyFile.close();
                    return Client;
                }
                vClient.push_back(Client);
            }
            MyFile.close();

        }
        return _GetEmptyClientObject();
    }
    static clsBankClient Find(string AccountNumber, string PinCode) {
        vector <clsBankClient> vClient;
        fstream MyFile;
        MyFile.open("Clients.txt", ios::in);
        if(MyFile.is_open()) {
            string Line;
            while (getline(MyFile, Line)) {
                clsBankClient Client = _ConvertLineToClientObject(Line);
                if(Client.AccountNumber() == AccountNumber && Client._PinCode == PinCode) {
                    MyFile.close();
                    return Client;
                }
                vClient.push_back(Client);
            }
            MyFile.close();

        }
        return _GetEmptyClientObject();
    }
    static bool IsClientExist(string AccountNumber) {
        clsBankClient Client = clsBankClient::Find(AccountNumber);
        return (!Client.IsEmpty());
    }
    static bool IsClientExist(string AccountNumber, string PinCode) {
        clsBankClient Client = clsBankClient::Find(AccountNumber, PinCode);
        return (!Client.IsEmpty());
    }
    enum enSaveResults {svFailedEmptyObject =0, svSucceeded = 1, svFailedAccountNumberExists = 2};
    enSaveResults Save() {
        switch (_Mode) {
            case enMode::EmptyMode: {
                return enSaveResults::svFailedEmptyObject;
                break;
            }
            case enMode::UpdateMode: {
                _Update();
                return enSaveResults::svSucceeded;
                break;
            }
            case enMode::AddNewMode: {
                if(clsBankClient::IsClientExist(_AccountNumber)) {
                    return enSaveResults::svFailedAccountNumberExists;
                }
                else {
                    _AddNew();
                    _Mode = enMode::UpdateMode;
                    return enSaveResults::svSucceeded;
                }
                break;
            }

            default:   
                return enSaveResults::svFailedEmptyObject;

        }
    }
    static clsBankClient GetAddNewClientObject(string AccountNumber) {
        return clsBankClient(enMode::AddNewMode, "", "", "","", AccountNumber, "",0);
    }
    // Delete form file and retrun Null Object 
    bool Delete() {
        vector <clsBankClient> _Clients = _LoadClientsDataFromFile();
        for(clsBankClient& C : _Clients) {
            if (C.AccountNumber() == _AccountNumber)
            {
                C._MarkForDelete = true;
                break;
            }  
        }
        _SaveClientsDataToFile(_Clients);
        *this = _GetEmptyClientObject();
        return true;
    }

    static vector <clsBankClient> GetClientsList() {
        return _LoadClientsDataFromFile();
    }
    static double GetTotalBalances() {
        vector <clsBankClient> vClients = clsBankClient::GetClientsList();
        double TotalBalances = 0;
        for(clsBankClient Client : vClients){
            TotalBalances += Client._AccountBalance;
        }
        return TotalBalances;
    }
    void Deposit(double Amount) {
        _AccountBalance += Amount;    
        Save();
    }
    bool Withdraw(double Amount) {
        if(Amount > _AccountBalance)
            return false;
        else { 
            _AccountBalance -= Amount;    
            Save();
        }
        return true;
    }
    bool Transfer(float Amount, clsBankClient& DestinationClient, string UserName) {
        if(Amount > AccountBalance())
            return false;
        Withdraw(Amount);
        DestinationClient.Deposit(Amount);
        _SaveTransferLog(this->AccountNumber(), DestinationClient.AccountNumber(), Amount, 
                    this->AccountBalance(), DestinationClient.AccountBalance(), UserName);
        return true;
    }
    
    void PrintCard() {
        cout << "\n==================================================\n";
        cout << "Full Name       : " << FullName() << endl; 
        cout << "Account Number  : " << AccountNumber() << endl;
        cout << "Account Balacne : " << AccountBalance() << endl;
        cout << "==================================================\n";
    }
    struct stTransferLog {
        string DateTime;
        string SourceAccount;
        string DestinationAccount;
        double Amount;
        double SourceBalanceAfter;
        double DestBalanceAfter;
        string Username;  
    };
    static stTransferLog _ConvertLineToSturct(string line) {
        vector<string> vTransfersData = clsString::SplitString(line, SEPARATOR);
        stTransferLog TransferData;
        TransferData.DateTime = vTransfersData[0];
        TransferData.SourceAccount = vTransfersData[1];
        TransferData.DestinationAccount = vTransfersData[2];
        TransferData.Amount = stod(vTransfersData[3]);
        TransferData.SourceBalanceAfter = stod(vTransfersData[4]);
        TransferData.DestBalanceAfter = stod(vTransfersData[5]);
        TransferData.Username = vTransfersData[6];
        return TransferData;
    }
    static vector<stTransferLog> _LoadTransferLoginDataFromFile() {
        vector<stTransferLog> vTransfersData;
        fstream MyFile;
        MyFile.open("TransferLogs.txt", ios::in);
        if(MyFile.is_open()) {
            string Line; 
            while (getline(MyFile, Line)) {
                stTransferLog Data = _ConvertLineToSturct(Line);
                vTransfersData.push_back(Data);
            }
            MyFile.close();
        }
        return vTransfersData;
    }
    static vector <stTransferLog> GetTransferLoginList() {
        return  _LoadTransferLoginDataFromFile();
    }

           
};
