/*
	finfo: file info get, check, show..

	Zhang Lihui <swordhuihui@gmail.com>
	2011.11.10
*/

#ifndef __SWORD_FINFO_H
#define __SWORD_FINFO_H

typedef struct
{
	char			type;
	const char*		pName;
	long int		size;
	long int		lastModTime;
	int				mask;
	unsigned short	uid;
	unsigned short	gid;
	char			csMD5[128];

}FINFO;

#define FINFO_CMP_FAIL_TYPE	(1<<0)
#define FINFO_CMP_FAIL_SIZE	(1<<1)
#define FINFO_CMP_FAIL_TIME	(1<<2)
#define FINFO_CMP_FAIL_MASK	(1<<3)
#define FINFO_CMP_FAIL_UID	(1<<4)
#define FINFO_CMP_FAIL_GID	(1<<5)
#define FINFO_CMP_FAIL_MD5	(1<<6)

#define FINFO_CKMASK_BASE (FINFO_CMP_FAIL_TYPE | FINFO_CMP_FAIL_MASK \
		| FINFO_CMP_FAIL_UID | FINFO_CMP_FAIL_GID)

#define FINFO_CKMASK_DIR (FINFO_CKMASK_BASE)
#define FINFO_CKMASK_LINK (FINFO_CKMASK_BASE | FINFO_CMP_FAIL_TIME)
#define FINFO_CKMASK_FILE (FINFO_CKMASK_BASE | FINFO_CMP_FAIL_MD5 | \
	FINFO_CMP_FAIL_TIME)

int finfo_get(const char* pName, FINFO* pInfo);
int finfo_getFromCSVSeg(const char* segs[], int iMaxSeg, FINFO* pInfo);
int finfo_show(const char* pName, FINFO* pInfo);
int finfo_cmp(FINFO* src, FINFO* dst, int ckmask);

	
#endif //__SWORD_FINFO_H
