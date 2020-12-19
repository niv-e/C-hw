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

	Airline airline;
	initAirline(&airline);

	int choice;
	do{
		runMenu();
		scanf("%d",&choice);
		getchar();
		runSelectedOption(choice, &manager, &airline);
	}while(choice!=6);


}
