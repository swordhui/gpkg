/*
	xgfileinfo: file record tool for Xiange Linux package management system
	file_info.c: main program of xgfileinfo

	by Pinkme005 @ LinuxSir (First version)
	Modified by Zhang Lihui <swordhuihui@gmail.com>
*/
	
#include "stdio.h"
#include "string.h"
#include <stdlib.h>
#include <sys/stat.h>
#include <unistd.h>
#include <time.h>

extern  int MDFile(const char *pName, char* pMd5Sum, int iBufLen);

#define MAX_NAME_LEN    (4096)
#define FILE_MODE_MASK 	0x1FF 
#define TIME_MODIFY_BUF	26
#define	MD5		5
#define	SHA256		256

int get_info(char* csFileName);

static long long f_llFileSize=0;
static long 	f_lDiskUsage=0;
static int	f_iDCount=0;
static int	f_iFCount=0;
static int	f_iSCount=0;
const char *applet_name;

/*
	Arguments 
	   -cm		check the file using md5 module
	   -cs		check the file using shax module (reserved space)
	   -f		filename list (optional,for losts of files)
	   filename 	single file (default use)
 */   

int main(argc,argv)
int argc;
char **argv;	
{
		char    *pRet=NULL;
		char    csName[MAX_NAME_LEN];
		int     count=0;
		int     len,i,verify_mode;

	applet_name = argv[0];

	#if 0
	if(argc>1)
	for(i=1;i<argc;i++)
		if(argv[i][0]=='-')
		{
			get_info(argv[i+1]);
			/* use MD5 check */
			if(strcmp(&argv[i][1],"cm")==0)
			  {
				MDFile(argv[i+1]);
				return 0;
			   }
			/* reserve other check module entry in here */
			else
				return 0;
		}
			/* do nothing but get file info */
		else
		{
			get_info(argv[i]);
			return 0;
		}
	}
	#endif

        while(1)
        {
                pRet=fgets(csName, MAX_NAME_LEN, stdin);
                if(NULL == pRet) break;

                //remove \n
                len=strlen(csName);
                if(csName[len-1] == '\n') csName[len-1]=0;

		//remov "."
		if(strcmp(csName, ".") == 0) continue;

                //to stdout.
                get_info(csName);
                count++;
        }

	//Show info. I,Fcount,Dcount,Scount,SpaceUsage,ReadSize
	printf("I,%d,%d,%d,%ld,%d\n", f_iFCount, f_iDCount, f_iSCount,
		f_lDiskUsage/2, (int)((f_llFileSize-1)/1024+1));

        return 0;
}

//routine for get file information, such as file tye, file Last Modify Time,
//file mode, file size, file md5 checksum, and output to stdout.
// file type:  'D' Directory. 'S' Symbol link. 'F' -- Normal file.
// if file type is 'F', then output name, mode, LMT, size,  md5checksum.
// if 'D', output name, mode, LMT
// if 'S', output name, mode, LMT, link destination.
int get_info(char* csFileName)
{
	struct stat 	info;
	int 		mask_test;
	long int	t_modify;
        long int	iTestSize;
        char            csTestSum[128];
	char		*pOutName;

        //type 'F' , name, mode, LMT, size, cksum
	//printf("file name is :%s\n",csFileName);
	if(lstat(csFileName,&info)!=0)
	{
		//printf("File is not exist!\n");
		return (1);
	}

	//remove leading . for output.
	pOutName=(csFileName[0] == '.' ? csFileName+1 : csFileName);

	iTestSize=info.st_size;
	t_modify=info.st_mtime;
	mask_test=info.st_mode;

	//csLMT=ctime(&t_modify);
	//get type.
	if(S_ISLNK(info.st_mode))
	{
		//Links. output "S,Name,Size,Mask,LMT
		printf("S,%s,%d,%04o,%d,%d,%d\n", pOutName, iTestSize,
			mask_test&FILE_MODE_MASK, info.st_uid, info.st_gid,
			t_modify);

		f_iSCount++;
		f_lDiskUsage+=info.st_blocks;
			
	}
	else if(S_ISDIR(info.st_mode))
	{
		//Dir, output "D,Name,Size,Mask,LMT
		printf("D,%s,%d,%04o,%d,%d,%d\n", pOutName, iTestSize,
			mask_test&FILE_MODE_MASK, info.st_uid, info.st_gid,
			t_modify);

		f_iDCount++;
		f_lDiskUsage+=info.st_blocks;
	}
	else
	{
		//get md5 sum
		MDFile(csFileName, csTestSum, 128);

		//file, output "F,Name,Size,Mask,uid, gid,LMT,Md5Sum
		printf("F,%s,%d,%04o,%d,%d,%d,%s\n", pOutName, iTestSize,
			mask_test&FILE_MODE_MASK, info.st_uid, info.st_gid,
			t_modify, csTestSum);

		f_iFCount++;
		f_lDiskUsage+=info.st_blocks;
		f_llFileSize+=iTestSize;
	}

	return 0;
}

void bb_show_usage(void)
{   
	//fputs(APPLET_full_usage "\n", stdout);
	exit(EXIT_FAILURE);
}

