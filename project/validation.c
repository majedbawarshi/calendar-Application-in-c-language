#include<stdio.h>
//this library (preprocessor) is used to check if the user input is valid or not

//allows the user to choose another option from the application
void reInput()
{
    char c[]="";
    printf("\nDo you want to re-enter a new choice from the main menu(y)? ");
    fflush(stdin);
    gets(c);
    //converting entered text to lower case
    strlwr(c);
    if(strcmp(c,"y")==0||strcmp(c,"yes")==0){
        system("cls");
        printChoices();
    }
    else{
        exit(0);
    }
}

//execute if the input is invalid
void invalidInput()
{
    printf("\nYou have selected invalid choice!\a");
    reInput();
}

//a function that checks whether the year and month is valid or not.
void checkValidYearAndMonth(float y, float m)
{
    //defining two variable of type int and assigning
    //the parameters value to them to get rid of the decimal point.
    int year=y,month=m;

    //(year!=y && month!=m) checks whether the entered month and year
    // are float numbers.
    if(0>=year && (0>=month || 12<month) || (year!=y && month!=m)){
        printf("\a\n\nYou have entered invalid year and month.\n\n");
        //terminate the program
        invalidInput();
    }
    else if(0>=year || year!=y){
        printf("\a\n\nYou have entered invalid year.\n\n");
        //terminate the program
        invalidInput();
    }
    else if((0>=month || 12<month) || month!=m){
        printf("\a\n\nYou have entered invalid month.\n\n");
        //terminate the program
        invalidInput();
    }
}

//used to check if the day is valid. used in option 2
void checkValidDay(float day)
{
    fflush(stdin);
    if(0>=day || day!=(int)day){
        printf("You have entered invalid day, please try again!\a\n");
        choice(2);
    }
}

//a function that check if none of the options has been selected or the user has selected invalid input
void checkValidChoice(float cho)
{
    int iChoice=cho;
    if((0>cho || 9<cho) || iChoice!=cho){
        //printing a failure message to the user and asking him if he would like to try
        //another functionallity of the app.
        invalidInput();
    }
}
