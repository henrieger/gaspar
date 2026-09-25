SUBDIRS = lib src
DIST_SUBDIRS = $(SUBDIRS) examples include tests

AUTOMAKE_OPTIONS = foreign

ACLOCAL_AMFLAGS = -I m4 --install

pkgconfigdir = $(libdir)/pkgconfig
pkgconfig_DATA = libgaspar.pc

install-data-hook:
	(cd include && $(MAKE) install)

uninstall-hook:
	(cd include && $(MAKE) uninstall)

check-recursive:
	$(MAKE) -C tests check
