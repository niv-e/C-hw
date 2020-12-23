/*
 * exe.c
 *
 *  Created on: 13 Dec 2020
 *      Author: niv
 */

#include "exe.h"
#include "Functions.h"
#include "Airline.h"
#include "Flight.h"



void runMenu()
{
	printf("1. Add flight to airline:\n");
	printf("2. Add Airport to airport manager:\n");
	printf("3. Print airline details:\n");
	printf("4. Print airport manager details:\n");
	printf("5. Check how many flights are between two airports:\n");
	printf("6. exit and free the dynamic allocations :\n");
}

void runSelectedOption(int optionNumber ,AirportManager *manager,Airline *airline)
{
	switch(optionNumber)
	{
	   case 1 :;
	   	   Flight* flight = initFlight(manager); //this function return flight after malloc
		   if(flight){
		   	   addFlightToAirline(airline, flight);
			   printAirline(airline);
		   }
		   break;

	   case 2 :;

		   Airport *airport = NULL;
		   while(!airport){
			   airport=initAirport();
		   }
		   int isExist = checkIfIataCodeExist(manager,airport->iata);
		   while(isExist)
		   {
			   printf("The entered airport already exist.. please try again\n");
			   airport=initAirport();
			   isExist = checkIfIataCodeExist(manager,airport->iata);
		   }
		   addNewAirport(manager, airport);
		   break;

	   case 3 :;
		   printAirline(airline);
		   break;

	   case 4 :;
		   printAirportManager(manager);
		   break;


	   case 5 :;
			printf("Please enter departure Airport IATA code:\n");
			getchar();
			char tempSrcIata[LEN];
			myGets(tempSrcIata,LEN);
			char tempDestIata[LEN];
			printf("Please enter destination Airport IATA code:\n");
			myGets(tempDestIata,LEN);

			int numOfFlightsOnLine = checkHowManyFlightsOnLine(airline->allFlights,airline->numOfFlights, tempSrcIata, tempDestIata);
			printf("The number of flights that departure from %s and landing at %s is: %d\n",
					tempSrcIata,
					tempDestIata,
					numOfFlightsOnLine);
	   		break;

	   case 6 :;
	   	   freeAirportManager(manager);
	   	   freeAirLine(airline);
	   	   printf("The program was executed successfully");
	   	   break;
	}
}


