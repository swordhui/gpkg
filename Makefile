prefix=
BASH_PATH=${prefix}/bin
CC_FLAG=-O2

all: xgfileinfo
	@echo "Done"


xgfileinfo: FORCE
	make -C xgfileinfo

install: FORCE
	@echo "Install to ${prefix}, bash is at ${BASH_PATH}"
	@mkdir -p ${prefix}/bin
	@cp gpkg ${prefix}/bin
	@cp xgfileinfo/xgfileinfo ${prefix}/bin
	@sed -i "s@^\#\!/bin@\#\!${BASH_PATH}@" ${prefix}/bin/gpkg
	@chmod a+x ${prefix}/bin/gpkg 
	@chmod a+x ${prefix}/bin/xgfileinfo 
	@echo "Done"

test: FORCE
	@mkdir ./test
	make prefix=./test BASH_PATH=/bin install
	@echo "Done"

clean: FORCE
	make -C xgfileinfo clean
	rm -rf ./test
	@echo "Done"

FORCE:

