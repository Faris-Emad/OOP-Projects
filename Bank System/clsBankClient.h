#pragma once
#include <iostream>
#include <fstream>
#include <string>
#include <vector>
#include "clsString.h"
#include "clsPerson.h"
using namespace std;

const string SEPARATOR = "#//#";

class clsBankClient : public clsPerson
{
private:
    enum enMode {EmptyMode = 0, UpdateMode = 1};
    enMode _Mode;
    string _AccountNumber;
    string _PinCode;
    float _AccountBalance;
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
            DataLine += to_string(Client.GetAccountBalance());
            return DataLine;
    }
    static clsBankClient _GetEmptyClinetObject() {
        return clsBankClient(enMode::EmptyMode, "", "", "", "", "","", 0);
    }

    static vector<clsBankClient>  _LoadClientsDataFromFile() {
        vector<clsBankClient> _vClients;
        fstream MyFile;
        MyFile.open("Clients.txt", ios::in);
        if(MyFile.is_open()) {
            string Line;
            while (getline(MyFile, Line)) {
                clsBankClient Clinet = _ConvertLineToClientObject(Line);
                _vClients.push_back(Clinet);
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
            for(clsBankClient C : _vClients) {
                DataLine = _ConverClientObjectToLine(C);
                MyFile << DataLine << endl;
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
    float GetAccountBalance() {
        return _AccountBalance;
    }
    void SetPinCode(string PinCode) {
        _PinCode = PinCode;
    }
    string GetPinCode() {
        return _PinCode;
    }

    void PrintInfo() {
        cout << "==================================================\n";
        cout << "              Clinet Card\n";
        cout << "==================================================\n";
        cout << "First Name : " << FirstName() << endl;
        cout << "Last Name  : " << LastName() << endl;
        cout << "Full Name  : " << FullName() << endl;
        cout << "Email      : " << Email() << endl;
        cout << "Phone      : " << Phone() << endl;
        cout << "Acc.Number : " << _AccountNumber << endl;
        cout << "Password   : " << _PinCode << endl;
        cout << "Balance    : " << _AccountBalance << endl;
    }

    static clsBankClient Find(string AccountNumber) {
        vector <clsBankClient> vClinet;
        fstream MyFile;
        MyFile.open("Clients.txt", ios::in);
        if(MyFile.is_open()) {
            string Line;
            while (getline(MyFile, Line)) {
                clsBankClient Clinet = _ConvertLineToClientObject(Line);
                if(Clinet.AccountNumber() == AccountNumber) {
                    MyFile.close();
                    return Clinet;
                }
                vClinet.push_back(Clinet);
            }
            MyFile.close();

        }
        return _GetEmptyClinetObject();
    }
    static clsBankClient Find(string AccountNumber, string PinCode) {
        vector <clsBankClient> vClinet;
        fstream MyFile;
        MyFile.open("Clients.txt", ios::in);
        if(MyFile.is_open()) {
            string Line;
            while (getline(MyFile, Line)) {
                clsBankClient Clinet = _ConvertLineToClientObject(Line);
                if(Clinet.AccountNumber() == AccountNumber && Clinet._PinCode == PinCode) {
                    MyFile.close();
                    return Clinet;
                }
                vClinet.push_back(Clinet);
            }
            MyFile.close();

        }
        return _GetEmptyClinetObject();
    }
    static bool IsClientExist(string AccountNumber) {
        clsBankClient Client = clsBankClient::Find(AccountNumber);
        return (!Client.IsEmpty());
    }
    enum enSaveResults {svFaildEmptyObject =0, svSucceeded = 1};
    enSaveResults Save() {
        switch (_Mode) {
            case enMode::EmptyMode: {
                return enSaveResults::svFaildEmptyObject;
                break;
            }
            case enMode::UpdateMode: {
                _Update();
                return enSaveResults::svSucceeded;
                break;
            }

        }
    }
};
