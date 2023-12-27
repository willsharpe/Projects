#include <stdio.h>

#define TRUE 1
#define FALSE 0

int days_in_month[]={0,31,28,31,30,31,30,31,31,30,31,30,31};
char* months[]={
    " ",
    "\n\n\nJanuary",
    "\n\n\nFebruary",
    "\n\n\nMarch",
    "\n\n\nApril",
    "\n\n\nMay",
    "\n\n\nJune",
    "\n\n\nJuly",
    "\n\n\nAugust",
    "\n\n\nSeptember",
    "\n\n\nOctober",
    "\n\n\nNovember",
    "\n\n\nDecember"
};



int inputyear(void){
    int year;
    printf("Please enter a year (example: 1999 ) : ");
    scanf("%d",&year);
    return year;
}


int leapyear(int year){
    if(year%4==FALSE && year%100!=FALSE || year%400==FALSE){
        days_in_month[2]=29;
        return TRUE;
    }
    else{
        days_in_month[2]=28;
        return FALSE;
    }
}


int days(int year){
    int day;
    int d1,d2,d3;
    d1=(year-1.)/4.0;
    d2=(year-1.)/100.;
    d3=(year-1.)/400.;
    day=(year+d1-d2+d3)%7;
    return day;
}


void calendar(int year,int day){
    int month,this_day;
    for(month=1;month<=12;month++){
        printf("%s",months[month]);
        printf("\n\nSun  Mon  Tue  Wed  Thu  Fri  Sat\n ");

        for (this_day=1;this_day<=1+day*5;this_day++){
            printf(" ");
        }

        for (this_day=1;this_day<=days_in_month[month];this_day++){
            printf("%2d",this_day);

            if((this_day+day)%7>0)
                printf("   ");
            else
                printf("\n ");
        }
        day=(day+days_in_month[month])%7;

    }
}

int main(void){
    int year,daycode,this_leapyear;
    year=inputyear();
    daycode=days(year);
    leapyear(year);
    calendar(year,daycode);
    printf("\n");

}