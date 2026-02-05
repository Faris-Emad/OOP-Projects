#include <iostream>
using namespace std;


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

int main() {

    string Text = "1111";
     cout << EncryptText(Text);


    return 0;
}
