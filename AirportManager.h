/*
 * AirportManager.h
 *
 *  Created on: 10 Dec 2020
 *      Author: niv
 */

#ifndef AIRPORTMANAGER_H_
#define AIRPORTMANAGER_H_

#include "Airport.h"
#include "Airline.h"

typedef struct
{
	int numberOfCurrentAirports;
	Airport* allAirports;
} AirportManager;


int addNewAirport(AirportManager *manager , const Airport *airport);
Airport* getAirportByIataCode(AirportManager *manager, const char *iataCode);
int initAirportManager(AirportManager *manager);
void printAirportManager(AirportManager *manager);
int checkIfIataCodeExist(AirportManager *manager , char* iataCode);
void freeAirportManager(AirportManager *manager);


#endif /* AIRPORTMANAGER_H_ */


