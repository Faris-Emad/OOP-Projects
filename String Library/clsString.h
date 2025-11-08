#pragma once
#include <iostream>
using namespace std;

class clsString {
    private:
        string _Value;
        char _Letter;
    public:

        clsString() {
            _Value = "";
            _Letter = ' ';
        }
        clsString(string Value) {
            _Value = Value;
        }
        void SetValue(string Value) {
            _Value = Value;
        }
        string GetValue() {
            return _Value;
        }
        void SetLetter(char Letter) {
            _Letter = Letter;
        }
        char GetLetter() {
            return _Letter;
        }
        
        static int CountEachWord(string S1) {
            int word = 0;
            string delim = " ";
            short pos = 0;
            string sWord;
            while((pos = S1.find(delim)) != std::string::npos) {
                sWord = S1.substr(0, pos);
                if(sWord != "") {
                    word = word + 1;
                }
                S1.erase(0,pos + delim.length());
            }
            if (S1 != "") {
                word = word + 1;
            }
            return word;
        }
        int CountEachWord() {
            return CountEachWord(_Value);
        }
        static void readFirstLetterOfEachWord(string S1) {
            bool IsFirstLetter = true;
            cout << "First Letter for this string: ";

            for (int i = 0; i < S1.length(); i++) {
                if (S1[i] != ' ' && IsFirstLetter) {
                    cout << S1[i] << " ";
                }
                IsFirstLetter = (S1[i] == ' '? true:false);
            }
        }
        void readFirstLetterOfEachWord() {
            return readFirstLetterOfEachWord(_Value);
        }
        static string UppercaseFirstLetterOfEachWord(string S1) {
            bool IsFirstLetter = true;
            for (int i = 0; i < S1.length(); i++) {
                if (S1[i] != ' ' && IsFirstLetter) {
                    S1[i] = toupper(S1[i]);
                }
                IsFirstLetter = (S1[i] == ' '? true:false);
            }
            return S1;
        }
        string UppercaseFirstLetterOfEachWord() {
            return UppercaseFirstLetterOfEachWord(_Value);
        }
        static string LowercaseFirstLetterOfEachWord(string S1) {
            bool IsFirstLetter = true;
            for (int i = 0; i < S1.length(); i++) {
                if (S1[i] != ' ' && IsFirstLetter) {
                    S1[i] = tolower(S1[i]);
                }
                IsFirstLetter = (S1[i] == ' '? true:false);
            }
            return S1;
        }
        string LowercaseFirstLetterOfEachWord() {
            return LowercaseFirstLetterOfEachWord(_Value);
        }
        static string InvertLetterCase(string S1) {
            for (int i =0; i < S1.length(); i++) {
                if (isalpha(S1[i])) {
                    S1[i] = (isupper(S1[i])) ? tolower(S1[i]) : toupper(S1[i]);
                }
            }
            return S1;
        }
        string InvertLetterCase() {
            return InvertLetterCase(_Value);
        }
        static int CountCapitalLetters(string S1) {
            int count = 0;
            for (int i = 0; i < S1.length(); i++) {
                if (isalpha(S1[i])) {
                    if (isupper(S1[i])) {
                        count++;
                    }
                }
            }
            return count;
        }
        int CountCapitalLetters() {
            return CountCapitalLetters(_Value);
        }
        static int CountLowerLetters(string S1) {
            int count = 0;
            for (int i = 0; i < S1.length(); i++) {
                if (isalpha(S1[i])) {
                    if (islower(S1[i])) {
                        count++;
                    }
                }
            }
            return count;
        }
        int CountLowerLetters() {
            return CountLowerLetters(_Value);
        }
        static int CountLetter(string S1, char C1) {
            int count = 0;
            for (int i = 0; i < S1.length(); i++) {
                if (isalpha(S1[i]) && (C1 == S1[i])) {
                    count++;
                }
            }
            return count;
        }
        int CountLetter() {
            return CountLetter(_Value, _Letter);
        }
        
};


