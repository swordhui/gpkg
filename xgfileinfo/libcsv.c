/*
	cvs file parser library

	by sword <szhang@vetronicsltd.com.cn>
	2011-10-18 15:15

*/

#include <stdio.h>
#include <string.h>
#include <stdlib.h>

#include "libcsv.h"

static char* trim_leadingspace(char* str)
{
	char* pret=str;

	while(pret && (*pret == ' ' || *pret == '\t')) pret++;

	return pret;
}

static char* trim_ending(char* str)
{
	int iLen=strlen(str);
	char* p=str+iLen-1;

	while(iLen && (*p == '\r' || *p == '\n'))
	{
		*p=0;
		p--;
		iLen--;
	}
	return str;
}

static void dumpseg(int iIndex, const char * pSeg[], int iMaxSeg)
{
	int i=0;
	if(iMaxSeg < 1 ) return;

	printf("[%4d] ", iIndex);
	for(i=0; i<iMaxSeg-1; i++)
		printf("S%d=%s, ", i, pSeg[i]);

	printf("S%d=%s\n", i, pSeg[i]);
}

int libcsv_init(void)
{
}


//parse file.
int libcsv_parse(const char* filename, LIBCSV_CALLBACK onNewLine)
{
	char buf[4096];
	FILE * pFile=NULL;
	int iRet=0;
	int	iLineNum=0;
	int iIndex=0;
	char* pline;

	//open file.
	pFile=fopen(filename, "r");
	if(pFile==NULL)
	{
		printf("[**Parse**] Open file %s failed.\n", filename);
		iRet=-1;
		goto ENDFUNC;
	}

	//parse file
	while(fgets(buf, 4096, pFile))
	{
		iLineNum++;

		//trim ending.
		trim_ending(buf);

		//trim leading space or tab.
		pline=trim_leadingspace(buf);


		//remove blank or comment line.
		if(buf[0] == 0 || buf[0]=='#') continue;

		//printf("%s\n", pline);

		//add it.
		onNewLine(iIndex, iLineNum, pline);

		iIndex++;
	}

	printf("Parse OK, %d line processed.\n", iLineNum);


ENDFUNC:
	if(pFile) fclose(pFile);
	return iRet;
}

//parse csv
int libcsv_getseg(char* src, const char* pSeg[], int maxseg)
{
	int iRet=0;
	char *pSegStart;
	while(*src)
	{
		//new seg
		if(maxseg == iRet) break;
		pSegStart=src;

		//trim leading space and record
		pSeg[iRet]=trim_leadingspace(pSegStart);

		if(maxseg-1 == iRet)
		{
			//last seg, to end.
			iRet++;
			continue;
		}

		//not the last, find \0 or ','
		while(*src && *src != ',') src++;
		if(*src==0)
		{
			// end with \0
		}
		else
		{
			//seg with ','
			*src=0;
			//src to next seg start.
			*src++;
		}

		iRet++;

	}

	return iRet;
}

