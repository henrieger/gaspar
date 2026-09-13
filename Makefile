BIN_DIR = /usr/local/bin
SRC_DIR = src/gaspar
TESTS_DIR = tests/gaspar

all:
	$(MAKE) -C ${SRC_DIR}

test:
	$(MAKE) -C ${TESTS_DIR}

optimize:
	$(MAKE) optimize -C ${SRC_DIR}

debug:
	$(MAKE) debug -C ${SRC_DIR}

sanitize:
	$(MAKE) sanitize -C ${SRC_DIR}

profile:
	$(MAKE) profile -C ${SRC_DIR}

install:
	cp ${SRC_DIR}/gaspar ${BIN_DIR}

clean:
	$(MAKE) clean -C ${SRC_DIR}

purge: clean
	rm -f ${BIN_DIR}/gaspar
