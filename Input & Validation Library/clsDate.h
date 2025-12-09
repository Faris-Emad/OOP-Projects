#pragma once
#include <iostream>
#include <fstream>
#include <random>
#include <cctype>
#include <iomanip>
#include <string>
#include <vector>
#include <ctime>
using namespace std;

class clsDate{
    private:
        struct _sDate {
            int _Day;
            int _Month;
            int _Year;
        };
    public:
        _sDate Date;
        clsDate() {
            time_t t = time(0);
            tm* now  = localtime(&t);
            Date._Day     = now->tm_mday;
            Date._Month   = now->tm_mon + 1;
            Date._Year    =  now->tm_year + 1900;
        }
        clsDate(int Day, int Month, int Year){
            Date._Day = Day;
            Date._Month = Month;
            Date._Year = Year;
        }
        clsDate(short DayOrderInYear, short Year) {
            Date = GetDateFromDayOrderInYear(DayOrderInYear, Year);
        }
        void SetDay(int Day){
            Date._Day = Day;
        }
        int Day() {
            return Date._Day;
        }
        void SetMonth(int Month){
            Date._Month = Month;
        }
        int Month() {
            return Date._Month;
        }
        void SetYear(int Year){
            Date._Year = Year;
        }
        int Year() {
            return Date._Year;
        }
        void Print() {
            cout << Date._Day << "/" << Date._Month << "/" << Date._Year << endl;
        }

        vector<string> SplitString(string S1, string delim) {
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

        _sDate StringToDate(string Date1) {
            _sDate Date;
            vector<string> vDate = SplitString(Date1, "/");
            Date._Day = stoi(vDate[0]);
            Date._Month = stoi(vDate[1]);
            Date._Year = stoi(vDate[2]);
            return Date;
        }
        clsDate(string Date1){
            Date = StringToDate(Date1);
        }

        static bool IsLeapYear(int year) {
            return (((year % 100) != 0 && (year % 4) == 0) || (year % 400) == 0);
        }
        bool IsLeapYear() {
            return IsLeapYear(Date._Year);
        }

        static bool IsLastDayInMonth(_sDate &Date1) {
            short LastDay = NumberOfDaysInAMonth(Date1._Month, Date1._Year);
            return Date1._Day == LastDay;
        }

        bool IsLastDayInMonth() {
            return IsLastDayInMonth(Date);
        }

        static bool IsLastMonthInYear(short Month) {
            return Month == 12;
        }
        bool IsLastMonthInYear() {
            return IsLastMonthInYear(Date._Month);
        }

        static short NumberOfDaysInAMonth(short month, short year) {
            if (month < 1 || month > 12) {
                return 0;
            }
            const short daysInMonth[13] = {0, 31, 28, 31, 30, 31, 30, 31, 31, 30, 31, 30, 31};
            return (month == 2) ? (IsLeapYear(year) ? 29 : 28) : daysInMonth[month];
        }
        short NumberOfDaysInAMonth(){
            return NumberOfDaysInAMonth(Date._Month, Date._Year);
        }

        static void PrintMonthCalender(short month, short year) {
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
        void PrintMonthCalender() {
            return PrintMonthCalender(Date._Month, Date._Year);
        }
        static short DayOfWeekOrder(short day, short month, short year) {
            int a = ((14 - month) / 12);
            int y = year - a;
            int m = month + (12 * a) - 2;
            int d = (day + (31 * m) / 12 + y + y / 4 - y / 100 + y / 400) % 7;
            return d;
        }

        short DayOfWeekOrder() {
            return DayOfWeekOrder(Date._Day, Date._Month, Date._Year);
        }

        static string DayName(short DayOfWeekOrder) {
            const string days[7] = {
                "Sunday", "Monday", "Tuesday", "Wednesday",
                "Thursday", "Friday", "Saturday"
            };
            return days[DayOfWeekOrder];
        }

        string DayName() {
            short _DayOfWeekOrder = DayOfWeekOrder();
            return DayName(_DayOfWeekOrder);
        }

        static string MonthShortName(int month) {
            const string months[13] = {"", "Jan", "Feb", "Mar", "Apr", "May", "Jun", "Jul", "Aug", "Sep", "Oct", "Nov", "Dec"};
            if (month < 1 || month > 12) return "";
            return months[month];
        }

        string MonthShortName(){
            return MonthShortName(Date._Month);
        }

        static void PrintYearCalender(short year) {
            cout << "\nCalendar for " << year << "\n";
            for (short month = 1; month <= 12; ++month) {
                PrintMonthCalender(month, year);
            }
        }
        void PrintYearCalender() {
            return PrintYearCalender(Date._Year);
        }
        static bool IsDate1BeforeDate2(_sDate Date1, _sDate Date2) {
            return  (Date1._Year < Date2._Year) ? true : ((Date1._Year == Date2._Year) ? (Date1._Month < Date2._Month ? true : (Date1._Month == Date2._Month ? Date1._Day < Date2._Day : false)) : false);
        }

        static bool IsDate1EqualDate2(_sDate Date1, _sDate Date2) {
            return  (Date1._Year == Date2._Year) ? ((Date1._Month == Date2._Month) ? ((Date1._Day == Date2._Day) ? true : false) : false) : false;
        }

        static bool IsDate1AfterDate2(_sDate Date1, _sDate Date2) {
            return (!IsDate1BeforeDate2(Date1, Date2) && !IsDate1EqualDate2(Date1, Date2));
        }

        enum enDateCompare { Before = -1, Equal = 0, After = 1 };

        static enDateCompare CompareDates(_sDate Date1, _sDate Date2) {
            if (IsDate1BeforeDate2(Date1, Date2))
                return enDateCompare::Before;
            if (IsDate1EqualDate2(Date1, Date2))
                return enDateCompare::Equal;
            // this is faster
            return enDateCompare::After;
        }

        static _sDate IncreaseDateByOneDay(_sDate &Date) {
            if (IsLastDayInMonth(Date)) {
                if (IsLastMonthInYear(Date._Month)) {
                    Date._Month = 1;
                    Date._Day = 1;
                    Date._Year++;
                }
                else {
                    Date._Day = 1;
                    Date._Month++;
                }
            }
            else {
                Date._Day++;
            }
            return Date;
        }

        _sDate IncreaseDateByOneDay() {
            return IncreaseDateByOneDay(Date);
        }
        

        static _sDate IncreaseDateByXDays(_sDate &Date, int AddingXDays) {
            for (int i = 1; i <= AddingXDays; i++) {
                Date = IncreaseDateByOneDay(Date);
            }
            return Date;
        }

        _sDate IncreaseDateByXDays(int AddingXDays) {
            return IncreaseDateByXDays(Date, AddingXDays);
        }
        

        static _sDate DecreaseDateByOneDay(_sDate &Date) {
            if (Date._Day == 1) {
                if (Date._Month == 1) {
                    Date._Month = 12;
                    Date._Day = NumberOfDaysInAMonth(Date._Month, Date._Year - 1);
                    Date._Year--;
                }
                else {
                    Date._Month--;
                    Date._Day = NumberOfDaysInAMonth(Date._Month, Date._Year);
                }
            }
            else {
                Date._Day--;
            }
            return Date;
        }

        _sDate DecreaseDateByOneDay() {
            return DecreaseDateByOneDay(Date);
        }

        static _sDate DecreaseDateByXDays(_sDate Date, int XDays) {
            for (int i = 1; i <= XDays; i++) {
                Date = DecreaseDateByOneDay(Date);
            }
            return Date;
        }

        _sDate DecreaseDateByXDays(int XDays) {
            return DecreaseDateByXDays(Date, XDays);
        }

        
        // Week/Month/Year increments and decrements
        static _sDate IncreaseDateByOneWeek(_sDate &Date) {
            return IncreaseDateByXDays(Date, 7);
        }
        _sDate IncreaseDateByOneWeek() {
            return IncreaseDateByOneWeek(Date);
        }

        static _sDate IncreaseDateByXWeeks(_sDate &Date, int AddingXWeeks) {
            return IncreaseDateByXDays(Date, AddingXWeeks * 7);
        }
        _sDate IncreaseDateByXWeeks(int XWeeks) {
            return IncreaseDateByXWeeks(Date, XWeeks);
        }

        static _sDate IncreaseDateByOneMonth(_sDate &Date) {
            if (IsLastMonthInYear(Date._Month)) {
            Date._Month = 1;
            Date._Year++;
            } else {
            Date._Month++;
            }
            
            short daysInNewMonth = NumberOfDaysInAMonth(Date._Month, Date._Year);
            if (Date._Day > daysInNewMonth) {
            Date._Day = daysInNewMonth;
            }
            
            return Date;
        }
        _sDate IncreaseDateByOneMonth() {
            return IncreaseDateByOneMonth(Date);
        }

        static _sDate IncreaseDateByXMonths(_sDate &Date, int AddingXMonths) {
            for (int i = 1; i <= AddingXMonths; i++) {
            Date = IncreaseDateByOneMonth(Date);
            }
            return Date;
        }
        _sDate IncreaseDateByXMonths(int AddingXMonths) {
            return IncreaseDateByXMonths(Date, AddingXMonths);
        }

        static _sDate IncreaseDateByOneYear(_sDate &Date) {
            Date._Year++;
            return Date;
        }
        _sDate IncreaseDateByOneYear() {
            return IncreaseDateByOneYear(Date);
        }

        static _sDate IncreaseDateByXYears(_sDate &Date, int AddingXYears) {
            Date._Year += AddingXYears;
            return Date;
        }
        _sDate IncreaseDateByXYears(int AddingXYears) {
            return IncreaseDateByXYears(Date, AddingXYears);
        }

        static _sDate IncreaseDateByOneDecade(_sDate &Date) {
            Date._Year += 10;
            return Date;
        }
        _sDate IncreaseDateByOneDecade() {
            return IncreaseDateByOneDecade(Date);
        }

        static _sDate IncreaseDateByXDecades(_sDate &Date, int AddingXDecades) {
            Date._Year += (AddingXDecades * 10);
            return Date;
        }
        _sDate IncreaseDateByXDecades(int AddingXDecades) {
            return IncreaseDateByXDecades(Date, AddingXDecades);
        }

        static _sDate IncreaseDateByOneCentury(_sDate &Date) {
            Date._Year += 100;
            return Date;
        }
        _sDate IncreaseDateByOneCentury() {
            return IncreaseDateByOneCentury(Date);
        }

        static _sDate IncreaseDateByOneMillennium(_sDate &Date) {
            Date._Year += 1000;
            return Date;
        }
        _sDate IncreaseDateByOneMillennium() {
            return IncreaseDateByOneMillennium(Date);
        }

        static _sDate DecreaseDateByOneWeek(_sDate &Date) {
            return DecreaseDateByXDays(Date, 7);
        }
        _sDate DecreaseDateByOneWeek() {
            return DecreaseDateByOneWeek(Date);
        }

        static _sDate DecreaseDateByXWeeks(_sDate &Date, int XWeeks) {
            return DecreaseDateByXDays(Date, XWeeks * 7);
        }
        _sDate DecreaseDateByXWeeks(int XWeeks) {
            return DecreaseDateByXWeeks(Date, XWeeks);
        }

        static _sDate DecreaseDateByOneMonth(_sDate &Date) {
            if (Date._Month == 1) {
            Date._Month = 12;
            Date._Year--;
            } else {
            Date._Month--;
            }
            
            short daysInNewMonth = NumberOfDaysInAMonth(Date._Month, Date._Year);
            if (Date._Day > daysInNewMonth) {
            Date._Day = daysInNewMonth;
            }
            
            return Date;
        }
        _sDate DecreaseDateByOneMonth() {
            return DecreaseDateByOneMonth(Date);
        }

        static _sDate DecreaseDateByXMonths(_sDate &Date, int XMonths) {
            for (int i = 1; i <= XMonths; i++) {
            Date = DecreaseDateByOneMonth(Date);
            }
            return Date;
        }
        _sDate DecreaseDateByXMonths(int XMonths) {
            return DecreaseDateByXMonths(Date, XMonths);
        }

        static _sDate DecreaseDateByOneYear(_sDate &Date) {
            Date._Year--;
            return Date;
        }
        _sDate DecreaseDateByOneYear() {
            return DecreaseDateByOneYear(Date);
        }

        static _sDate DecreaseDateByXYears(_sDate &Date, int XYears) {
            Date._Year -= XYears;
            return Date;
        }
        _sDate DecreaseDateByXYears(int XYears) {
            return DecreaseDateByXYears(Date, XYears);
        }

        static _sDate DecreaseDateByOneDecade(_sDate &Date) {
            Date._Year -= 10;
            return Date;
        }
        _sDate DecreaseDateByOneDecade() {
            return DecreaseDateByOneDecade(Date);
        }

        static _sDate DecreaseDateByXDecades(_sDate &Date, int XDecades) {
            Date._Year -= (XDecades * 10);
            return Date;
        }
        _sDate DecreaseDateByXDecades(int XDecades) {
            return DecreaseDateByXDecades(Date, XDecades);
        }

        static _sDate DecreaseDateByOneCentury(_sDate &Date) {
            Date._Year -= 100;
            return Date;
        }
        _sDate DecreaseDateByOneCentury() {
            return DecreaseDateByOneCentury(Date);
        }

        static _sDate DecreaseDateByOneMillennium(_sDate &Date) {
            Date._Year -= 1000;
            return Date;
        }
        _sDate DecreaseDateByOneMillennium() {
            return DecreaseDateByOneMillennium(Date);
        }

        static short NumberOfTotalDaysFormTheBeginning(short day, short month, short year) {
            short Total = 0;
            for (short i = 1; i <= month - 1; i++) {
                Total += NumberOfDaysInAMonth(i, year);
            }
            Total += day;
            return Total;
        }

        short NumberOfTotalDaysFromTheBeginning() {
            return NumberOfTotalDaysFormTheBeginning(Date._Day, Date._Month, Date._Year);
        }
        static short DayOfWeekOrder(_sDate Date) {
            return DayOfWeekOrder(Date._Day, Date._Month, Date._Year);
        }

        static short DaysUntilEndOfWeek(_sDate &Date) {
            short dayOrder = DayOfWeekOrder(Date);
            return (6 - dayOrder); // Saturday is day 6
        }

        short DaysUntilEndOfWeek() {
           return DaysUntilEndOfWeek(Date);
        }

        static short DaysUntilEndOfMonth(_sDate &Date) {
            short NumberOfDaysInCurrentMonth = NumberOfDaysInAMonth(Date._Month, Date._Year);
            return NumberOfDaysInCurrentMonth - Date._Day;
        }

        short DaysUntilEndOfMonth() {
           return DaysUntilEndOfMonth(Date);
        }

        static short DaysUntilEndOfYear(_sDate &Date) {
            short totalDays = NumberOfTotalDaysFormTheBeginning(Date._Day, Date._Month, Date._Year);
            short daysInYear = IsLeapYear(Date._Year) ? 366 : 365;
            return daysInYear - totalDays;
        }

        short DaysUntilEndOfYear() {
           return DaysUntilEndOfYear(Date);
        }

        
        static _sDate GetDateFromDayOrderInYear(short DaysOrderInYear, short year) {
            _sDate Date;
            Date._Year = year;
            Date._Month = 1;
            Date._Day = 1;
            
            short remainingDays = DaysOrderInYear - 1;
            
            while (remainingDays > 0) {
                short daysInCurrentMonth = NumberOfDaysInAMonth(Date._Month, Date._Year);
                
                if (remainingDays >= daysInCurrentMonth - Date._Day + 1) {
                    remainingDays -= (daysInCurrentMonth - Date._Day + 1);
                    Date._Month++;
                    Date._Day = 1;
                } else {
                    Date._Day += remainingDays;
                    remainingDays = 0;
                }
            }
            
            return Date;
        }

        static bool IsEndOfWeek(_sDate &Date) {
            return DayOfWeekOrder(Date) == 6; // Saturday
        }

        bool IsEndOfWeek() {
            return IsEndOfWeek(Date);
        }

        static bool IsWeekEnd(_sDate &Date) {
            short dayOrder = DayOfWeekOrder(Date);
            return (dayOrder == 5 || dayOrder == 6); // Friday = 5, Saturday = 6
        }

        bool IsWeekEnd() {
            return IsWeekEnd(Date);
        }


        static bool IsBusinessDay(_sDate &Date) {
            return !IsWeekEnd(Date);
        }

        bool IsBusinessDay() {
            return IsBusinessDay(Date);
        }

        static bool IsValidDate(short day, short month, short year) {
            if (month < 1 || month > 12 || day < 1) {
                return false;
            }
            return day <= NumberOfDaysInAMonth(month, year);
        }

        bool IsValidDate() {
            return IsValidDate(Date._Day, Date._Month, Date._Year);
        }

        static void SwapDates(_sDate& Date1, _sDate& Date2) {
            _sDate TempDate = Date1;
            Date1 = Date2;
            Date2 = TempDate;
        }

        
        static int ActualVacationDays(_sDate Date1, _sDate Date2) {
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

        static int GetDifferenceInDays(_sDate Date1, _sDate Date2, bool IncludingEndDay) {
            int Days = 0;
            if (IsDate1AfterDate2(Date1, Date2)) {
                SwapDates(Date1, Date2);
            }
            while (!IsDate1EqualDate2(Date1, Date2)) {
                Days++;
                Date1 = IncreaseDateByOneDay(Date1);
            }
            return IncludingEndDay ? ++Days : Days;
        }

        int GetDifferenceInDays(clsDate Date2, bool IncludingEndDay) {
            return GetDifferenceInDays(this->Date, Date2.Date, IncludingEndDay);
        }

        static int PeriodLengthInDays(_sDate Date1, _sDate Date2, bool IncludingEndDay) {
            return GetDifferenceInDays(Date1, Date2, IncludingEndDay);
        }

        static int GetYourAgeInDays(_sDate BirthDate, _sDate Today, bool IncludingEndDay) {
            return GetDifferenceInDays(BirthDate, Today, IncludingEndDay);
        }

        int GetYourAgeInDays(bool IncludingEndDay) {
            clsDate Today;
            return GetDifferenceInDays(this->Date, Today.Date, IncludingEndDay);
        }

        

};