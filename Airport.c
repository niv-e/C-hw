/*
 * Airport.c
 *
 *  Created on: 10 Dec 2020
 *      Author: niv
 */

#include <stdio.h>
#include <string.h>
#include <ctype.h>
#include <stdlib.h>



#include "Airport.h"
#include "Functions.h"

/**
check if pFirst and pSecond have the same IATA code;
**/
int	checkIfAirportsAreSame(Airport* pFirst , Airport* pSecond)
{
	if(pFirst->iata == pSecond->iata)
	{
		return 1;
	}
	return 0;
}



/**
check if the airport IATA code are same as the IATA code that insert ;
**/
int	checkIATACode(Airport* pAirport , const char* iataCode)
{
	if(strcmp(pAirport->iata, iataCode))
	{
		return 1;
	}
	return 0;
}

int setAirportName(Airport* pAirport)
{
	int numOfWordsInName;
	int* wordsIndexes=NULL;
	char * airportName = getStringInLowerCaseAndWordIndexs(&numOfWordsInName,&wordsIndexes);

	firstLetterUpper(&airportName, numOfWordsInName, wordsIndexes);

	int* wordSizes = getWordsSizeArr(airportName,numOfWordsInName);

	makeOneBigOneSmallIfEven(&airportName , wordSizes ,wordsIndexes, numOfWordsInName);

	avoidFormSpacesAtEnd(&airportName);

	pAirport->name=airportName;

	free(wordsIndexes);//this array was just for the name format;
	return 1;
}



int setAirportCountry(Airport* pAirport)
{
	printf("Please enter airport country: \n");
	getchar();//clean the buffer

	char tempCountry[LEN];
	myGets(tempCountry, LEN);
	if(isspace(tempCountry[0]))
		return 0;
	int tempSize = sizeof(tempCountry)/sizeof(tempCountry[0]);
	if(tempSize==0)
	{
			return 0;
	}
	pAirport->country = strdup(tempCountry);

	return 1;

}

int checkIfValideIata(const char* iata)
{
	int tempSize = strlen(iata);
	if(tempSize!=3)
	{
		printf("Invalid IATA code... make sure that the length of the code no more the 3.\n");
		return 0;
	}

	for(int i=0 ; i<3;i++)
	{
		int res;
		res = islower(iata[i]);
		if(res)
		{
			printf("Invalid IATA code.. make sure that you insert the code in upper case\n");
			return 0;

		}
	}
	return 1;

}


int setAirpotIata(Airport* pAirport)
{
	printf("Please enter airport IATA code, make sure that the code exactly length of 3: \n");
	char tempIata[LEN];
	myGets(tempIata,LEN);

	if(checkIfValideIata(tempIata))
	{
		pAirport->iata=strdup(tempIata);
		return 1;
	}

	return 0;

}

/*
 this function make sure that the set name, counter and code performed successfully
 * */
Airport* initAirport()
{

	Airport *airport = (Airport*)malloc(sizeof(Airport));
	int countryFlag , nameFlag ,iataFlag;

	countryFlag = setAirportCountry(airport);
	if(!(countryFlag))
		{
			printf("Invalid country please try again.. \n");
			free(airport);
			return NULL;
		}
	nameFlag = setAirportName(airport);
	iataFlag= setAirpotIata(airport);

	if(!( nameFlag && iataFlag))
	{
		printf("Placement failed ,some fields are missing please try again.. \n");
		free(airport);
		return NULL;
	}
	return airport;
}

void printAirportDetails(Airport* pAirport)
{
	printf("Airport name: %s\n",pAirport->name);
	printf("Airport country: %s\n",pAirport->country);
	printf("Airport IATA code: %s\n",pAirport->iata);

}

void freeAirport(Airport* airport)
{
	free(airport->country);
	free(airport->name);
	free(airport->iata);
}
