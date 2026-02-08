#pragma once
#include <iostream>
#include <fstream>
#include <string>
#include <vector>
#include "clsString.h"
using namespace std;



class clsCurrency {
    private:
        inline  static const string CurrncyFile = "exchange_rates_updated_feb2026.txt";
        inline  static const string SEPARATOR = "#//#";
        enum enMode { EmptyMode = 0, UpdateMode = 1};
        enMode _Mode;
        string _Country;
        string _CurrencyCode;
        string _CurrencyName;
        float  _Rate;
        static clsCurrency _ConvertLineToCurrencyObject(string line) {
            vector <string> vCurrencyData = clsString::SplitString(line, SEPARATOR);
            return clsCurrency(enMode::UpdateMode, vCurrencyData[0], vCurrencyData[1], vCurrencyData[2], stof(vCurrencyData[3]));
        }
        static string _ConverCurrncyObjectToLine(clsCurrency Currency) {
            string DataLine = "";
            DataLine += Currency._Country + SEPARATOR;
            DataLine += Currency._CurrencyCode + SEPARATOR;
            DataLine += Currency._CurrencyName + SEPARATOR;
            DataLine += to_string(Currency._Rate);
            return DataLine;
        }
        static vector<clsCurrency> _LoadCurrencyDataFromFile() {
            vector<clsCurrency> _vCurrency;
            fstream MyFile;
            MyFile.open(CurrncyFile, ios::in);
            if(MyFile.is_open()) {
                string Line;
                while (getline(MyFile, Line)) {

                    clsCurrency Currency = _ConvertLineToCurrencyObject(Line);
                    _vCurrency.push_back(Currency);
                }
                MyFile.close();

            }
            return _vCurrency;
        }
        static void _SaveCurrencyDataToFile(vector<clsCurrency> _vCurrency) {
            fstream MyFile;
            MyFile.open(CurrncyFile, ios::out); // Open file for writing (overwrites existing)
            string DataLine;
            if(MyFile.is_open()) {
                for(clsCurrency& C : _vCurrency) {  
                    DataLine = _ConverCurrncyObjectToLine(C);
                    MyFile << DataLine << endl;
                }
                MyFile.close();
            }
        }
        static clsCurrency _GetEmptyCurrencyObject(){
            return clsCurrency(enMode::EmptyMode, "", "", "",0);
        }
        void _Update() {
            vector<clsCurrency> _vCurrency;
            _vCurrency = _LoadCurrencyDataFromFile();
            for(clsCurrency& C : _vCurrency) {
                if(C.CurrencyCode() == CurrencyCode()){
                    C = *this;
                    break;
                }
            }
            _SaveCurrencyDataToFile(_vCurrency);
        }
    public:
        clsCurrency(enMode Mode, string Country, string CurrencyCode, 
                       string CurrencyName, float Rate) {
            _Mode = Mode;
            _Country = Country;
            _CurrencyCode = CurrencyCode;
            _CurrencyName = CurrencyName;
            _Rate = Rate;
        }
        bool IsEmpty() {
            return (_Mode == enMode::EmptyMode);
        }
        string Country(){
            return _Country;
        }
        string CurrencyCode() {
            return _CurrencyCode;
        }
        string CurrencyName() {
            return _CurrencyName;
        }
        float Rate() {
            return _Rate;
        }
        void UpdateRate(float NewRate) {
            _Rate = NewRate;
            _Update();
        }
        static clsCurrency FindByCode(string CurrencyCode) {
            fstream MyFile;
            MyFile.open(CurrncyFile, ios::in);
            if(MyFile.is_open()) {
                string Line;
                while (getline(MyFile, Line)) {
                    clsCurrency Currency = _ConvertLineToCurrencyObject(Line);
                    if(Currency.CurrencyCode() == CurrencyCode) {
                        MyFile.close();
                        return Currency;
                    }
                }
                
            }
            return _GetEmptyCurrencyObject();
        }
        static clsCurrency FindByCountry(string CurrencyName) {
            fstream MyFile;
            MyFile.open(CurrncyFile, ios::in);
            if(MyFile.is_open()) {
                string Line;
                while (getline(MyFile, Line)) {
                    clsCurrency Currency = _ConvertLineToCurrencyObject(Line);
                    if(Currency.Country()== CurrencyName) {
                        MyFile.close();
                        return Currency;
                    }
                }
                
            }
            return _GetEmptyCurrencyObject();
        }
       

        static bool IsCurrencyExist(string CurrencyCode) {
            clsCurrency Currency = clsCurrency::FindByCode(CurrencyCode);
            return(!Currency.IsEmpty());
        }
        static vector <clsCurrency> GetCurrencyList() {
            return _LoadCurrencyDataFromFile();
        }

        float ConvertToUSD(float Amount) {
            float AmountInUSD = Amount / _Rate;
            return AmountInUSD;
        }

        
        float ConvertToOtherCurrency(float Amount, clsCurrency OtherCurrency) {
            float AmountInUSD = ConvertToUSD(Amount);
            if(OtherCurrency.CurrencyCode() == "USD") {
                return AmountInUSD;
            }
            return (AmountInUSD) * OtherCurrency.Rate();
        }

};


