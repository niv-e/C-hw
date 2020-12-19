
#include "Airline.h"
#include <stdio.h>
#include <string.h>

#include "Airport.h"
#include "Functions.h"

int initAirline(Airline *airline)
{
	printf("Initializing the Airline\n");
	airline->numOfFlights=0;
	airline->allFlights=(Flight**)malloc(sizeof(Flight*)); // need to free
	int res;
	res = setAirlineName(airline);
	if(res)
		return 1;
	else
	{
		printf("Invalid name! please try again...\n");
		return 0;
	}

}

int setAirlineName(Airline *airline)
{
	printf("Please enter airline name: \n");
	char tempName[LEN];
	myGets(tempName, LEN);
	int tempSize = sizeof(tempName)/sizeof(tempName[0]);
	if(tempSize==0)
	{
				return 0;
	}
	airline->name=strdup(tempName);
	return 1;

}


int addFlightToAirline(Airline *airline , Flight *flight)
{
	int numOfCourrentFlight = airline->numOfFlights;
	airline->allFlights = (Flight**)realloc(airline->allFlights, (airline->numOfFlights+1)*sizeof(Flight*));
	airline->allFlights[numOfCourrentFlight]=flight;
	airline->numOfFlights ++;
	return 1;
}

int checkHowManyFlightsOnLine (Airline *airline ,char* iataCodeSrc, char* iataCodeDest )
{
	int numOfCourrentFlight = airline->numOfFlights;
	int count=0;
	int numOfMatchFlights;
	int sameSrc;
	int sameDest;

	while(count <numOfCourrentFlight)
	{
		sameSrc = strcmp(airline->allFlights[count]->iataCodeSrc , iataCodeSrc);
		sameDest = strcmp(airline->allFlights[count]->iataCodeDest , iataCodeDest);
		if(sameDest && sameSrc)
		{
			numOfMatchFlights++;
		}
		count ++;
	}
	return numOfMatchFlights;

}

void printAirline(Airline* airline)
{
	printf("Airline name:\t%s\n",airline->name);
	printf("Number of current flights:\t%d\n",airline->numOfFlights);

	int i =0;
	if(airline->numOfFlights==0)
	{
		printf("There is no flights at this moment..\n");
		return;
	}
	while(i<airline->numOfFlights)
	{
		printFlightDetails((airline->allFlights[i]));
//		printAirportDetails((airline->allFlights[i]));
		printf("\n");
		i++;
	}
}

void freeAirLine(Airline* airline)
{
	free(airline->name);
	int count =0;
	while(count<airline->numOfFlights)
	{
		free(airline->allFlights[count]);
	}

}
