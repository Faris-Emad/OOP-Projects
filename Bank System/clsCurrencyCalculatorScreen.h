#pragma once
#include <iomanip>
#include <iostream>
#include "clsScreen.h"
#include "clsCurrency.h"
#include "clsInputValidate.h"
#include "clsString.h"
using namespace std;



class clsCurrencyCalculatorScreen : protected clsScreen{
    private:
        static void _PrintCurrency(clsCurrency Currency) {
            cout << "\n------------------------------------";
            cout << "\nCountry    : " << Currency.Country();
            cout << "\nCode       : " << Currency.CurrencyCode();
            cout << "\nName       : " << Currency.CurrencyName();
            cout << "\nRate(1$)       : " << Currency.Rate();
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
        static string _ReadCurrencyCode(string message) {
            string CurrencyCode;
            cout << message;
            CurrencyCode = clsInputValidate::ReadString();
            CurrencyCode = _FormatCurrencyCode(CurrencyCode);
            while (!clsCurrency::IsCurrencyExist(CurrencyCode)) {
                cout << "\nCurrency is not found, choose another one: ";
                CurrencyCode = clsInputValidate::ReadString();
                CurrencyCode = _FormatCurrencyCode(CurrencyCode);
            }
            return CurrencyCode;
        }

    public:
        static void ShowCurrencyCalculatorScreen() {
            _DrawScreenHeader("Currency Calculator Screen");
            string SourceCurrencyCode = _ReadCurrencyCode("\nPlease Enter Source Currency Code: ");
            clsCurrency SourceCurrency = clsCurrency::FindByCode(SourceCurrencyCode);
            _PrintCurrency(SourceCurrency);

            string DestinationCurrencyCode = _ReadCurrencyCode("\nPlease Enter Destination Currency Code: ");
            clsCurrency DestinationCurrency = clsCurrency::FindByCode(DestinationCurrencyCode);
            _PrintCurrency(DestinationCurrency);

            float Amount;
            cout << "\nPlease Enter Amount to Exchange: ";
            Amount = clsInputValidate::ReadFloatNumber();

            float ConvertedAmount = SourceCurrency.ConvertToOtherCurrency(Amount, DestinationCurrency);

            cout << "\n======================================";
            cout << "\n  Convert Result:";
            cout << "\n======================================";
            cout << "\n  " << fixed << setprecision(2) << Amount << " " << SourceCurrency.CurrencyCode()
                 << " = " << ConvertedAmount << " " << DestinationCurrency.CurrencyCode();
            cout << "\n======================================\n";
            
        }
       
};


