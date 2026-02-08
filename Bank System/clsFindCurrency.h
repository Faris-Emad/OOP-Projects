#pragma once
#include <iomanip>
#include <iostream>
#include "clsScreen.h"
#include "clsCurrency.h"
#include "clsInputValidate.h"
#include "clsString.h"
#include <string>
#include <cctype>
using namespace std;


class clsFindCurrency : protected clsScreen {
    private:
        enum enFindBy { ByCode = 1, ByCountry = 2 };
        static void _PrintCurrency(clsCurrency Currency) {
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
                _PrintCurrency(Currency);
            }
            else {
                cout << "Currency was not found :(\n";
            }
        }
        static string FormatCurrencyCode(string CurrencyCode) {
            return clsString::ToUpperCase(CurrencyCode);
        }
        static string FormatCountryName(string Country) {
            Country = clsString::ToLowerCase(Country);
            if(Country.length() > 0 && Country[0] >= 'a' && Country[0] <= 'z') {
                Country[0] = Country[0] - 32;
            }
            return Country;
        }

        static void _ChooseCurrencyByCode() {
            string CurrencyCode;
            cout << "\nPlease Enter Currency Code: ";
            CurrencyCode = clsInputValidate::ReadString();
            clsCurrency Currency = clsCurrency::FindByCode(FormatCurrencyCode(CurrencyCode));
            _ShowResults(Currency);
        }
        static void _ChooseCurrencyByCountry() {
            string Country;
            cout << "\nPlease Enter Country Name: ";
            Country = clsInputValidate::ReadLine();
            Country = FormatCountryName(Country);
            cout << "Country Name after " << Country << endl;
            clsCurrency Currency = clsCurrency::FindByCountry(Country);
            _ShowResults(Currency);
        }

    public:
        static void ShowFindCurrencyScreen() {
            
            _DrawScreenHeader("Find Currency Screen");
            cout << "Find By: " << "[1] Code or [2] Country ?";
            short choose =  clsInputValidate::ReadShortNumber();
            if(choose == enFindBy::ByCode) {
                _ChooseCurrencyByCode();
            }
            else if(choose == enFindBy::ByCountry) {
                _ChooseCurrencyByCountry();
            }
            else {
                cout << "Invalid Choice!!!" << endl;
            }
        }
};

