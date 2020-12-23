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

Flight* initFlight(AirportManager* manager)
{

	Flight* flight = (Flight*)malloc(sizeof(Flight));
	if (!flight) // (flight == NULL) --> allocation didn't succeed
	{
		printf("ERROR! Out of memory!\n");
		return NULL;
	}

	printf("Please enter flight departure Airport IATA code,"
			" make sure that the code exactly length of 3: \n");
	getchar();
	char tempSrcIata[IATA_LEN+1];
	myGets(tempSrcIata,LEN);
	if(!(checkIfValideIata(tempSrcIata))){
		free(flight);
		return NULL;
	}

	int flag =0;
	int isValid;
	char tempDestIata[LEN+1];
	while(flag==0)
	{
		printf("Please enter flight destination Airport IATA code, make sure that the code exactly length of 3: \n");
		myGets(tempDestIata,LEN);
		isValid = checkIfValideIata(tempDestIata);
		if(isValid && ((strcmp(tempSrcIata,tempDestIata) !=0)))
		{
			flag =1;
		}
		else{
			printf("Invalid destination Airport IATA code... please try again \n");
		}
	}

	int isExist = checkIfIataCodeExist(manager,tempSrcIata);
	if(isExist==0)
	{
		printf("The entered departure IATA code does not exist\n");
		free(flight);
		return NULL;
	}

	isExist = checkIfIataCodeExist(manager,tempDestIata);
	if(isExist==0)
	{
		printf("The entered destination IATA code does not exist.. please try again\n ");
		free(flight);
		return NULL;
	}

	Clock *clock = NULL;
	while (clock==NULL)
	{
		clock=setTime();
	}

	Date* date = NULL;
	while (date==NULL)
	{
		date=setDate();
	}

	flight->iataCodeSrc=strdup(tempSrcIata);
	flight->iataCodeDest=strdup(tempDestIata);
	flight->clock=clock;
	flight->date=date;

	return flight;
}

int checkHowManyFlightsOnLine (Flight **allFlights,int allFlightSize ,char* iataCodeSrc, char* iataCodeDest)
{
	int count=0;
	int numOfMatchFlights=0;
	int sameSrc=1;
	int sameDest=1;

	while(count <allFlightSize)
	{
		char* flightSrc =(allFlights[count]->iataCodeSrc);
		char* flightDest = (allFlights[count]->iataCodeDest);
		sameSrc = strcmp(flightSrc, iataCodeSrc);
		sameDest = strcmp(flightDest , iataCodeDest);
		if(sameDest==0 && sameSrc==0)
		{
			numOfMatchFlights++;
		}
		count ++;
	}
	return numOfMatchFlights;

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

