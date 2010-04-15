CC_FLAG=-O2


all: xgfileinfo
	@echo "Done"

sources=file_info.c md5.c mddriver.c
headers=global.h md5.h


xgfileinfo: ${sources}
	gcc ${CC_FLAG}  -o $@ ${sources}

clean:
	rm -f xgfileinfo
	
