all:
	$(MAKE) -C src/
	cp src/gaspar gaspar

test:
	$(MAKE) test -C src/

optimize:
	$(MAKE) optimize -C src/

debug:
	$(MAKE) debug -C src/

thesis:
	$(MAKE) -C thesis/

thesis-purge:
	$(MAKE) purge -C thesis/

profile:
	$(MAKE) profile -C src/

clean:
	$(MAKE) clean -C src/
