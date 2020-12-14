/*
 * exe.h
 *
 *  Created on: 13 Dec 2020
 *      Author: niv
 */

#ifndef EXE_H_
#define EXE_H_

#include "AirportManager.h"
#include "Airline.h"
#include <stdio.h>

void runMenu();
void runSelectedOption(int optionNumber ,AirportManager *manager,Airline *airline);
//void addFlightToAirline(AirportManager *manager, Airline *airline);

#endif /* EXE_H_ */
