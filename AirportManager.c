/*
 * AirportManager.c
 *
 *  Created on: 10 Dec 2020
 *      Author: niv
 */

#include "AirportManager.h"
#include "Airport.h"

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>

int initAirportManager(AirportManager *manager)
{
	int numOfAirports=0;
	manager->numberOfCurrentAirports=0;

	printf("Initializing the Airport manager\n");
	printf("Please enter how many airport you would like to add: \n");
	scanf("%d",&numOfAirports);
	while(numOfAirports==0){
		printf("Invalid index! make sure that you entered a number!..\n");
		printf("Please try again..\n");
	    while ((getchar()) != '\n'){}
		scanf("%d",&numOfAirports);

	}
//    char ch = getchar(); //clean the \n


	manager->allAirports = (Airport*)malloc(numOfAirports*sizeof(Airport));

	int count=0;
	while(count<numOfAirports)
	{
		Airport* tempAirport = initAirport();
		if(tempAirport)
		{
			addNewAirport(manager, tempAirport);
			count++;
		}
	}

	return 1;
}


int addNewAirport(AirportManager *manager , const Airport *airport)
{
	int numberOfCurrentAirports = manager->numberOfCurrentAirports;
	manager->allAirports=(Airport*)realloc(manager->allAirports,(numberOfCurrentAirports+1)*sizeof(Airport));
	manager->allAirports[numberOfCurrentAirports]=*airport;
	manager->numberOfCurrentAirports++;
	return 1;
}

Airport* getAirportByIataCode(AirportManager *manager, const char* iataCode)
{
	int i=0;
	while(i<manager->numberOfCurrentAirports)
	{
		int res =strcmp(manager->allAirports[i].iata,iataCode);
		if(res==0)
			return &manager->allAirports[i];
	}
	return NULL;
}

int checkIfIataCodeExist(AirportManager *manager , char* iataCode)
{
	int i=0;
	while(i< (manager->numberOfCurrentAirports))
	{
		int res =strcmp(manager->allAirports[i].iata,iataCode);
		if(res==0)
			return 1;
		i++;
	}
	return 0;

}


void printAirportManager(AirportManager *manager)
{
	printf("Number of current Airports\t%d\n",manager->numberOfCurrentAirports);
	int i =0;
	while(i<manager->numberOfCurrentAirports)
	{
		printAirportDetails(&(manager->allAirports[i]));
		printf("\n");
		i++;
	}
}

void freeAirportManager(AirportManager *manager)
{
	int count =0;
	while(count<manager->numberOfCurrentAirports)
	{
		freeAirport(&manager->allAirports[count++]);
	}

}


