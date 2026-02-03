#pragma once
#include <iomanip>
#include <iostream>
#include "clsScreen.h"
#include "clsBankClient.h"

class clsTransfersLogScreen : protected clsScreen {

    
private:
    static void _PrintTransferLogRecordLine(clsBankClient::stTransferLog TransferLog) {
        cout << setw(8) << left << "" << "| " << setw(23) << left << TransferLog.DateTime;
        cout << "| " << setw(8) << left << TransferLog.SourceAccount;
        cout << "| " << setw(8) << left << TransferLog.DestinationAccount;
        cout << "| " << setw(8) << left << TransferLog.Amount;
        cout << "| " << setw(10) << left << TransferLog.SourceBalanceAfter;
        cout << "| " << setw(10) << left << TransferLog.DestBalanceAfter;
        cout << "| " << setw(8) << left << TransferLog.Username;
    }

public:
    static void ShowTransferLogList() {
        vector<clsBankClient::stTransferLog> vTransferLog = 
            clsBankClient::GetTransferLoginList();

        string Title = "\t  Transfer Log List Screen";
        string SubTitle = "\t    (" + to_string(vTransferLog.size()) + ") Record(s).";

        _DrawScreenHeader(Title, SubTitle);

        cout << setw(8) << left << "" << "\n\t_______________________________________________________";
        cout << "______________________________________________\n" << endl;

        cout << setw(8) << left << "" << "| " << left << setw(23) << "Date/Time";
        cout << "| " << left << setw(8) << "s.Acct";
        cout << "| " << left << setw(8) << "d.Acct";
        cout << "| " << left << setw(8) << "Amount";
        cout << "| " << left << setw(10) << "s.Balance";
        cout << "| " << left << setw(10) << "d.Balance";
        cout << "| " << left << setw(8) << "User";
        
        cout << setw(8) << left << "" << "\n\t_______________________________________________________";
        cout << "______________________________________________\n" << endl;

        if (vTransferLog.size() == 0) {
            cout << "\t\t\t\tNo Transfers Available In the System!";
        }
        else {
            for (clsBankClient::stTransferLog& Record : vTransferLog) {
                _PrintTransferLogRecordLine(Record);
                cout << endl;
            }
        }

        cout << setw(8) << left << "" << "\n\t_______________________________________________________";
        cout << "______________________________________________\n" << endl;
    }
};