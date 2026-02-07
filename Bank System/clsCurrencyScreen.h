#pragma once
#include <iostream>
#include "clsScreen.h"
#include <iomanip>
#include "clsCurrency.h"
using namespace std;


class clsCurrencyScreen : protected clsScreen  {
    private:
        enum enCurrencyMenuOptions {
            eListCurrencies = 1, eFindCurrency = 2, eUpdateRate = 3,
            eCurrencyCalculator = 4, eMainMenu= 5
        };
        static short _ReadCurrencyMenuOption() {
            cout <<setw(37) << left << ""<< "Choose what do you want to do? [1 to 5]? ";
            short Choice = clsInputValidate::ReadIntNumberBetween(1,5,"Enter Number between 1 to 5? ");
            return Choice;
        }
        static  void _GoBackToCurrencyMenu() {
            cout << setw(37) << left << ""<<"\n\tPress any key to go back to Currency Menu...\n";
            system("pause>0");
            ShowCurrencyScreen();
        }
        static void _ShowCurrencyListScreen() {
            cout  << "soon" << endl;
        }
        static void _ShowFindCurrencyScreen() {
            cout  << "soon" << endl;
        }
        static void _ShowUpdateRateScreen() {
            cout  << "soon" << endl;
        }
        static void _ShowCurrencyCalcScreen() {
            cout  << "soon" << endl;
        }
        static  void _PerfromCurrencyMenuOption(enCurrencyMenuOptions enCurrencyMenuOptions) {
            switch(enCurrencyMenuOptions) {
                case enCurrencyMenuOptions::eListCurrencies: {
                    system("cls");
                    _ShowCurrencyListScreen();
                    _GoBackToCurrencyMenu();
                    break;
                }
                case enCurrencyMenuOptions::eFindCurrency: {
                    system("cls");
                    _ShowFindCurrencyScreen();
                    _GoBackToCurrencyMenu();
                    break;
                }
                case enCurrencyMenuOptions::eUpdateRate: {
                    system("cls");
                    _ShowUpdateRateScreen();
                    _GoBackToCurrencyMenu();
                    break;
                }
                case enCurrencyMenuOptions::eCurrencyCalculator: {
                    system("cls");
                    _ShowCurrencyCalcScreen();
                    _GoBackToCurrencyMenu();
                    break;
                }
                case enCurrencyMenuOptions::eMainMenu: {
                    
                }
            }
        }

        
    public:
        static void ShowCurrencyScreen() {
            if(!CheckAccessRights(clsUser::UserAccess::Currency))
                return;
            system("cls");
            _DrawScreenHeader("Currency Screen");
            cout << setw(37) << left <<""<< "===========================================\n";
            cout << setw(37) << left << "" << "\t\t\tManage Currencies Menu\n";
            cout << setw(37) << left << "" << "===========================================\n";
            cout << setw(37) << left << "" << "\t[1] List Currencies.\n";
            cout << setw(37) << left << "" << "\t[2] Find Currency.\n";
            cout << setw(37) << left << "" << "\t[3] Update Rate.\n";
            cout << setw(37) << left << "" << "\t[4] Currency Calculator.\n";
            cout << setw(37) << left << "" << "\t[5] Main Menu.\n";
            cout << setw(37) << left << "" << "===========================================\n";
            _PerfromCurrencyMenuOption((enCurrencyMenuOptions)_ReadCurrencyMenuOption());
            
        }
        
};
