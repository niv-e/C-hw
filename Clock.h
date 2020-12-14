/*
 * Clock.h
 *
 *  Created on: 13 Dec 2020
 *      Author: niv
 */

#ifndef CLOCK_H_
#define CLOCK_H_

#define TIME_LEN 6

typedef struct
{
	int hours;
	int minutes;
}Clock;

int setHours(Clock *clock);
int setMinutes(Clock *clock);
Clock* setTime();
int checkValiadHours(int hours);
int checkValiadMinutes(int minutes);
void printTime(Clock *clock);



#endif /* CLOCK_H_ */
