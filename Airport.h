/*
 * Airport.h
 *
 *  Created on: 10 Dec 2020
 *      Author: niv
 */

#ifndef __Airport__
#define __Airport__

#define LEN 50
#define IATA_LEN 3


typedef struct
{
	char*	name;
	char*	country;
	char*	iata;
} Airport;

int checkIfValideIata(const char* iata);
int	checkIfAiportsAreSame(Airport* pFirst , Airport* pSecond);
int	checkIATACode(Airport* pAirport , const char* iataCode);
Airport* initAirport();
int setAirportName(Airport* pAirport);
int setAirportCountry(Airport* pAirport);
int setAirpotIata(Airport* pAirport);
void printAirportDetails(Airport* pAirport);
void freeAirport(Airport* airport);
#endif

