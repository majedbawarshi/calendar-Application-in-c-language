//a function that returns the day name of the given day number.
char* dayName(int day)
{
    char* weekDays[] = {"Saturday", "Sunday", "Monday",
                        "Tuseday", "Wednesday", "Thursday",
                        "Friday" };
    return weekDays[day-1];
}

//Zeller’s technique to find the day of the given date
int zellersAlgorithm(int day, int month, int year)
{
    int century, yearOfCentury, zellersFormula;

    //in zeller's Algorithm january and febrruary are counted as months 13 and 14 of the previous year
    if(2 >= month){
        month += 12;
        year--;
    }

    century=(year)/100;

    yearOfCentury=(year)%100;

    zellersFormula=(day+((26*(month+1))/10)+yearOfCentury+(yearOfCentury/4)+(century/4)+5*century) % 7;

    return zellersFormula+1;
}
