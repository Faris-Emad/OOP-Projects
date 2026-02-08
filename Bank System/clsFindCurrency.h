#pragma once
#include <iomanip>
#include <iostream>
#include "clsScreen.h"
#include "clsCurrency.h"
#include "clsInputValidate.h"
using namespace std;


class clsFindCurrency : protected clsScreen {
    private:
        static void _PrintCurrecny(clsCurrency Currency) {
            cout << "\n------------------------------------";
            cout << "\nCountry    : " << Currency.Country();
            cout << "\nCode       : " << Currency.CurrencyCode();
            cout << "\nName       : " << Currency.CurrencyName();
            cout << "\nRate       : " << Currency.Rate();
            cout << "\n------------------------------------\n";
        }
        static void _ShowResults(clsCurrency Currency) {
            if(!Currency.IsEmpty()) {
                cout << "\nCurrency Found ;)";
                _PrintCurrecny(Currency);
            }
            else {
                cout << "Currency was not found :(\n";
            }
        }
        static string FormatCurrencyCode(string CurrencyCode) {
            string Code = "";
            for(int i = 0; i <= CurrencyCode.size(); i++) {
                Code = toupper(CurrencyCode[i]);
            }
            return Code;
        }
        static void ChooseCurrencyByCode() {
            string CurrencyCode;
            cout << "\nPlease Enter Currnecy Code: ";
            CurrencyCode = clsInputValidate::ReadString();
            CurrencyCode = FormatCurrencyCode(CurrencyCode);
            // clsCurrency Currency = clsCurrency::FindByCode(CurrencyCode);
            // _ShowResults(Currency);
            cout << CurrencyCode;
        }
        static void ChooseCurrencyByCountry() {
            string Country;
            cout << "\nPlease Enter Country Name: ";
            Country = clsInputValidate::ReadString();
            clsCurrency Currency = clsCurrency::FindByCode(Country);
            _ShowResults(Currency);
        }

    public:
        static void ShowFindCurrencyScreen() {
            _DrawScreenHeader("Find Currency Screen");
            cout << "Find By: " << "[1] Code or [2] Country ?";
            short choose =  clsInputValidate::ReadShortNumber();
            if(choose == 1) {
                ChooseCurrencyByCode();
            }
            if(choose == 2) {
                ChooseCurrencyByCountry();
            }
        }
};

