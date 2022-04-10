//Gregorian Calendar, the standard calendar in most of the world
#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include <string.h>
#include "validation.h"
#include "monthCalendar.h"
#include "dayname.h"


typedef struct{
    int year, month, day;
}MonthAndYearInt;

//they are float type because they will be used for testing purposes
typedef struct{
    float year, month, day;
}MonthAndYearFloat;

//a function that print if the year is leap or not.
void checkYear(int year)
{
    (isLeapYear(year)==true)?printf("\nthe year is leap.\n"):printf("\nthe year is not leap.\n");
}

//a function that print the month calendar on a text file.
void writeMonthOnFile(int year, int month, char *fileName, char *mode)
{
    FILE *monthCalendarFile;
    int startDayIndex, numOfDaysInMonth, i;
    //char *fileName="monthCalendar.txt", *mode="w";

    //getting the month's first day index.
    startDayIndex=monthStartingDay(year,month);

    //getting the number of days in month.
    numOfDaysInMonth=numberOfDaysInMonth(year,month);

    //oppening file for writing.
    monthCalendarFile = fopen(fileName, mode);

    //checking if the file has been opened successfully.
    if(monthCalendarFile == NULL){
      printf("Error!");
      exit(1);
    }

    //this will only work when we want to print many different years and months.
    if(fileName=="multipleMonths.txt")
        fprintf(monthCalendarFile,"\nMonth %d of year %d",month,year);

    //printing the month title and days title.
    fprintf(monthCalendarFile,"\n-----------------------------\n");

    //for styling purposes.
    if(month==5)
        fprintf(monthCalendarFile,"|\t     %s\t    |",monthName(month));
    else if(month==6||month==7)
        fprintf(monthCalendarFile,"|\t    %s\t    |",monthName(month));
    else
        fprintf(monthCalendarFile,"|\t   %s\t    |",monthName(month));

    fprintf(monthCalendarFile,"\n-----------------------------\n");
    fprintf(monthCalendarFile," Sun Mon Tue Wed Thu Fri Sat  \n");

    for(i=0;i<startDayIndex;i++)
        //4 spaces are between each month name and the month after.
        fprintf(monthCalendarFile,"    ");

    for(i=1;i<=numOfDaysInMonth;i++){
        //%4d means print 3 white spaces before the day number.
        fprintf(monthCalendarFile,"%4d",i);
        //if the days in the week are fully achieved then go down one line.
        if((i+startDayIndex)%7 == 0)
           fprintf(monthCalendarFile,"\n");
    }
    fprintf(monthCalendarFile,"\n");

    fclose(monthCalendarFile);
}

//a function that print the year calendar on a text file.
void writeYearOnFile(int year)
{
    int month;
    char *fileName="yearCalendar.txt";

    for(month=1;month<=12;month++){
        if(month==1){
            writeMonthOnFile(year, month, fileName, "w");
        }
        else{
            writeMonthOnFile(year, month, fileName, "a");
        }
    }
}

//a function that print multiple month calendar on a text file.
void writeMultipleMonthOnFile(MonthAndYearInt *iMAndY, int numberOfMonths)
{
    int monthNo;
    char *fileName="multipleMonths.txt";

    //writing the entered months on file.
    for(monthNo=0;monthNo<numberOfMonths;monthNo++){
        if(monthNo==0){
            writeMonthOnFile((iMAndY+monthNo)->year, (iMAndY+monthNo)->month, fileName, "w");
        }
        else{
            writeMonthOnFile((iMAndY+monthNo)->year, (iMAndY+monthNo)->month, fileName, "a");
        }
    }
}

//a function that read the calendar from a text file.
void readCalendarfromFile(char *fileName)
{
    FILE *calendarFile;
    char calendarFileChar;

    //oppening file for writing.
    calendarFile = fopen(fileName, "r");

    //checking if the file has been opened successfully.
    if(calendarFile == NULL){
      printf("Error!");
      exit(1);
    }

    //printing every character that is in the file.
    while( (calendarFileChar=fgetc(calendarFile)) != EOF )
        printf("%c", calendarFileChar);

    fclose(calendarFile);
}

//a function that returns the century number
int calculateCentury(int year)
{
    int res;
    res=year/100;
    if(year%100 == 0){
        return res;
    }
    else{
        return res+1;
    }
}

//a function that print the month calendar on the screen.
void printYear(int year){
    int month;
    for(month=1;month<=12;month++){
        printMonth(year, month);
        printf("\n");
    }
}

//choices
void choice(int cho)
{
    MonthAndYearFloat fMAndY, *pFMAndY;
    MonthAndYearInt iMAndY, *pIMAndY;
    char *desiredDay;

    //9. print multiple years months on file and screen
    if(cho==9){
        //private variables are only available within the scope of this if statement and they are only used inside it.
        int numberOfMonths, monthNo;

        printf("enter how many months do you want: ");
        scanf("%d",&numberOfMonths);

        pFMAndY=(MonthAndYearFloat*) malloc(numberOfMonths*sizeof(MonthAndYearFloat));
        pIMAndY=(MonthAndYearInt*)   malloc(numberOfMonths*sizeof(MonthAndYearInt));

        //getting the month and year of each month callendar the user want to print
        for(monthNo=0;monthNo<numberOfMonths;monthNo++){
            fflush(stdin);
            printf("enter number %d year: ",monthNo+1);
            scanf("%f",&(pFMAndY+monthNo)->year);

            printf("enter number %d month: ",monthNo+1);
            scanf("%f",&(pFMAndY+monthNo)->month);

            checkValidYearAndMonth(pFMAndY->year,pFMAndY->month);

            (pIMAndY+monthNo)->year=(pFMAndY+monthNo)->year;
            (pIMAndY+monthNo)->month=(pFMAndY+monthNo)->month;
        }

        //sending the reference of the struct pIMAndY to send the stored values inside of it.
        writeMultipleMonthOnFile(pIMAndY, numberOfMonths);

        printf("\nYears months has been printed successfully to the file: multipleMonths.txt\n");
        printf("\nThe year calendar in the file is: \n");

        //printing the years months calendar by getting it from the file
        readCalendarfromFile("multipleMonths.txt");

        //giving a chance to the user to try another functionallity of the app.
        reInput();

        return;
    }

    printf("enter year: ");
    scanf("%f",&fMAndY.year);

    //check whether the input is valid or not.
    checkValidYearAndMonth(fMAndY.year,1);

    //storing the float variable in integer variable
    iMAndY.year=fMAndY.year;

    //checking if choice 0, 1, 4, 6, 8 because they only require the year input.
    if(cho==0 || cho==1 || cho==4 || cho==6 || cho==8){
        switch(cho){
            //0. calculate century
            case 0:
                printf("The century of year %d is: %d", iMAndY.year, calculateCentury(iMAndY.year));

                //giving a chance to the user to try another functionallity of the app.
                reInput();

            break;

            //1. check leap year
            case 1:
                checkYear(fMAndY.year);

                //giving a chance to the user to try another functionallity of the app.
                reInput();

            break;

            //4. print year calendar
            case 4:
                //printing year calendar.
                printYear(iMAndY.year);

                //giving a chance to the user to try another functionallity of the app.
                reInput();

            break;

            //6. write to file one year calendar
            case 6:
                writeYearOnFile(iMAndY.year);

                printf("\nYear has been printed successfully to the file: yearCalendar.txt\n");

                //giving a chance to the user to try another functionallity of the app.
                reInput();

            break;

            //8. write to file&print on screen one year
            case 8:
                writeYearOnFile(iMAndY.year);

                printf("\nYear has been printed successfully to the file: yearCalendar.txt\n");
                printf("\nThe year calendar in the file is: \n");

                //printing the year calendar by getting it from the file
                readCalendarfromFile("yearCalendar.txt");

                //giving a chance to the user to try another functionallity of the app.
                reInput();

            break;
        }
    }
    else{
        printf("enter month: ");
        scanf("%f",&fMAndY.month);

        checkValidYearAndMonth(fMAndY.year,fMAndY.month);

        //storing the float variable in integer variable
        iMAndY.month=fMAndY.month;

        switch(cho){
            //2. check day name of a given date
            case 2:
                printf("Enter the day of the month 1-31: ");
                scanf("%f",&fMAndY.day);

                //checking if entered day is valid
                checkValidDay(fMAndY.day);

                //storing the float variable in integer variable
                iMAndY.day=fMAndY.day;

                //getting the day name
                desiredDay=dayName(zellersAlgorithm(iMAndY.day, iMAndY.month, iMAndY.year));

                printf("Day name on the date %d/%d/%d is: %s", iMAndY.day, iMAndY.month, iMAndY.year, desiredDay);

                //giving a chance to the user to try another functionallity of the app.
                reInput();

            break;

            //3. print month calendar
            case 3:
                //printing month calendar.
                printMonth(iMAndY.year, iMAndY.month);

                //giving a chance to the user to try another functionallity of the app.
                reInput();

            break;

            //5. write to file one month calendar
            case 5:
                writeMonthOnFile(iMAndY.year, iMAndY.month, "monthCalendar.txt", "w");

                printf("\nMonth has been printed successfully to the file: monthCalendar.txt\n");

                //giving a chance to the user to try another functionallity of the app.
                reInput();

            break;

            //7. write to file&print on screen one month
            case 7:
                writeMonthOnFile(iMAndY.year, iMAndY.month, "monthCalendar.txt", "w");

                printf("\nMonth has been printed successfully to the file: monthCalendar.txt\n");
                printf("\nThe month calendar in the file is: \n");

                //printing the month by getting it from the file
                readCalendarfromFile("monthCalendar.txt");

                //giving a chance to the user to try another functionallity of the app.
                reInput();

            break;
        }
    }
}

void printChoices()
{
    float ch;
    printf("0. calculate century\n");
    printf("1. check leap year\n");
    printf("2. check day name of a given date\n");
    printf("3. print month calendar\n");
    printf("4. print year calendar\n");
    printf("5. write to file one month calendar\n");
    printf("6. write to file one year calendar\n");
    printf("7. write to file&print on screen one month\n");
    printf("8. write to file&print on screen one year\n");
    printf("9. write multiple years month to file and print it on screen\n");
    printf("\nYour choice: ");
    scanf("%f",&ch);
    checkValidChoice(ch);
    choice(ch);
}

int main()
{
    printChoices();
    return 0;
}
