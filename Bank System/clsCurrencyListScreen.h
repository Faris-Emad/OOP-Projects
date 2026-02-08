#pragma once
#include <iomanip>
#include <iostream>
#include "clsScreen.h"
#include "clsCurrency.h"
using namespace std;


class clsCurrencyListScreen : protected clsScreen {
    private:
        /* data */
    public:
        static void ShowCurrencyListScreen() {
            vector<clsCurrency>  vCurrency = clsCurrency::GetCurrencyList();
            string Title = "\tCurrency List Screen";
            string SubTitle = "\t    (" + to_string(vCurrency.size()) + ") Record(s).";
            _DrawScreenHeader(Title, SubTitle);
            cout << setw(8) << left << "" << "\n\t_______________________________________________________";
                        cout << "_________________________________________\n" << endl;
                        cout << setw(8) << left << "" << "| " << left << setw(30) << "Country";
                        cout << "| " << left << setw(8) << "Code";
                        cout << "| " << left << setw(45) << "Name";
                        cout << "| " << left << setw(10) << "Rate/(1$)";
                        cout << setw(8) << left << "" << "\n\t_______________________________________________________";
                        cout << "_________________________________________\n" << endl;

                        if (vCurrency.size() == 0)
                            cout << "\t\t\t\tNo Currencies Available In the System!";
                        else {
                            for (clsCurrency& C : vCurrency) {
                                cout << setw(8) << left << "" << "| " << setw(30) << left << C.Country();
                                cout << "| " << setw(8) << left << C.CurrencyCode();
                                cout << "| " << setw(45) << left << C.CurrencyName();
                                cout << "| " << setw(10) << left << C.Rate();
                                cout << endl;
                            }
                        }
                        cout << setw(8) << left << "" << "\n\t_______________________________________________________";
                        cout << "_________________________________________\n" << endl;
        }

};
