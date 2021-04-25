#define _CRT_SECURE_NO_WARNINGS
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <stdarg.h>
#include "Company.h"
#include "Airport.h"
#include "General.h"
#include "fileHelper.h"
#include "main.h"
#include "myMacros.h"



static const char* sortOptStr[eNofSortOpt] = {
	"None","Hour", "Date", "Airport takeoff code", "Airport landing code" };


int	initCompanyFromFile(Company* pComp, AirportManager* pManaer, const char* fileName)
{
	L_init(&pComp->flighDateList);
	if (loadCompanyFromFile(pComp, pManaer, fileName))
	{
		initDateList(pComp);
		return 1;
	}
	return 0;
}

void	initCompany(Company* pComp,AirportManager* pManaer)
{
	printf("-----------  Init Airline Company\n");
	L_init(&pComp->flighDateList);
	
	pComp->name = getStrExactName("Enter company name");
	pComp->flightArr = NULL;
	pComp->flightCount = 0;
}

void	initDateList(Company* pComp)
{	
	for (int i = 0; i < pComp->flightCount; i++)
	{
		if(isUniqueDate(pComp,i))
		{
			char* sDate = createDateString(&pComp->flightArr[i]->date);
			L_insert(&(pComp->flighDateList.head), sDate);
		}
	}
}

int		isUniqueDate(const Company* pComp, int index)
{
	Date* pCheck = &pComp->flightArr[index]->date;
	for (int i = 0; i < pComp->flightCount; i++)
	{
		if (i == index)
			continue;
		if (equalDate(&pComp->flightArr[i]->date,pCheck))
			return 0;
	}
	return 1;
}

int		addFlight(Company* pComp, const AirportManager* pManager)
{

	if (pManager->count < 2)
	{
		printf("There are not enoght airport to set a flight\n");
		return 0;
	}
	pComp->flightArr = (Flight**)realloc(pComp->flightArr, (pComp->flightCount + 1) * sizeof(Flight*));
	if (!pComp->flightArr)
		return 0;
	pComp->flightArr[pComp->flightCount] = (Flight*)calloc(1, sizeof(Flight));
	if (!pComp->flightArr[pComp->flightCount])
		return 0;
	initFlight(pComp->flightArr[pComp->flightCount], pManager);
	if (isUniqueDate(pComp, pComp->flightCount))
	{
		char* sDate = createDateString(&pComp->flightArr[pComp->flightCount]->date);
		L_insert(&(pComp->flighDateList.head), sDate);
	}
	pComp->flightCount++;
	return 1;
}

void	printCompany(const Company* pComp, char* str, ...)
{
	va_list allWords;
	char* currentWord;
	char* delimiter = "_";

	va_start(allWords, str);
	currentWord = str;
	while (currentWord != NULL)
	{
		printf("%s", currentWord);
		currentWord = va_arg(allWords, char*);
		if(currentWord != NULL)
			printf("%s", delimiter);
	}
	va_end(allWords);

	printf("\nHas %d flights\n", pComp->flightCount);
	generalArrayFunction((void*)pComp->flightArr, pComp->flightCount, sizeof(Flight**), printFlightV);
	printf("\nFlight Date List:");
	L_print(&pComp->flighDateList, printStr);
}

void	printShortCompany(const Company* pComp, char* str, ...)
{
	va_list allWords;
	char* currentWord;
	char* delimiter = "_";

	va_start(allWords, str);
	currentWord = str;
	while (currentWord != NULL)
	{
		printf("%s", currentWord);
		currentWord = va_arg(allWords, char*);
		if (currentWord != NULL)
			printf("%s", delimiter);
	}
	va_end(allWords);
	printf("\nHas %d flights\n", pComp->flightCount);
}

void	macroPrintCompany(const Company* pComp, char* str)
{
#ifdef DETAIL_PRINT
		printCompany(pComp, str, "Hachi", "Babit", "Ba", "Olam", NULL);
#else
		printShortCompany(pComp, str, "Hachi", "Babit", "Ba", "Olam", NULL);
#endif
}



void	printFlightsCount(const Company* pComp)
{
	char codeOrigin[CODE_LENGTH + 1];
	char codeDestination[CODE_LENGTH + 1];

	if (pComp->flightCount == 0)
	{
		printf("No flight to search\n");
		return;
	}

	printf("Origin Airport\n");
	getAirportCode(codeOrigin);
	printf("Destination Airport\n");
	getAirportCode(codeDestination);

	int count = countFlightsInRoute(pComp->flightArr, pComp->flightCount, codeOrigin, codeDestination);
	if (count != 0)
		printf("There are %d flights ", count);
	else
		printf("There are No flights ");

	printf("from %s to %s\n", codeOrigin, codeDestination);
}

int		saveCompanyToFile(const Company* pComp, const char* fileName)
{
	FILE* fp;
	fp = fopen(fileName, "wb");

	CHECK_RETURN_0(fp);


	#ifdef COMPERSS

		BYTE data[2] = { 0 };  // array for the flight count , sort option and airLine name length..
							   // flight count bit: 15-7 | sort option bits: 4-6 | name length: 3-0

		data[1] = pComp->flightCount >> 1;
		data[0] = (pComp->flightCount | 0x80) << 7;
		data[0] = data[0] | (pComp->sortOpt & 0x7) << 4;
		data[0] = data[0] | strlen(pComp->name) & 0xf;

		// Wrtie to file the details: flight count , sortType, airline name length ;
		if (fwrite(data, sizeof(BYTE), 2, fp) != 2) { fclose(fp); return 0; }
		if (fwrite(pComp->name, sizeof(BYTE), strlen(pComp->name) + 1, fp) != strlen(pComp->name) + 1)  MSG_CLOSE_RETURN_0(fp);
		for (int i = 0; i < pComp->flightCount; i++)
		{
			int flightData = 0;
			if (fwrite(pComp->flightArr[i]->originCode, sizeof(BYTE), 3, fp) != 3) MSG_CLOSE_RETURN_0(fp);
			if (fwrite(pComp->flightArr[i]->destCode, sizeof(BYTE), 3, fp) != 3) MSG_CLOSE_RETURN_0(fp);

			flightData = flightData | pComp->flightArr[i]->date.year << 14;

			flightData = flightData | pComp->flightArr[i]->date.month << 10;

			flightData = flightData | pComp->flightArr[i]->date.month << 5;

			flightData = flightData | pComp->flightArr[i]->hour;

			if (fwrite(&flightData, sizeof(BYTE), 4, fp) != 4) { fclose(fp); return 0; }
		}

	#else

		CHECK_0_MSG_COLSE_FILE(writeStringToFile(pComp->name, fp, "Error write comapny name\n"), fp);

		CHECK_0_MSG_COLSE_FILE(writeIntToFile(pComp->flightCount,fp , "Error write flight count\n"), fp);

		CHECK_0_MSG_COLSE_FILE(writeIntToFile((int)pComp->sortOpt, fp, "Error write sort option\n"), fp);

		for (int i = 0; i < pComp->flightCount; i++)
		{
			if (!saveFlightToFile(pComp->flightArr[i], fp))
				return 0;
		}

	#endif

		fclose(fp);
		return 1;
}

int		readCompressCompanyDetails(Company* pComp, FILE* file)
{
	BYTE data[2] = { 0 };  // array for the flight count , sort option and airLine name length..
						   // flight count bit: 15-7 | sort option bits: 4-6 | name length: 3-0

	//reading 2 bytes to to data.
	if ((fread(data, sizeof(BYTE), 2, file) != 2)) { fclose(file); return 0; }

	//reading the first 8 bits of the flight count. (high bits)
	int tFlightCount = data[1];
	tFlightCount = tFlightCount << 1;
	tFlightCount = tFlightCount | (data[0] >> 7);
	pComp->flightCount = tFlightCount;

	int tSortOption = 0;
	tSortOption = data[0] & 0x70; //0x70 = 01110000 binary.
	tSortOption = tSortOption >> 4;
	pComp->sortOpt = tSortOption;

	int tAirlineNameLength = 0;
	tAirlineNameLength = data[0] & 0xf;


	BYTE nameT[5] = { 0 };

	if ((fread(nameT, sizeof(BYTE), 5, file) != 5)) { fclose(file); return 0; }
	pComp->name = (char*)malloc(sizeof(char)* tAirlineNameLength+1);
	strcpy(pComp->name, nameT);
	pComp->flightArr = (Flight**)malloc(sizeof(Flight*)*pComp->flightCount);
	L_init(&pComp->flighDateList);
	return 1;

}

int		readCompressFlightDetails(Company* pComp, FILE* file)
{
	/*
	*	Make sure that you use this function ONLY after "readCompressCompanyDetails"
	*/
	int codeLen = CODE_LENGTH + 1;
	int tFlightBuff = 0;


	for (int i = 0; i < pComp->flightCount; i++)
	{
		pComp->flightArr[i] = (Flight*)malloc(sizeof(Flight));
		char* destCode = (char*)malloc(sizeof(char)* codeLen);
		char* originCode = (char*)malloc(sizeof(char)* codeLen);

		if ((fread(originCode, sizeof(BYTE), CODE_LENGTH, file) != CODE_LENGTH)) { fclose(file); free(pComp->flightArr[i]);	 return 0; }
		strcpy(pComp->flightArr[i]->originCode, originCode);
		pComp->flightArr[i]->originCode[3] = '\0';

		if ((fread(destCode, sizeof(BYTE), CODE_LENGTH, file) != CODE_LENGTH)) { fclose(file); free(pComp->flightArr[i]);	 return 0; }
		strcpy(pComp->flightArr[i]->destCode, destCode);
		pComp->flightArr[i]->destCode[3] = '\0';

		if ((fread(&tFlightBuff, sizeof(BYTE), 4, file) != 4)) { fclose(file); free(pComp->flightArr[i]);	 return 0; }

		pComp->flightArr[i]->date.year = tFlightBuff >> 14;

		pComp->flightArr[i]->date.month = (tFlightBuff >> 10) & 0xf;

		pComp->flightArr[i]->date.day = (tFlightBuff >> 5) & 0x1f;

		pComp->flightArr[i]->hour = tFlightBuff & 0x1f;

	}
	return 1;
}

int		loadCompanyFromFile(Company* pComp, const AirportManager* pManager, const char* fileName)
{
	FILE* fp = fopen(fileName, "rb");
	CHECK_RETURN_0(fp);

	#ifdef COMPERSS

	// init the company from compressed binaray file ( flightsCount, sortType , name , and init flightArr)
	readCompressCompanyDetails(pComp, fp); 

	/*------------- reading fights -------------*/
	readCompressFlightDetails(pComp, fp);
	

	#else
	
		pComp->name = readStringFromFile(fp, "Error reading company name\n");
		if (!pComp->name)
			return 0;

		if (!readIntFromFile(&pComp->flightCount, fp, "Error reading flight count name\n"))
			return 0;

		int opt;
		if (!readIntFromFile(&opt, fp,"Error reading sort option\n"))
			return 0;

		pComp->sortOpt = (eSortOption)opt;

		if (pComp->flightCount > 0)
		{
			pComp->flightArr = (Flight**)malloc(pComp->flightCount * sizeof(Flight*));
			if (!pComp->flightArr)
			{
				printf("Alocation error\n");
				fclose(fp);
				return 0;
			}
		}
		else
			pComp->flightArr = NULL;

		for (int i = 0; i < pComp->flightCount; i++)
		{
			pComp->flightArr[i] = (Flight*)calloc(1, sizeof(Flight));
			if (!pComp->flightArr[i])
			{
				printf("Alocation error\n");
				fclose(fp);
				return 0;
			}
			if (!loadFlightFromFile(pComp->flightArr[i], pManager, fp))
				return 0;
		}


	#endif // COMPERSS
		fclose(fp);
		return 1;

}

void	sortFlight(Company* pComp)
{
	pComp->sortOpt = showSortMenu();
	int(*compare)(const void* air1, const void* air2) = NULL;

	switch (pComp->sortOpt)
	{
	case eHour:
		compare = compareByHour;
		break;
	case eDate:
		compare = compareByDate;
		break;
	case eSorceCode:
		compare = compareByCodeOrig;
		break;
	case eDestCode:
		compare = compareByCodeDest;
		break;
	
	}

	CHECK_RETURN_NULL(compare); // switch the if statment
	qsort(pComp->flightArr, pComp->flightCount, sizeof(Flight*), compare);

}

void	findFlight(const Company* pComp)
{
	int(*compare)(const void* air1, const void* air2) = NULL;
	Flight f = { 0 };
	Flight* pFlight = &f;


	switch (pComp->sortOpt)
	{
	case eHour:
		f.hour = getFlightHour();
		compare = compareByHour;
		break;
	case eDate:
		getchar();
		getCorrectDate(&f.date);
		compare = compareByDate;
		break;
	case eSorceCode:
		getchar();
		getAirportCode(f.originCode);
		compare = compareByCodeOrig;
		break;
	case eDestCode:
		getchar();
		getAirportCode(f.destCode);
		compare = compareByCodeDest;
		break;
	}

	if (compare != NULL)
	{
		Flight** pF = bsearch(&pFlight, pComp->flightArr, pComp->flightCount, sizeof(Flight*), compare);
		if (pF == NULL)
			printf("Flight was not found\n");
		else {
			printf("Flight found, ");
			printFlight(*pF);
		}
	}
	else {
		printf("The search cannot be performed, array not sorted\n");
	}

}

eSortOption showSortMenu()
{
	int opt;
	printf("Base on what field do you want to sort?\n");
	do {
		for (int i = 1; i < eNofSortOpt; i++)
			printf("Enter %d for %s\n", i, sortOptStr[i]);
		scanf("%d", &opt);
	} while (opt < 0 || opt >eNofSortOpt);

	return (eSortOption)opt;
}

void	freeCompany(Company* pComp)
{
	generalArrayFunction((void*)pComp->flightArr, pComp->flightCount, sizeof(Flight**), freeFlight);
	free(pComp->flightArr);
	free(pComp->name);
	L_free(&pComp->flighDateList, freePtr);
}


