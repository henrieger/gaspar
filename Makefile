all:
	$(MAKE) -C src/
	cp src/gaspar gaspar

test:
	$(MAKE) test -C src/

optimize:
	$(MAKE) optimize -C src/

debug:
	$(MAKE) debug -C src/

profile:
	$(MAKE) profile -C src/

clean:
	$(MAKE) clean -C src/
