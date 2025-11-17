#pragma once
#include "clsDate.h"

class clsPeriod
{
public:

    clsDate StartDate;
    clsDate EndDate;

    clsPeriod(clsDate StartDate, clsDate DateTo)
    {
        this->StartDate = StartDate;
        this->EndDate = DateTo;

    }

    static bool IsOverlapPeriods(clsPeriod Period1, clsPeriod Period2)
    {

        if (
            clsDate::CompareDates(Period2.EndDate.Date, Period1.StartDate.Date) == clsDate::enDateCompare::Before
            ||
            clsDate::CompareDates(Period2.StartDate.Date, Period1.EndDate.Date) == clsDate::enDateCompare::After
            )
            return false;
        else
            return true;

    }


    bool IsOverLapWith(clsPeriod Period2)
    {
        return IsOverlapPeriods(*this, Period2);
    }

    void Print()
    {
        cout << "Period Start: ";
        StartDate.Print();


        cout << "Period End: ";
        EndDate.Print();


    }

};
