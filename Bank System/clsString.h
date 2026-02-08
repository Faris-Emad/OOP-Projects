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
    public:

        clsString() {
            _Value = "";
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
            readFirstLetterOfEachWord(_Value);
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
        int CountLetter(char Letter, bool MatchCase = true) {
            return CountLetter(_Value, Letter, MatchCase);
        }
        static bool IsVowel(char C1) {
            C1 = tolower(C1);
            return (C1 == 'a' || C1 == 'e' || C1 == 'i' || C1 == 'o' || C1 == 'u');
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
                else if (CurrentWord != "") {
                    cout << CurrentWord << endl;
                    CurrentWord = "";
                }
            }
            if (CurrentWord != "") {
                cout << CurrentWord << endl;
            }
        }
        void PrintEachWord() {
            PrintEachWord(_Value);
        }
        // static string TrimLeft(string S1) {
        //     for (int i = 0; i <= S1.length() - 1; i++) {
        //         if (S1[i] != ' ') {
        //             return S1 = S1.substr(i, S1.length());
        //         }
        //     }
        //     return "";
        // }
        static string TrimLeft(string S1) {
            for (int i = 0; i < S1.length(); i++) {
                if (S1[i] != ' ') {
                    return S1.substr(i);
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
        //Error
        static string JoinString(string arrString[], int len, string delim) {
            string S1 = "";
            for (int i = 0; i < len; i++) {
                S1 += arrString[i] + delim;
            }

            return S1.substr(0,S1.length() - delim.length());
        }
        static bool isPunctuation(char c) {
            return (c >= 33 && c <= 47) ||
                (c >= 58 && c <= 64) ||
                (c >= 91 && c <= 96) ||
                (c >= 123 && c <= 126);
        }
        static string RemovePunctuations(string originalText) {
            string UpdatedString;
            for (char c : originalText) {

                if (!ispunct(c)) {
                    UpdatedString += c ;
                }
            }
            return UpdatedString;
        }

        // static string ToLowerCase(string S5) {
        //     for (int i = 0; i <= S5.length(); i++) {
        //         S5[i] = tolower(S5[i]);
        //     }
        //     return S5;
        //}
        static string ToLowerCase(string S5) {
            for (int i = 0; i < S5.length(); i++) {  // ✅
                if (S5[i] >= 'A' && S5[i] <= 'Z') {
                    S5[i] += 32;
                }
            }
            return S5;
        }
        static string ToUpperCase(string text) {
            for(int i = 0; i < text.length(); i++) {
                if(text[i] >= 'a' && text[i] <= 'z') {
                    text[i] = text[i] - 32;
                }
            }
            return text;
        }
        static string RemoveTrailingPunctuation(string S4) {
            if (S4.empty()) {
                return S4;
            }
            // إزالة من النهاية أولاً
            while (!S4.empty() && isPunctuation(S4.back())) {
                S4.pop_back();
            }
            // إزالة من البداية
            while (!S4.empty() && isPunctuation(S4.front())) {
                S4.erase(0,1);
            }
            return S4;
        }

        static string ReplaceWords(string S1, string S2, string S3) {
            vector <string> vString;
            vString = SplitString(S1 ," ");
            string UpdatedString = "";
            string cleanWord;
            for (int i = 0; i <= vString.size() - 1; i++) {
                if (vString[i].empty() || vString[i] == " ") {
                    continue;
                }
                string original = vString[i];
                cleanWord = RemoveTrailingPunctuation(vString[i]);
                if (cleanWord == S2) {
                    string frontPunct = "", backPunct = "";
                    if (isPunctuation(original.back())) {
                        backPunct = original.back();
                    }
                    if (isPunctuation(original.front())) {
                        frontPunct = original.front();
                    }
                    vString[i] = frontPunct + S3 + backPunct;
                }
            }
            for (string &s : vString) {
                UpdatedString += s + " ";
            }
            UpdatedString = UpdatedString.substr(0, UpdatedString.length() - 1); // remove last space
            return UpdatedString;
        }
        static string ReplaceIgnoreCase(string originalText, string wordToReplace, string replacementWord) {
            vector <string> vString;
            vString = SplitString(originalText ," ");
            string UpdatedString = "";
            string cleanWord;
            for (int i = 0; i <= vString.size() - 1; i++) {
                if (vString[i].empty() || vString[i] == " ") {
                    continue;
                }
                string original = vString[i];
                cleanWord = RemoveTrailingPunctuation(vString[i]);
                if (ToLowerCase(cleanWord) == ToLowerCase(wordToReplace)) {
                    string frontPunct = "", backPunct = "";
                    if (isPunctuation(original.back())) {
                        backPunct = original.back();
                    }
                    if (isPunctuation(original.front())) {
                        frontPunct = original.front();
                    }
                    vString[i] = frontPunct + replacementWord + backPunct;
                }
            }
            for (string &s : vString) {
                UpdatedString += s + " ";
            }
            UpdatedString = UpdatedString.substr(0, UpdatedString.length() - 1); // remove last space
            return UpdatedString;
        }



};


