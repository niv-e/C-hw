/*
 * Date.h
 *
 *  Created on: 13 Dec 2020
 *      Author: niv
 */

#ifndef DATE_H_
#define DATE_H_

#define DATE_LEN 11
typedef struct
{
	int day;
	int month;
	int year;

}Date;


Date* setDate();
void printDate(const Date *date);

#endif /* DATE_H_ */
