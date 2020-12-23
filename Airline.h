/*
 * Airline.h
 *
 *  Created on: 13 Dec 2020
 *      Author: niv
 */

#ifndef AIRLINE_H_
#define AIRLINE_H_

#define NAME_LEN 50

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "Flight.h"

typedef struct
{
	Flight **allFlights;
	char* name;
	int numOfFlights;

}Airline;

int setAirlineName(Airline *airline);
int initAirline(Airline *airline);
int addFlightToAirline(Airline *airline , Flight *flight);
void printAirline(Airline* airline);
void freeAirLine(Airline* airline);

#endif /* AIRLINE_H_ */
