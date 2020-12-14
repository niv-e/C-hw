/*
 * Functions.c
 *
 *  Created on: 11 Dec 2020
 *      Author: niv
 */


#include <stdio.h>
#include <string.h>
#include <ctype.h>

#include "Functions.h"

char* myGets(char* buf, size_t size)
{
	if(buf != NULL && size > 0)
	{
		if(fgets(buf,size,stdin))
		{
			buf[strcspn(buf,"\n")] = '\0';
			return buf;
		}
		*buf = '\0';
	}
	return NULL;

}






