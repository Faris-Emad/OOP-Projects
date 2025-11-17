#include "CommonLib.h"
#include <fstream>
#include <random>
#include <cctype>

//===========================================
// Date Utility Functions Implementation
//===========================================

bool IsLeapYear(int year) {
    return (((year % 100) != 0 && (year % 4) == 0) || (year % 400) == 0);
}

short NumberOfDaysInAMonth(short month, short year) {
    if (month < 1 || month > 12) {
        return 0;
    }
    const short daysInMonth[13] = {0, 31, 28, 31, 30, 31, 30, 31, 31, 30, 31, 30, 31};
    return (month == 2) ? (IsLeapYear(year) ? 29 : 28) : daysInMonth[month];
}

bool IsLastDayInMonth(sDate Date) {
    short LastDay = NumberOfDaysInAMonth(Date.Month, Date.Year);
    return Date.Day == LastDay;
}

bool IsLastMonthInYear(short Month) {
    return Month == 12;
}

sDate IncreaseDateByOneDay(sDate Date) {
    if (IsLastDayInMonth(Date)) {
        if (IsLastMonthInYear(Date.Month)) {
            Date.Month = 1;
            Date.Day = 1;
            Date.Year++;
        }
        else {
            Date.Day = 1;
            Date.Month++;
        }
    }
    else {
        Date.Day++;
    }
    return Date;
}

sDate IncreaseDateByXDays(sDate Date, int AddingXDays) {
    for (int i = 1; i <= AddingXDays; i++) {
        Date = IncreaseDateByOneDay(Date);
    }
    return Date;
}

sDate DecreaseDateByOneDay(sDate Date) {
    if (Date.Day == 1) {
        if (Date.Month == 1) {
            Date.Month = 12;
            Date.Day = NumberOfDaysInAMonth(Date.Month, Date.Year - 1);
            Date.Year--;
        }
        else {
            Date.Month--;
            Date.Day = NumberOfDaysInAMonth(Date.Month, Date.Year);
        }
    }
    else {
        Date.Day--;
    }
    return Date;
}

sDate DecreaseDateByXDays(sDate Date, int XDays) {
    for (int i = 1; i <= XDays; i++) {
        Date = DecreaseDateByOneDay(Date);
    }
    return Date;
}

// Week/Month/Year increments and decrements
sDate IncreaseDateByOneWeek(sDate Date) {
    return IncreaseDateByXDays(Date, 7);
}

sDate IncreaseDateByXWeeks(sDate Date, int AddingXWeeks) {
    return IncreaseDateByXDays(Date, AddingXWeeks * 7);
}

sDate IncreaseDateByOneMonth(sDate Date) {
    if (IsLastMonthInYear(Date.Month)) {
        Date.Month = 1;
        Date.Year++;
    } else {
        Date.Month++;
    }
    
    // Adjust for months with different days
    short daysInNewMonth = NumberOfDaysInAMonth(Date.Month, Date.Year);
    if (Date.Day > daysInNewMonth) {
        Date.Day = daysInNewMonth;
    }
    
    return Date;
}

sDate IncreaseDateByXMonths(sDate Date, int AddingXMonths) {
    for (int i = 1; i <= AddingXMonths; i++) {
        Date = IncreaseDateByOneMonth(Date);
    }
    return Date;
}

sDate IncreaseDateByOneYear(sDate Date) {
    Date.Year++;
    return Date;
}

sDate IncreaseDateByXYears(sDate Date, int AddingXYears) {
    Date.Year += AddingXYears;
    return Date;
}

sDate IncreaseDateByOneDecade(sDate Date) {
    Date.Year += 10;
    return Date;
}

sDate IncreaseDateByXDecades(sDate Date, int AddingXDecades) {
    Date.Year += (AddingXDecades * 10);
    return Date;
}

sDate IncreaseDateByOneCentury(sDate Date) {
    Date.Year += 100;
    return Date;
}

sDate IncreaseDateByOneMillennium(sDate Date) {
    Date.Year += 1000;
    return Date;
}

sDate DecreaseDateByOneWeek(sDate Date) {
    return DecreaseDateByXDays(Date, 7);
}

sDate DecreaseDateByXWeeks(sDate Date, int XWeeks) {
    return DecreaseDateByXDays(Date, XWeeks * 7);
}

sDate DecreaseDateByOneMonth(sDate Date) {
    if (Date.Month == 1) {
        Date.Month = 12;
        Date.Year--;
    } else {
        Date.Month--;
    }
    
    // Adjust for months with different days
    short daysInNewMonth = NumberOfDaysInAMonth(Date.Month, Date.Year);
    if (Date.Day > daysInNewMonth) {
        Date.Day = daysInNewMonth;
    }
    
    return Date;
}

sDate DecreaseDateByXMonths(sDate Date, int XMonths) {
    for (int i = 1; i <= XMonths; i++) {
        Date = DecreaseDateByOneMonth(Date);
    }
    return Date;
}

sDate DecreaseDateByOneYear(sDate Date) {
    Date.Year--;
    return Date;
}

sDate DecreaseDateByXYears(sDate Date, int XYears) {
    Date.Year -= XYears;
    return Date;
}

sDate DecreaseDateByOneDecade(sDate Date) {
    Date.Year -= 10;
    return Date;
}

sDate DecreaseDateByXDecades(sDate Date, int XDecades) {
    Date.Year -= (XDecades * 10);
    return Date;
}

// Aliases for naming variations found in problems
sDate DecreaseDateByOneyear(sDate Date) {
    return DecreaseDateByOneYear(Date);
}

sDate DecreaseDateByXyears(sDate Date, int X_Years) {
    return DecreaseDateByXYears(Date, X_Years);
}

sDate DecreaseDateByXYearsFaster(sDate Date, int X_Years) {
    return DecreaseDateByXYears(Date, X_Years);
}

bool IsDate1LessThanDate2(sDate Date1, sDate Date2) {
    return ((Date1.Year < Date2.Year) ||
            (Date1.Year == Date2.Year && Date1.Month < Date2.Month) ||
            (Date1.Year == Date2.Year && Date1.Month == Date2.Month && Date1.Day < Date2.Day));
}

bool IsDate1EqualDate2(sDate Date1, sDate Date2) {
    return (Date1.Year == Date2.Year && Date1.Month == Date2.Month && Date1.Day == Date2.Day);
}

bool IsDate1AfterDate2(sDate Date1, sDate Date2) {
    return (!IsDate1LessThanDate2(Date1, Date2) && !IsDate1EqualDate2(Date1, Date2));
}

bool IsDate1BeforeDate2(sDate Date1, sDate Date2) {
    return IsDate1LessThanDate2(Date1, Date2);
}

enDateCompare CompareDates(sDate Date1, sDate Date2) {
    if (IsDate1LessThanDate2(Date1, Date2))
        return enDateCompare::Before;
    if (IsDate1EqualDate2(Date1, Date2))
        return enDateCompare::Equal;
    return enDateCompare::After;
}

void SwapDates(sDate& Date1, sDate& Date2) {
    sDate TempDate = Date1;
    Date1 = Date2;
    Date2 = TempDate;
}

short GetDifferenceInDays(sDate Date1, sDate Date2, bool IncludingEndDay) {
    int Days = 0;
    
    // Swap dates if Date1 is after Date2
    if (IsDate1AfterDate2(Date1, Date2)) {
        SwapDates(Date1, Date2);
    }
    
    while (!IsDate1EqualDate2(Date1, Date2)) {
        Days++;
        Date1 = IncreaseDateByOneDay(Date1);
    }
    
    return IncludingEndDay ? ++Days : Days;
}

int PeriodLengthInDays(sDate Date1, sDate Date2, bool IncludingEndDay) {
    return GetDifferenceInDays(Date1, Date2, IncludingEndDay);
}

short NumberOfTotalDaysFormTheBeginning(short day, short month, short year) {
    short Total = 0;
    for (short i = 1; i <= month - 1; i++) {
        Total += NumberOfDaysInAMonth(i, year);
    }
    Total += day;
    return Total;
}

short NumberOfTotalDaysFormTheBeginning(sDate Date) {
    return NumberOfTotalDaysFormTheBeginning(Date.Day, Date.Month, Date.Year);
}

short NumberOfTotalDaysFromTheBeginning(short day, short month, short year) {
    return NumberOfTotalDaysFormTheBeginning(day, month, year);
}

short NumberOfTotalDaysFromTheBeginning(sDate Date) {
    return NumberOfTotalDaysFormTheBeginning(Date);
}

short DaysUntilEndOfWeek(sDate Date) {
    short dayOrder = DayOfWeekOrder(Date);
    return (6 - dayOrder); // Saturday is day 6
}

short DaysUntilEndOfMonth(sDate Date) {
    short NumberOfDaysInCurrentMonth = NumberOfDaysInAMonth(Date.Month, Date.Year);
    return NumberOfDaysInCurrentMonth - Date.Day;
}

short DaysUntilEndOfYear(sDate Date) {
    short totalDays = NumberOfTotalDaysFormTheBeginning(Date);
    short daysInYear = IsLeapYear(Date.Year) ? 366 : 365;
    return daysInYear - totalDays;
}

sDate GetDateFromDayOrderInYear(short DaysOrderInYear, short year) {
    sDate Date;
    Date.Year = year;
    Date.Month = 1;
    Date.Day = 1;
    
    short remainingDays = DaysOrderInYear - 1;
    
    while (remainingDays > 0) {
        short daysInCurrentMonth = NumberOfDaysInAMonth(Date.Month, Date.Year);
        
        if (remainingDays >= daysInCurrentMonth - Date.Day + 1) {
            remainingDays -= (daysInCurrentMonth - Date.Day + 1);
            Date.Month++;
            Date.Day = 1;
        } else {
            Date.Day += remainingDays;
            remainingDays = 0;
        }
    }
    
    return Date;
}

sDate AddDaysToDate(sDate Date, int DaysToAdd) {
    return IncreaseDateByXDays(Date, DaysToAdd);
}

int ActualVacationDays(sDate Date1, sDate Date2) {
    int Days = 0;
    
    if (IsDate1AfterDate2(Date1, Date2)) {
        SwapDates(Date1, Date2);
    }
    
    while (!IsDate1EqualDate2(Date1, Date2)) {
        if (IsBusinessDay(Date1)) {
            Days++;
        }
        Date1 = IncreaseDateByOneDay(Date1);
    }
    
    return Days;
}

int GetYourAgeInDays(sDate Date, sDate Today, bool IncludingEndDay) {
    return GetDifferenceInDays(Date, Today, IncludingEndDay);
}

short DayOfWeekOrder(short day, short month, short year) {
    int a = ((14 - month) / 12);
    int y = year - a;
    int m = month + (12 * a) - 2;
    int d = (day + (31 * m) / 12 + y + y / 4 - y / 100 + y / 400) % 7;
    return d;
}

short DayOfWeekOrder(sDate Date) {
    return DayOfWeekOrder(Date.Day, Date.Month, Date.Year);
}

string DayName(short DayOfWeekOrder) {
    const string days[7] = {
        "Sunday", "Monday", "Tuesday", "Wednesday",
        "Thursday", "Friday", "Saturday"
    };
    return days[DayOfWeekOrder];
}

string MonthShortName(int month) {
    const string months[13] = {"", "Jan", "Feb", "Mar", "Apr", "May", "Jun", "Jul", "Aug", "Sep", "Oct", "Nov", "Dec"};
    if (month < 1 || month > 12) return "";
    return months[month];
}

void PrintMonthCalender(short month, short year) {
    cout << "\n  " << MonthShortName(month) << " " << year << "\n";
    cout << "Su Mo Tu We Th Fr Sa\n";

    short daysInMonth = NumberOfDaysInAMonth(month, year);

    // Day of week for 1st of the month
    short startDay = DayOfWeekOrder(1, month, year);

    // Indent first week
    for (short i = 0; i < startDay; ++i) cout << "   ";

    for (short day = 1; day <= daysInMonth; ++day) {
        cout << setw(2) << day << " ";
        if ((startDay + day) % 7 == 0) cout << "\n";
    }
    cout << "\n";
}

void PrintYearCalender(short year) {
    cout << "\nCalendar for " << year << "\n";
    for (short month = 1; month <= 12; ++month) {
        PrintMonthCalender(month, year);
    }
}

bool IsEndOfWeek(sDate Date) {
    return DayOfWeekOrder(Date) == 6; // Saturday
}

bool IsWeekEnd(sDate Date) {
    short dayOrder = DayOfWeekOrder(Date);
    return (dayOrder == 5 || dayOrder == 6); // Friday = 5, Saturday = 6
}

bool IsBusinessDay(sDate Date) {
    return !IsWeekEnd(Date);
}

bool IsValidDate(short day, short month, short year) {
    if (month < 1 || month > 12 || day < 1) {
        return false;
    }
    return day <= NumberOfDaysInAMonth(month, year);
}

sDate GetCurrentDate() {
    time_t t = time(0);
    tm* now = localtime(&t);
    sDate CurrentDate;
    CurrentDate.Day = now->tm_mday;
    CurrentDate.Month = now->tm_mon + 1;
    CurrentDate.Year = now->tm_year + 1900;
    return CurrentDate;
}

short ReadYear() {
    short year;
    cout << "Please enter a Year? ";
    cin >> year;
    return year;
}

short ReadMonth() {
    short month;
    cout << "Please enter a Month? ";
    cin >> month;
    return month;
}

short ReadDay() {
    short day;
    cout << "Please enter a Day? ";
    cin >> day;
    return day;
}

short ReadVacationDays() {
    short days;
    cout << "Please enter vacation days?: ";
    cin >> days;
    return days;
}

sDate ReadFullDate() {
    sDate Date;
    Date.Day = ReadDay();
    Date.Month = ReadMonth();
    Date.Year = ReadYear();
    return Date;
}

void PrintDate(sDate date, string description) {
    if (!description.empty()) {
        cout << description << ": ";
    }
    cout << date.Day << "/" << date.Month << "/" << date.Year;
}

void PrintDateFormatted(sDate Date) {
    cout << DayName(DayOfWeekOrder(Date)) << " , " 
         << Date.Day << "/" << Date.Month << "/" << Date.Year;
}

bool IsDateWithinPeriod(sDate DateToCheck, sPeriod Period) {
    return (!IsDate1LessThanDate2(DateToCheck, Period.StartDate) && 
            !IsDate1AfterDate2(DateToCheck, Period.EndDate));
}

bool IsOverlap(sPeriod Period1, sPeriod Period2) {
    return (!IsDate1LessThanDate2(Period1.EndDate, Period2.StartDate) && 
            !IsDate1LessThanDate2(Period2.EndDate, Period1.StartDate));
}

sPeriod ReadFullPeriods() {
    sPeriod Period;
    cout << "\\nEnter Start Date:\\n";
    Period.StartDate = ReadFullDate();
    cout << "\\nEnter End Date:\\n";
    Period.EndDate = ReadFullDate();
    return Period;
}
