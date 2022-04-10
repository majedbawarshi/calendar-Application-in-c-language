#ifndef MONTHCALENDAR_H_INCLUDED
#define MONTHCALENDAR_H_INCLUDED

bool isLeapYear(int year);

int numberOfDaysInMonth(int year, int month);

int getTotalNumberOfDays(int year, int month);

int monthStartingDay(int year, int month);

char* monthName(int month);

void printMonth(int year, int month);

#endif // MONTHCALENDAR_H_INCLUDED
