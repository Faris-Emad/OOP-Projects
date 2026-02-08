#pragma once
#include <iomanip>
#include <iostream>
#include "clsScreen.h"
#include "clsCurrency.h"
#include "clsInputValidate.h"
#include "clsString.h"
using namespace std;


class clsUpdateCurrencyRate : protected clsScreen  {
    private:
        static void _PrintCurrency(clsCurrency Currency) {
            cout << "\n------------------------------------";
            cout << "\nCountry    : " << Currency.Country();
            cout << "\nCode       : " << Currency.CurrencyCode();
            cout << "\nName       : " << Currency.CurrencyName();
            cout << "\nRate(1$)   : " << Currency.Rate();
            cout << "\n------------------------------------\n";
        }
        static void _ShowResults(clsCurrency Currency) {
            if(!Currency.IsEmpty()) {
                cout << "\nCurrency Found ;)";
                _PrintCurrency(Currency);
            }
            else {
                cout << "Currency was not found :(\n";
            }
        }
        static string _FormatCurrencyCode(string CurrencyCode) {
            return clsString::ToUpperCase(CurrencyCode);
        }
        static float _ReadNewRate() {
            cout << "\nUpdate Currency Rate:\n";
            cout << "_____________________\n";
            cout << "Enter New Rate: ";
            float NewRate = clsInputValidate::ReadFloatNumber();
            while(NewRate <= 0) {
                cout << "Invalid rate! Rate must be positive.\n";
                cout << "Enter New Rate: ";
                NewRate = clsInputValidate::ReadFloatNumber();
            }
            return NewRate;
        }
    public:
        static void ShowUpdateCurrencyRate() {
            _DrawScreenHeader("Update Currency Rate Screen");
            string CurrencyCode;
            cout << "\nPlease Enter Currency Code: ";
            CurrencyCode = clsInputValidate::ReadString();
            CurrencyCode = _FormatCurrencyCode(CurrencyCode);
            while (!clsCurrency::IsCurrencyExist(CurrencyCode)) {
                cout << "\nCurrency is not found, choose another one: ";
                CurrencyCode = clsInputValidate::ReadString();
                CurrencyCode = _FormatCurrencyCode(CurrencyCode);
            }
            clsCurrency Currency = clsCurrency::FindByCode(CurrencyCode);
            _ShowResults(Currency);
            if(Currency.IsEmpty())
                return;
            char Answer = clsInputValidate::AskYesNo("\nAre you sure you want to update the rate of this Currency?");
            if(Answer == 'y' || Answer == 'Y') {
                float NewRate =  _ReadNewRate();
                Currency.UpdateRate(NewRate);
                cout << "\nCurrency rate updated successfully!\n"; 
                _ShowResults(Currency);
            }
            else {
                cout << "Update Cancelled.\n";
            }
        }
        

};

