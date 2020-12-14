/*
 * Flight.c
 *
 *  Created on: 13 Dec 2020
 *      Author: niv
 */

#include "Flight.h"
#include "Airport.h"
#include "Functions.h"
#include <stdlib.h>
#include <string.h>

Flight* initFlight()
{
	Flight* flight = (Flight*)malloc(sizeof(Flight));
	if (!flight) // (clock == NULL) --> allocaton didn't succeed
	{
		printf("ERROR! Out of memory!\n");
		return NULL;
	}

	printf("Please enter flight departure Airport IATA code, make sure that the code exactly length of 3: \n");
	char tempSrcIata[LEN];
	myGets(tempSrcIata,LEN);
	if(!(checkIfValideIata(tempSrcIata)))
		return NULL;

	int flag =0;
	int isValid;
	char tempDestIata[LEN];
	while(flag==0)
	{
		printf("Please enter flight destination Airport IATA code, make sure that the code exactly length of 3: \n");
		myGets(tempDestIata,LEN);
		isValid = checkIfValideIata(tempDestIata);
		if(isValid && ((strcmp(tempSrcIata,tempDestIata) !=0)))
		{
			flag =1;
		}

	}
	Clock *clock =NULL;
	while (!clock)
	{
		clock=setTime();
	}

	Date* date = NULL;
	while (!date)
	{
		date=setDate();
	}

	flight->iataCodeSrc=strdup(tempSrcIata);
	flight->iataCodeDest=strdup(tempDestIata);
	flight->clock=clock;
	flight->date=date;

	return flight;
}


int checkIfFlightLandingAtDest(const Flight flight ,char* iataCodeSrc, char* iataCodeDest)
{
	char* flightIataSrc = flight.iataCodeSrc;
	char* flightIataDest = flight.iataCodeDest;

	int sameSrc;
	int sameDest;

	sameSrc = strcmp(flightIataSrc , iataCodeSrc);
	sameDest = strcmp(flightIataDest , iataCodeDest);

	if(sameDest && sameSrc)
	{
		printf("the flight departure from the source and landing at the destination\n");
		return 0;
	}
	else if(!(sameSrc))
	{
		printf("the flight departure airport IATA code is different\n");
	}
	else if(!(sameDest))
	{
		printf("the flight landing airport IATA code is different\n");
	}
	return 1;

}

void printFlightDetails(Flight* flight)
{
	printf("Flight departure IATA code:\t%s\n",flight->iataCodeSrc);
	printf("Flight destination IATA code:\t%s\n",flight->iataCodeDest);
	printTime(flight->clock);
	printDate(flight->date);
	printf("\n");


}

void freeFlight(Flight* flight)
{
	free(flight->iataCodeSrc);
	free(flight->iataCodeDest);
	free(flight->clock);
	free(flight->date);

}

//int checkHowManyFlightsOnLine (Flight** allFlight , int allFlightSize,char* iataCodeSrc, char* iataCodeDest )
//{
//	int count=0;
//	int numOfFlights;
//	int sameSrc;
//	int sameDest;
//
//	while(count <allFlightSize)
//	{
//		sameSrc = strcmp(allFlight[count]->iataCodeSrc , iataCodeSrc);
//		sameDest = strcmp(allFlight[count]->iataCodeDest , iataCodeDest);
//		if(sameDest && sameSrc)
//		{
//			numOfFlights++;
//		}
//		count ++;
//	}
//	return numOfFlights;
//
//}
