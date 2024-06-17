BIN_DIR = ${PWD}

all:
	$(MAKE) -C src/
	cp src/gaspar ${BIN_DIR}/gaspar

test:
	$(MAKE) test -C src/

optimize:
	$(MAKE) optimize -C src/
	cp src/gaspar ${BIN_DIR}/gaspar

debug:
	$(MAKE) debug -C src/
	cp src/gaspar ${BIN_DIR}/gaspar

thesis:
	$(MAKE) -C thesis/

thesis-purge:
	$(MAKE) purge -C thesis/

profile:
	$(MAKE) profile -C src/
	cp src/gaspar ${BIN_DIR}/gaspar

clean:
	$(MAKE) clean -C src/

purge: clean
	rm -f ${BIN_DIR}/gaspar
