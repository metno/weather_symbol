# Share directory organization
pkgincludedir = 		$(includedir)/weather_symbol
pkgconfigdir =			$(libdir)/pkgconfig

ACLOCAL_AMFLAGS = -I m4

AM_CXXFLAGS = -DSYSCONFDIR=\"$(pkgsysconfdir)\" -fPIC 
AM_LDFLAGS = -fPIC

# Setting Targets
lib_LTLIBRARIES = libweather-symbol.la

libweather_symbol_la_SOURCES =

pkginclude_HEADERS =

libweather_symbol_la_CPPFLAGS =  $(BOOST_CPPFLAGS)
libweather_symbol_la_LIBADD = 	$(BOOST_LDFLAGS)
LIBTOOL_VERSION_CURRENT = 	1
LIBTOOL_VERSION_REVISION = 	0 
LIBTOOL_VERSION_AGE = 		0
libweather_symbol_la_LDFLAGS = $(AM_LDFLAGS) -version-info $(LIBTOOL_VERSION_CURRENT):$(LIBTOOL_VERSION_REVISION):$(LIBTOOL_VERSION_AGE)

pkgconfig_DATA = libweather-symbol.pc

CLEANFILES =

EXTRA_DIST =

include src/make.mk
#include test/libwdbLoad.mk


include debian.mk
