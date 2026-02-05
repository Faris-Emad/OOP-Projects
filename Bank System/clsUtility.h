#pragma once
/*
    randoumNumber(from, to)
    getRandomCharacter(type character)
    genreateWord(type character , number character )
    genrateKey(type character )
    genrateKeys(number character ,type character )
    swap (int 1, int 2)
    swap(double 1 , double 2)
    swap(string 1 , string 2)
    swap (date1,date2)
    shuffle array (int array, size array)
    shuffle array (string  array, size array)
    fillArrayWithRandoumNumbers(array,size,from,to)
    fillArrayWithRandoumWords(array,size,Type character ,number character)
    fillArrayWithRandoumKeys(array,number keys,type character )
    tabs (number tabs)
    encryption(text, encryption key) 
    decryption(text, decryption key)
*/

#pragma once
#include <iostream>
#include <string>
#include "clsDate.h"

using namespace std;

class clsUtility
{
   
public:
    enum enCharType {
        SamallLetter = 1, CapitalLetter = 2,
        Digit = 3, MixChars = 4, SpecialCharacter = 5
    };

    static void  Srand()
    {
        //Seeds the random number generator in C++, called only once
        srand((unsigned)time(NULL));
    }

    static  int RandomNumber(int From, int To)
    {
        //Function to generate a random number
        int randNum = rand() % (To - From + 1) + From;
        return randNum;
    }

    static string NumberToText(long long number) {
        if (number == 0) {
            return "zero";
        }

        // Handle negative numbers
        if (number < 0) {
            return "negative " + NumberToText(-number);
        }
        if (number >= 1 && number <= 19) {
            const string arr[] = {
                "", "one", "two", "three", "four", "five",
                "six", "seven", "eight", "nine", "ten",
                "eleven", "twelve", "thirteen", "fourteen", "fifteen",
                "sixteen", "seventeen", "eighteen", "nineteen"
            };
            return arr[number];
        }

        if (number >= 20 && number <= 99) {
            const string arr[] = {"","","twenty","thirty","forty","fifty","sixty","seventy","eighty","ninety"};
            string result = arr[number / 10];
            if (number % 10 != 0) {
                result += " " + NumberToText(number % 10);
            }
            return result;
        }

        if (number >= 100 && number <= 999) {
            string result = NumberToText(number / 100) + " hundred";
            if (number % 100 != 0) {
                result += " " + NumberToText(number % 100);
            }
            return result;
        }

        if (number >= 1000 && number <= 999999) {
            string result = NumberToText(number / 1000) + " thousand";
            if (number % 1000 != 0) {
                result += " " + NumberToText(number % 1000);
            }
            return result;
        }

        if (number >= 1000000 && number <= 999999999) {
            string result = NumberToText(number / 1000000) + " million";
            if (number % 1000000 != 0) {
                result += " " + NumberToText(number % 1000000);
            }
            return result;
        }

        if (number >= 1000000000 && number <= 999999999999LL) {
            string result = NumberToText(number / 1000000000) + " billion";
            if (number % 1000000000 != 0) {
                result += " " + NumberToText(number % 1000000000);
            }
            return result;
        }

        if (number >= 1000000000000LL && number <= 999999999999999LL) {
            string result = NumberToText(number / 1000000000000LL) + " trillion";
            if (number % 1000000000000LL != 0) {
                result += " " + NumberToText(number % 1000000000000LL);
            }
            return result;
        }

        if (number >= 1000000000000000LL && number <= 999999999999999999LL) {
            string result = NumberToText(number / 1000000000000000LL) + " quadrillion";
            if (number % 1000000000000000LL != 0) {
                result += " " + NumberToText(number % 1000000000000000LL);
            }
            return result;
        }

        // For numbers >= 1 quintillion (1000000000000000000LL)
        if (number >= 1000000000000000000LL) {
            string result = NumberToText(number / 1000000000000000000LL) + " quintillion";
            if (number % 1000000000000000000LL != 0) {
                result += " " + NumberToText(number % 1000000000000000000LL);
            }
            return result;
        }

        return "";
    }

    static char GetRandomCharacter(enCharType CharType)
    {

        //updated this method to accept mixchars
        if (CharType == MixChars)
        {
            //Capital/Samll/Digits only
            CharType = (enCharType)RandomNumber(1, 3);

        }

        switch (CharType)
        {

        case enCharType::SamallLetter:
        {
            return char(RandomNumber(97, 122));
            break;
        }
        case enCharType::CapitalLetter:
        {
            return char(RandomNumber(65, 90));
            break;
        }
        case enCharType::SpecialCharacter:
        {
            return char(RandomNumber(33, 47));
            break;
        }
        case enCharType::Digit:
        {
            return char(RandomNumber(48, 57));
            break;
        }
        defualt:
        {
            return char(RandomNumber(65, 90));
            break;
        }
        }
    }

    static  string GenerateWord(enCharType CharType, short Length)

    {
        string Word;

        for (int i = 1; i <= Length; i++)

        {

            Word = Word + GetRandomCharacter(CharType);

        }
        return Word;
    }

    static string  GenerateKey(enCharType CharType = CapitalLetter)
    {

        string Key = "";


        Key = GenerateWord(CharType, 4) + "-";
        Key = Key + GenerateWord(CharType, 4) + "-";
        Key = Key + GenerateWord(CharType, 4) + "-";
        Key = Key + GenerateWord(CharType, 4);


        return Key;
    }

    static void GenerateKeys(short NumberOfKeys, enCharType CharType)
    {

        for (int i = 1; i <= NumberOfKeys; i++)

        {
            cout << "Key [" << i << "] : ";
            cout << GenerateKey(CharType) << endl;
        }

    }

    static void FillArrayWithRandomNumbers(int arr[100], int arrLength, int From, int To)
    {
        for (int i = 0; i < arrLength; i++)
            arr[i] = RandomNumber(From, To);
    }

    static void FillArrayWithRandomWords(string arr[100], int arrLength, enCharType CharType, short Wordlength)
    {
        for (int i = 0; i < arrLength; i++)
            arr[i] = GenerateWord(CharType, Wordlength);

    }

    static void FillArrayWithRandomKeys(string arr[100], int arrLength, enCharType CharType)
    {
        for (int i = 0; i < arrLength; i++)
            arr[i] = GenerateKey(CharType);
    }

    static  void Swap(int& A, int& B)
    {
        int Temp;

        Temp = A;
        A = B;
        B = Temp;
    }

    static  void Swap(double& A, double& B)
    {
        double Temp;

        Temp = A;
        A = B;
        B = Temp;
    }

    static  void Swap(bool& A, bool& B)
    {
        bool Temp;

        Temp = A;
        A = B;
        B = Temp;
    }

    static  void Swap(char& A, char& B)
    {
        char Temp;

        Temp = A;
        A = B;
        B = Temp;
    }

    static  void Swap(string& A, string& B)
    {
        string Temp;

        Temp = A;
        A = B;
        B = Temp;
    }

    static  void Swap(clsDate& A, clsDate& B)
    {
        clsDate Temp = A;
        A = B;
        B = Temp;

    }

    static  void ShuffleArray(int arr[100], int arrLength)
    {

        for (int i = 0; i < arrLength; i++)
        {
            Swap(arr[RandomNumber(1, arrLength) - 1], arr[RandomNumber(1, arrLength) - 1]);
        }

    }

    static  void ShuffleArray(string arr[100], int arrLength)
    {

        for (int i = 0; i < arrLength; i++)
        {
            Swap(arr[RandomNumber(1, arrLength) - 1], arr[RandomNumber(1, arrLength) - 1]);
        }

    }

    static string  Tabs(short NumberOfTabs)
    {
        string t = "";

        for (int i = 1; i < NumberOfTabs; i++)
        {
            t = t + "\t";
            cout << t;
        }
        return t;

    }

    static string  EncryptText(string Text, short EncryptionKey = 16)
    {

        for (int i = 0; i <= Text.length(); i++)
        {

            Text[i] = char((int)Text[i] + EncryptionKey);

        }

        return Text;

    }

    static string  DecryptText(string Text, short EncryptionKey = 16)
    {

        for (int i = 0; i <= Text.length(); i++)
        {

            Text[i] = char((int)Text[i] - EncryptionKey);

        }
        return Text;

    }

    static bool GoBackOrExit(string messages = "\n\nPress [Enter] to go back to Main Menu: ") {
        cout << messages;
        string input;
        getline(cin, input);
        if (input == "x" || input == "X") {
            return false; // Exit program
        }
        return true; // Return to menu
    }

};

