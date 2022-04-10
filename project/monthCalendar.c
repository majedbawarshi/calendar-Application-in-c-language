#include <stdbool.h>
#define FirstYearInCalendar 1
#define FirstDayInJanYear1 1

//a function that checks if the year is leap.
bool isLeapYear(int year)
{
    /*
    Every year that is exactly divisible by four is a leap year,
    except for years that are exactly divisible by 100,
    but these centurial years are leap years if they are exactly
    divisible by 400. For example, the years 1700, 1800
    and 1900 are not leap years, but the years 1600 and 2000 are.
    */
    if((year%4 == 0 && year%100 != 0) || year%400 == 0)
        // It is a leap year and February has 29 days.
        return true;
    else
        // It is not a leap year and February has 28 days.
        return false;
}

//a function that returns the number of days in a month.
int numberOfDaysInMonth(int year, int month)
{
    switch(month)
    {
        case 1:
            return 31;
        break;

        case 2:
            return (isLeapYear(year)==true)? 29 : 28;
        break;

        case 3:
            return 31;
        break;

        case 4:
            return 30;
        break;

        case 5:
            return 31;
        break;

        case 6:
            return 30;
        break;

        case 7:
            return 31;
        break;

        case 8:
            return 31;
        break;

        case 9:
            return 30;
        break;

        case 10:
            return 31;
        break;

        case 11:
            return 30;
        break;

        case 12:
            return 31;
        break;
    }
}

/*
a function that calculate the number of days starting from the first day
defined in FirstYearInCalendar macro (first year in the calendar)
till the last month(given as parameter).
*/
int getTotalNumberOfDays(int year, int month)
{
    int i, totalDays=0;
    /*
    calculating the days number in the whole years that are before the
    given year(given as the function parameter).
    */
    //FirstYearInCalendar is a macro defined using preprocessor directive.
    for(i=FirstYearInCalendar;i<year;i++){
        if(isLeapYear(i))
            //if the year is leap then it will have 366 days.
            totalDays+=366;
        else
            //if the year is not leap then it will have 365 days.
            totalDays+=365;
    }
    /*
    calculating the days in the last year that is given as a parameter
    till the desired month by starting from the month 1 till the last/desired
    month.
    */
    for(i=1;i<month;i++){
        totalDays+=numberOfDaysInMonth(year, i);
    }
    //returning the whole days count before the desired month.
    return totalDays;
}

//a function that returns the starting month's day index number.
int monthStartingDay(int year, int month)
{
    int totalNumOfDays, startDayIndex;
    //calculating the total number of days that are before the given month.
    totalNumOfDays=getTotalNumberOfDays(year, month);
    //FirstDayInJanYear1 is a macro defined using preprocessor directive.
    //Getting the index of the first day in the given month(as a parameter).
    startDayIndex=(totalNumOfDays + FirstDayInJanYear1) % 7;
    /*
    Indexes:
    Sunday =0, Monday=1, Tuesday=2, Wednesday=3,
    Thursday=4, Friday=5, Saturday=6.
    */
    return startDayIndex;
}

//a function that returns the month name of the given month number.
char* monthName(int month)
{
    char* months[] = {"January", "February", "March", "April", "May"
                            , "June", "July", "August", "September", "October"
                            , "November", "December" };
    return months[month-1];
}

//a function that print the month calendar.
void printMonth(int year, int month)
{
    int startDayIndex, numOfDaysInMonth, i;

    //getting the month's first day index.
    startDayIndex=monthStartingDay(year,month);

    //getting the number of days in month.
    numOfDaysInMonth=numberOfDaysInMonth(year,month);

    //printing the month title and days title.
    printf("\n-----------------------------\n");

    //for styling purposes.
    if(month==5)
        printf("|\t     %s\t    |",monthName(month));
    else if(month==6 || month==7)
        printf("|\t    %s\t    |",monthName(month));
    else
        printf("|\t   %s\t    |",monthName(month));

    printf("\n-----------------------------\n");
    printf(" Sun Mon Tue Wed Thu Fri Sat  \n");

    for(i=0;i<startDayIndex;i++)
        //4 spaces are between each month name and the month after.
        printf("    ");

    for(i=1;i<=numOfDaysInMonth;i++){
        //%4d means print 3 white spaces before the day number.
        printf("%4d",i);
        //if the days in the week are fully achieved then go down one line.
        if((i+startDayIndex)%7 == 0)
           printf("\n");
    }
    printf("\n");
}
