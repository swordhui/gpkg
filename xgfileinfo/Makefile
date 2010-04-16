CC=gcc
CFLAGS=-O2


all: xgfileinfo
	@echo "Done"

sources=file_info.c md5.c mddriver.c
headers=global.h md5.h


xgfileinfo: ${sources}
	${CC} ${CFLAGS}  -o $@ ${sources}

clean:
	rm -f xgfileinfo
	
