AM_CFLAGS =					\
	$(GROONGA_CFLAGS)

AM_LDFLAGS =					\
	-avoid-version				\
	-module					\
	-no-undefined

LIBS =						\
	$(GROONGA_LIBS)

regex_plugins_LTLIBRARIES =
regex_plugins_LTLIBRARIES += regex.la

regex_la_SOURCES = \
regex.cpp

regex_la_CPPFLAGS = $(AM_CFLAGS) $(AM_CPPFLAGS)
regex_la_LIBADD = $(LIBS) $(RE2_LIBS)
regex_la_LDFLAGS = $(AM_LDFLAGS)
