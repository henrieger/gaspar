AM_CPPFLAGS = -I$(top_srcdir)/include \
							-I$(top_builddir)/lib   \
							-I$(top_srcdir)/lib     \
							-I$(srcdir)

BUILT_SOURCES = gaspar-parser.h
AM_YFLAGS = -d -Wcounterexamples

GASPAR_CFILES = functions.c
GASPAR_HFILES = functions.h $(top_srcdir)/include/gaspar/gaspar.h
GASPAR_LFILES = gaspar-scanner.l
GASPAR_YFILES = gaspar-parser.y

bin_PROGRAMS = gaspar
gaspar_SOURCES = \
	$(GASPAR_YFILES) \
	$(GASPAR_LFILES) \
	$(GASPAR_CFILES) \
	$(GASPAR_HFILES)
gaspar_LDADD = $(top_builddir)/lib/libgaspar.la
