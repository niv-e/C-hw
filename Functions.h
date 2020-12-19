/*
 * Functions.h
 *
 *  Created on: 11 Dec 2020
 *      Author: niv
 */

#ifndef FUNCTIONS_H_
#define FUNCTIONS_H_
#include <stdio.h>


char* myGets(char* buf, size_t size);
void myBufferCleaner();
char* getStringInLowerCaseAndWordIndexs(int* numOfWord ,int** wordsIndexes);
int firstLetterUpper(char** string ,const int numOfWord ,const int* wordsIndexes);
int* getWordsSizeArr(const char* string,const int numOfWord);
int makeOneBigOneSmallIfEven(char** string , const int* wordSizes ,const int* wordsIndexes, const int numOfWords);
int avoidFormSpacesAtEnd(char** string);

#endif /* FUNCTIONS_H_ */
