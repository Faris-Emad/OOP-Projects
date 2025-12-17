#pragma once
#include <iostream>
#include <limits>
#include <string>
#include "clsDate.h"

class clsInputValidate {
    public:
        static bool IsNumberBetween(int number, int from, int to) {
            return number >= from && number <= to;
        }
        static bool IsNumberBetween(float number, float from, float to) {
            return number >= from && number <= to;
        }
        static bool IsDateBetween(clsDate Date, clsDate from, clsDate to) {
            if( !Date.IsValidDate() ||
                !from.IsValidDate() || 
                !to.IsValidDate()) {
                return false;
            }
            clsDate::enDateCompare cmpFrom = clsDate::CompareDates(Date.Date, from.Date);
            clsDate::enDateCompare cmpTo = clsDate::CompareDates(Date.Date, to.Date);
            return ((cmpFrom != clsDate::enDateCompare::Before && 
                    cmpTo != clsDate::enDateCompare::After) ||
                    (cmpTo != clsDate::enDateCompare::Before && 
                    cmpFrom != clsDate::enDateCompare::After));
        }
        static int ReadIntNumber(string messageError) {
            int UserNumber = 0;
            while (true) {
                cin >> UserNumber;
                if (cin.fail()) {
                    cin.clear();
                    cin.ignore(numeric_limits<streamsize>::max(), '\n');
                    cout << messageError;
                    continue;
                }
                if (UserNumber < 0) {
                    cout << "Invalid input! Please enter a positive number.\n";
                    cin.ignore(numeric_limits<streamsize>::max(), '\n');
                    continue;
                }

                cin.ignore(numeric_limits<streamsize>::max(), '\n');
                return UserNumber;
            }
        }
        static double ReadDblNumber(string messageError) {
            double UserNumber = 0;
            while (true) {
                cin >> UserNumber;
                if (cin.fail()) {
                    cin.clear();
                    cin.ignore(numeric_limits<streamsize>::max(), '\n');
                    cout << messageError;
                    continue;
                }
                if (UserNumber < 0) {
                    cout << "Invalid input! Please enter a positive number.\n";
                    cin.ignore(numeric_limits<streamsize>::max(), '\n');
                    continue;
                }

                cin.ignore(numeric_limits<streamsize>::max(), '\n');
                return UserNumber;
            }
        }
        static string ReadString(string message) {
            string UserString = "";
            while(true){
                cout << message; 
                cin >> UserString;
                if (cin.fail()) {
                    cin.clear();
                    cin.ignore(numeric_limits<streamsize>::max(), '\n');
                    cout << "Invalid String, Enter again:\n";
                    continue;
                }
                cin.ignore(numeric_limits<streamsize>::max(), '\n');
                return UserString;
            }
        }
        static string ReadString() {
            string UserString = "";
            while(true){
                cin >> UserString;
                if (cin.fail()) {
                    cin.clear();
                    cin.ignore(numeric_limits<streamsize>::max(), '\n');
                    cout << "Invalid String, Enter again:\n";
                    continue;
                }
                cin.ignore(numeric_limits<streamsize>::max(), '\n');
                return UserString;
            }
        }
        static int ReadIntNumberBetween(int from , int to, string messageError) {
             int UserNumber = 0;
            while (true) {
                cin >> UserNumber;
                if (cin.fail()) {
                    cin.clear();
                    cin.ignore(numeric_limits<streamsize>::max(), '\n');
                    cout << "Invalid Number, Enter again:\n";
                    continue;
                }
                if (UserNumber < from || UserNumber > to) {
                    cout << messageError;
                    cin.ignore(numeric_limits<streamsize>::max(), '\n');
                    continue;
                }

                cin.ignore(numeric_limits<streamsize>::max(), '\n');
                return UserNumber;
            }
            return UserNumber;
        }
        static int ReadDblNumberBetween(int from , int to, string messageError) {
            double UserNumber = 0;
            while (true) {
                cin >> UserNumber;
                if (cin.fail()) {
                    cin.clear();
                    cin.ignore(numeric_limits<streamsize>::max(), '\n');
                    cout << "Invalid Number, Enter again:\n";
                    continue;
                }
                if (UserNumber < from || UserNumber > to) {
                    cout << messageError;
                    cin.ignore(numeric_limits<streamsize>::max(), '\n');
                    continue;
                }

                cin.ignore(numeric_limits<streamsize>::max(), '\n');
                return UserNumber;
            }
            return UserNumber;
        }
        static bool IsValideDate(clsDate Date)
        {
            return	Date.IsValidDate();
        }

};
