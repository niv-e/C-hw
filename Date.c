/*
 * Date.c
 *
 *  Created on: 13 Dec 2020
 *      Author: niv
 */


#include "Date.h"
#include <stdio.h>
#include <stdlib.h>

#include <string.h>
#include "Functions.h"

Date* setDate()
{
	Date *date = (Date*)malloc(sizeof(Date));
	if (!date)
	{
	printf("ERROR! Out of memory!\n");
	return NULL;
	}
	int days_in_month[]= {0,31,28,31,30,31,30,31,31,30,31,30,31};
	char tempDate[DATE_LEN];
	char delim[] = {",:/"};
	char *token ;
	myGets(tempDate,DATE_LEN);//clean the buffer

	int day;
	int month;
	int year;

	printf("Please enter a date in format DD/MM/YYYY : \n");
	myGets(tempDate,DATE_LEN);
	printf("tempDate: %s \n",tempDate);
	getchar();
	token = strtok(tempDate, delim);
	day = atoi(token);
	token = strtok(NULL, delim);
	month = atoi(token);
	token = strtok(NULL, delim);
	year = atoi(token);

    if((month > 12) || (month < 0))
        return NULL;
    if((day > 31) || (day < 0) || day>days_in_month[month])
        return NULL;
    if((year > 9999) || (year < 2020))
        return NULL;

    date->day=day;
    date->month=month;
    date->year=year;

    return date;
}

void printDate(const Date *date)
{
	if(date->day<10)
	{
		printf("0%d/",date->day);
	}
	else
		printf("%d/",date->day);


	if(date->month<10)
	{
		printf("0%d/",date->month);
	}
	else
		printf("%d/",date->month);

	printf("%d\n",date->year);



}
