/*
 * Functions.c
 *
 *  Created on: 11 Dec 2020
 *      Author: niv
 */


#include <stdio.h>
#include <string.h>
#include <ctype.h>
#include <stdlib.h>

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


void myBufferCleaner()
{
	while ((getchar()) != '\n')
			 {
			 }
}

char* getStringInLowerCaseAndWordIndexs(int* numOfWords ,int** wordsIndexes)
/*
 *
 * this function get string from the user char by char and make each char lower case
 * the function also make sure that of the string contain " " (spaces)
 * if its single space the function will double him and if the string contain more then
 * 2 spaces and row it take them of and keep only 2 spaces.
 * the function return the string and fill in the 2 pointers the number of words in the string
 * and the index of the first letter of of word in the wordsIndexes array;
 *
 * */
{
	printf("Please enter airport name: \n");
	char tempName[255];
	char tempChar = getchar();
	if (tempChar==' ')
	{
		printf("Name can not start with space! please try again...\n");
		return NULL;

	}
	int* tempWordIndex = (int*)malloc(10 * sizeof(int));
	*numOfWords=1;
	int i=0;
	int flag=1;
	while(tempChar != '\n')
	{
		if(tempChar!=' ')
		{
			tempName[i++]=tolower(tempChar);
			tempChar=getchar();
			flag =1;
		}
		else if(tempChar==' ' && flag)
		{

			*(tempWordIndex + (*numOfWords))=(i+2);
			tempName[i++]=' ';
			tempName[i++]=' ';
			flag =0;
			tempChar=getchar();
			*numOfWords = *numOfWords+1;
		}
		else
			tempChar=getchar();
	}
	if(*numOfWords>1)
		*numOfWords=*numOfWords-1;
	char* name=strdup(tempName); //this function do dynamic allocation make sure the free "name"
	*wordsIndexes = tempWordIndex; //make sure to free wordIndexes
	return name;

}


int firstLetterUpper(char** string ,const int numOfWord ,const int* wordsIndexes)
{
	/*
	 *
	 * this part change the first latter of each word to upperCase;
	 * the string pass with operator ** because one * for char array
	 * and the second * for passing argument by reference
	 *
	 * */

	for(int i=0 ; i<numOfWord-1 ; i++)
	{
		*(*string+wordsIndexes[i])=toupper(*(*string+wordsIndexes[i]));
	}
	return 1;
}

int* getWordsSizeArr(const char* string,const int numOfWord)
{

	/*
	 *
	 * this function store at wordSize array the size of each word of the name
	 * count assuming each word in string separated by two spaces
	 *
	 * */

	int* wordSize= (int*)malloc(sizeof(int)*numOfWord);
	int wordCounter=0;
	int startWordIndex=0;

	for(int k=0; k<strlen(string);k++)
	{
		if(string[k]==' ' && string[k-1] == ' ')
		{
			if(wordCounter==0)
			{
				wordSize[wordCounter]=k-1;
				startWordIndex+=k;
			}
			else
			{
				wordSize[wordCounter]=k-startWordIndex-2;
				startWordIndex =k;
			}
			wordCounter++;
		}

	}
	return wordSize;
}

int makeOneBigOneSmallIfEven(char** string , const int* wordSizes ,const int* wordsIndexes, const int numOfWords)
/*
 *
 *  this function check if the each word length is even
 *  and if true change the word as follows: "AaBjDcXy......Zx"
 *
 * */
{

	for (int i = 0; i <= numOfWords; i++) {
		if (wordSizes[i] % 2 == 0) {
			int firstWordIndex;
			int lastWordIndex;

			if (i == 0)
				firstWordIndex = 0;
			else
				firstWordIndex = wordsIndexes[i];

			if (i == numOfWords)
				lastWordIndex = strlen(*string);

			else
				lastWordIndex = wordsIndexes[i + 1] - 2;

			for (int j = firstWordIndex; j < lastWordIndex; j += 2) {
				*(*string+j) = toupper(*(*string+j));
			}
		}

	}
	return 1;
}


int avoidFormSpacesAtEnd(char** string)
/*
 *
 * this function make sure that the name wont end with spaces
 *
 * */
{
	int tempNameSize = strlen(*string);

	while(*(*string+(tempNameSize-1))==' ')
	{
		*(*string+tempNameSize-1)='\0';
		tempNameSize--;
	}

	return 1;
}
