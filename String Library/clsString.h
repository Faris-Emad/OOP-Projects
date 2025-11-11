#pragma once
#include <iostream>
#include <string>
#include <cctype>
#include <limits>
#include <vector>
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
        static int CountLetter(string S1, char C1, bool MatchCase = true) {
            int count = 0;
            for (int i = 0; i < S1.length(); i++) {
                if (MatchCase) {
                    if (isalpha(S1[i]) && ((C1 == S1[i]))) {
                        count++;
                    }
                }
                else {
                    if (isalpha(S1[i]) && ((tolower(C1) == tolower(S1[i])))) {
                        count++;
                    }
                }
            }
            return count;
        }
        int CountLetter(bool MatchCase = true) {
            return CountLetter(_Value, _Letter, MatchCase);
        }
        int CountLetter(char Letter, bool MatchCase = true) {
            return CountLetter(_Value, Letter, MatchCase);
        }
        static bool IsVowel(char C1) {
            C1 = tolower(C1);
            return (C1 == 'a' || C1 == 'e' || C1 == 'i' || C1 == 'o' || C1 == 'u');
        }
        bool IsVowel() {
            return IsVowel(_Letter);
        }
        static int CountVowel(string s1) {
            int vowel = 0;
            for (int i = 0; i < s1.length(); i++) {
                    if (IsVowel(s1[i])) {
                        vowel++;
                    }
            }
            return vowel;
        }
        int CountVowel() {
            return CountVowel(_Value);
        }
        static void PrintEachWord(string S1) {
            string CurrentWord = "";
            for (int i = 0; i < S1.length(); i++) {
                    if (S1[i] != ' ') {
                        CurrentWord += S1[i];
                    }
                    else {
                        cout << endl;
                        CurrentWord = "";
                    }

            }
            if (CurrentWord != "") {
                    cout << CurrentWord;
                    cout << endl;
            }
        }
        void PrintEachWord() {
            return PrintEachWord(_Value);
        }
        static string TrimLeft(string S1) {
            for (int i = 0; i <= S1.length() - 1; i++) {
                if (S1[i] != ' ') {
                    return S1 = S1.substr(i, S1.length() - 1);
                }
            }
            return "";
        }
        string TrimLeft() {
            return TrimLeft(_Value);
        }
        static string TrimRight(string S1) {
            for (int i = S1.length() - 1  ; i >= 0 ; i--) {
                if (S1[i] != ' ') {
                    return S1 = S1.substr(0, i + 1);
                }
            }
            return "";
        }
        string TrimRight() {
            return TrimRight(_Value);
        }
        static string Trim(string S1) {
            return TrimLeft(TrimRight(S1));
        }
        string Trim() {
            return Trim(_Value);
        }
        static vector<string> SplitString(string S1, string delim) {
            vector <string> vString;
            short pos = 0;
            string sWord;
            while((pos = S1.find(delim)) != std::string::npos) {
                sWord = S1.substr(0, pos);
                if(sWord != "") {
                    vString.push_back(sWord);
                }
                S1.erase(0,pos + delim.length());
            }
            if (S1 != "") {
                vString.push_back(S1);
            }
            return vString;
        }
        vector<string> SplitString(string delim) {
            return SplitString( _Value ,delim);
        }

        static string ReverseString(string S1){
            vector<string> vString;
            string S2 = "";
            vString = SplitString(S1, " ");
            vector<string>::iterator iter =vString.end();
            while (iter != vString.begin()) {
                --iter;
                S2 += *iter + " ";
            }
            S2 = S2.substr(0, S2.length() - 1); // remove last space
            return S2;
        }
        string ReverseString() {
            return ReverseString(_Value);
        }
        static string JoinString(vector<string> vString, string delim) {
            string S1 = "";
            for (string& s : vString) {
                S1 = S1 + s + delim;
            }

            return S1.substr(0,S1.length() - delim.length());
        }

        static string JoinString(string arrString[], int len, string delim) {
            string S1 = "";
            for (int i = 0; i <= len; i++) {
                S1 += arrString[i] + delim;
            }

            return S1.substr(0,S1.length() - delim.length());
        }

};


