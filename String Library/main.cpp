#include <iostream>
#include "clsString.h"

int main() {
    
    clsString MyString1;
    clsString MyString2("Faris Emad Elden e");
    MyString2.SetLetter('F');

    cout << MyString2.CountLetter() << endl;
    cout << MyString2.CountLetter('E', false) << endl;
    MyString1.SetLetter('a');
    ;
    if (MyString1.IsVowel()) {
        cout << "YES Letter '" << MyString1.GetLetter() << "' is vowel";
    }
    else {
        cout << "NO Letter '" << MyString1.GetLetter()  << "' is not vowel";
    }
    MyString1.SetValue("   Faris Emad-eldin   ");
    cout << endl;
    cout << MyString1.GetValue();
    //MyString1.PrintEachWord(); i need to cheack angin is this function is work or no ??
    cout << endl;
    // MyString1.PrintEachWord();
    cout << "trim left  = " << MyString1.TrimLeft() << endl;
    cout << "trim right = " << MyString1.TrimRight() << endl;
    cout << "trim       ="  << MyString1.Trim() << endl;
    cout << "=============================\n";
    
    vector<string> vString;

    vString = MyString1.SplitString(" ");

    cout << "\nTokens = " << vString.size() << endl;

    for (string& s : vString)
    {
        cout << s << endl;
    }
    cout << "=============================\n";
    //Joins
    vector<string> vString1 = { "Mohammed","Faid","Ali","Maher" };
    
    cout << "\n\nJoin String From Vector: \n";
    cout << clsString::JoinString(vString1, " ");


    string arrString[] = { "Mohammed","Faid","Ali","Maher" };

    cout << "\n\nJoin String From array: \n";
    cout << clsString::JoinString(arrString, 4, " ");
    return 0;
}