/*
 * Flight.h
 *
 *  Created on: 13 Dec 2020
 *      Author: niv
 */

#ifndef FLIGHT_H_
#define FLIGHT_H_

#include "AirportManager.h"
#include "Clock.h"
#include "Date.h"
#include <stdio.h>

typedef struct
{
	char* iataCodeSrc;
	char* iataCodeDest;
	Clock* clock;
	Date* date;
}Flight;

Flight* initFlight(AirportManager* manager);
int checkIfFlightLandingAtDest(Flight flight ,char* iataCodeSrc, char* iataCodeDest);
void printFlightDetails(Flight* flight);
void freeFlight(Flight* flight);
int checkHowManyFlightsOnLine (Flight **allFlights,int allFlightSize ,char* iataCodeSrc, char* iataCodeDest);


#endif /* FLIGHT_H_ */
