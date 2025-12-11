#include <iostream>
#include "clsBankClient.h"
using namespace std;


int main() {
    clsBankClient Client1 = clsBankClient::Find("A107");
    Client1.PrintInfo();
    clsBankClient Client2 = clsBankClient::Find("A103", "12343");
    Client2.PrintInfo(); 
    cout<< endl << clsBankClient::IsClientExist("A101");
    return 0;
}