/*
 * main.c
 *
 *  Created on: 10 Dec 2020
 *      Author: niv
 */

//#include "Airport.h"
//#include "AirportManager.h"

#include <stdio.h>
#include <time.h>
#include <string.h>

#include "Airport.h"
#include "Airline.h"
#include "AirportManager.h"
#include "Clock.h"
#include "exe.h"



int main()
{

	AirportManager manager;
	initAirportManager(&manager);
//	printAirportManager(&manager);

	Airline airline;
	initAirline(&airline);
//	printAirline(&airline);

	runMenu();
	int choice;
	scanf("%d",&choice);
	getchar();
	while(choice!=6)
	{
		runSelectedOption(choice, &manager, &airline);
		runMenu();
		scanf("%d",&choice);
		getchar();
	}

}
