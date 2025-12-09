#pragma once
#include <iostream>
#include <string>
#include "clsDate.h"

class clsInputValidation {
    private:

    public:
        static bool IsNumberBetween(int number, int from, int to) {
            return number >= from && number <= to;
        }
        static bool IsNumberBetween(float number, float from, float to) {
            return number >= from && number <= to;
        }
        static bool IsDateBetween(clsDate Date, clsDate form, clsDate to)  {
            return clsDate::IsDate1AfterDate2(Date, form) && clsDate::IsDate1BeforeDate2(Date, to);
        }

};

