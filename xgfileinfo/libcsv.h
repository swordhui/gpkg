/*
	cvs file parser library

	by sword <szhang@vetronicsltd.com.cn>
	2011-10-18 15:15

*/

#ifndef __SWORD_LIBCSV_H
#define __SWORD_LIBCSV_H

//callback define.
typedef int (*LIBCSV_CALLBACK)(int iIndex, int iLineNum, char* pLine);



//init libcsv.
int libcsv_init(void);

//parse csv file, call callback function if get a new line. 
int libcsv_parse(const char* filename, LIBCSV_CALLBACK onNewLine);

//brack line to segs
int libcsv_getseg(char* pLine, const char* pSeg[], int maxseg);



#endif //__SWORD_LIBCSV_H


