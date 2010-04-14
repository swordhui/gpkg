all:
	@echo "Done"

install: FORCE
	@echo "Install to ${prefix}"
	@mkdir -p ${prefix}/usr/bin
	@cp gpkg ${prefix}/usr/bin
	@chmod a+x ${prefix}/usr/bin 
	@echo "Done"

test: FORCE
	@mkdir ./test
	make prefix=./test install
	@echo "Done"

clean: FORCE
	rm -rf ./test
	@echo "Done"

FORCE:

