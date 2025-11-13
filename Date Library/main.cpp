#include <iostream>
#include "clsDate.h"
using namespace std;



int main() {
    clsDate Date1;
    Date1.Print();
    clsDate Date2(19, 12, 2006);
    Date2.Print();
    Date2.PrintMonthCalender();
    cout << "========================\n";
    clsDate Date3("18/1/2007");

    Date3.Print();
    Date3.IncreaseDateByOneDay();
    Date3.IncreaseDateByOneDay();
    Date3.Print();
    Date3.IncreaseDateByOneWeek();
    Date3.Print();
    Date3.IncreaseDateByXWeeks();
    Date3.Print();
    //فضل بس 
    //clsDate Date2(273, 2007);
    return 0;
}