#include <iostream>
#include "clsString.h";

int main() {
    
    clsString MyString1;
    clsString MyString2("Faris Emad Elden");

   

    cout << MyString2.GetValue()<< endl;
    cout << "count words: " << MyString2.CountEachWord();
    cout << "count letter:  " << 
    return 0;
}