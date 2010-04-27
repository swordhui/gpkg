prefix=
BASH_PATH=${prefix}/bin
CC=gcc
CFLAGS=-O2
DESTDIR=

all: xgfileinfo
	@echo "Done"


xgfileinfo: FORCE
	make -C xgfileinfo

install: xgfileinfo
	@echo "Install to ${DESTDIR}, bash is at ${BASH_PATH}"
	@mkdir -p ${DESTDIR}${prefix}/bin
	@cp gpkg ${DESTDIR}${prefix}/bin
	@cp xgfileinfo/xgfileinfo ${DESTDIR}${prefix}/bin
	@sed -i "s@^\#\!/bin@\#\!${BASH_PATH}@" ${DESTDIR}${prefix}/bin/gpkg
	@chmod a+x ${DESTDIR}${prefix}/bin/gpkg 
	@chmod a+x ${DESTDIR}${prefix}/bin/xgfileinfo 
	@echo "Done"

test: FORCE
	@bash gpkg selftest
	

testinst: FORCE
	@mkdir ./test
	make DESTDIR=./test prefix=/usr  install
	@echo "Done"

clean: FORCE
	make -C xgfileinfo clean
	rm -rf ./test
	@echo "Done"

FORCE:

