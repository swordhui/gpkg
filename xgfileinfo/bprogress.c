
#include <stdio.h>
#include <string.h>
#include "bprogress.h"


static int f_iLastStrLen=0;

int bp_init()
{
	f_iLastStrLen=0;
}

void bp_clear()
{
	char csBack[80];	

	if(f_iLastStrLen)
	{
		memset(csBack, '\b', f_iLastStrLen);
		csBack[f_iLastStrLen]=0;
		printf(csBack);
		f_iLastStrLen=0;
	}
}

void bp_printf(const char* s)
{
	f_iLastStrLen=strlen(s);
	printf("%s", s);
}


