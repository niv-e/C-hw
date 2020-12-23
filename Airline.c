
#include "Airline.h"
#include <stdio.h>
#include <string.h>
#include <ctype.h>


#include "Airport.h"
#include "Functions.h"

int initAirline(Airline *airline)
{
	printf("Initializing the Airline\n");
	airline->numOfFlights=0;
	airline->allFlights=(Flight**)malloc(sizeof(Flight*)); // need to free

    if(!(airline->allFlights))
    {
        printf("Error! memory not allocated.");
        return 0;
    }



	int res;
	res = setAirlineName(airline);
	if(res)
		return 1;
	else
	{
		printf("Invalid name! please try again...\n");
		freeAirLine(airline);
		return 0;
	}

}

int setAirlineName(Airline *airline)
{
	printf("Please enter airline name: \n");
	char tempName[LEN];
	myGets(tempName, LEN);
	int tempSize = sizeof(tempName)/sizeof(tempName[0]);
	if(tempSize==0 ||isspace(*tempName)) //check if start with ' '
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
		free(airline->allFlights[count++]);
	}

}
