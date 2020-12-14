/*
 * clock.c
 *
 *  Created on: 13 Dec 2020
 *      Author: niv
 */

#include "Clock.h"
#include "Functions.h"
#include <stdio.h>
#include <stdlib.h>
#include <string.h>


Clock* setTime()
{
	Clock* clock = (Clock*)malloc(sizeof(Clock));
	if (!clock) // (clock == NULL) --> allocaton didn't succeed
	{
		printf("ERROR! Out of memory!\n");
		return NULL;
	}
	char tempTime[TIME_LEN];
	char delim[] = {",:"};
	char *token ;

	int tempHours;
	int tempMinetes;

	printf("Please enter time in format HH:MM :\n");
	myGets(tempTime,TIME_LEN);
//	printf( "%s\n", tempTime );
	token = strtok(tempTime, delim);
	tempHours = atoi(token);
	token = strtok(NULL, delim);
	tempMinetes = atoi(token);

	if(checkValiadHours(tempHours) && checkValiadMinutes(tempMinetes))
	{
		clock->hours=tempHours;
		clock->minutes=tempMinetes;
		return clock;
	}

	printf( "Invalid time! please try again...\n");
	 return NULL;
}

int checkValiadHours(int hours)
{
	if(hours>23 || hours <0)
		return 0;
	else return 1;
}

int checkValiadMinutes(int minutes)
{
	if(minutes>59 || minutes <0)
		return 0;
	else return 1;
}

void printTime(Clock *clock)
{
	if(clock->hours<10)
	{
		printf("0%d:",clock->hours);
	}
	else
		printf("%d:",clock->hours);


	if(clock->minutes<10)
	{
		printf("0%d\n",clock->minutes);
	}
	else
		printf("%d\n",clock->minutes);

}
