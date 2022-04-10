#ifndef VALIDATION_H_INCLUDED
#define VALIDATION_H_INCLUDED

//allows the user to choose another option from the application
void reInput();

//execute if the input is invalid
void invalidInput();

//a function that checks whether the year and month is valid or not.
void checkValidYearAndMonth(float y, float m);

//used to check if the day is valid. used in option 2
void checkValidDay(float day);

//a function that check if none of the options has been selected or the user has selected invalid input
void checkValidChoice(float cho);

#endif // VALIDATION_H_INCLUDED
