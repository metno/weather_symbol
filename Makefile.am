ACLOCAL_AMFLAGS = -I m4

# Share directory organization
pkgincludedir = 		$(includedir)/weather_symbol
pkgconfigdir =			$(libdir)/pkgconfig


AM_CXXFLAGS = -DSYSCONFDIR=\"$(pkgsysconfdir)\" -fPIC 
AM_LDFLAGS = -fPIC

# Setting Targets
lib_LTLIBRARIES = libweather-symbol.la

libweather_symbol_la_SOURCES =

pkginclude_HEADERS =

libweather_symbol_la_CPPFLAGS =  $(BOOST_CPPFLAGS)
libweather_symbol_la_LIBADD = 	$(BOOST_LDFLAGS)
LIBTOOL_VERSION_CURRENT = 4
LIBTOOL_VERSION_REVISION =	1	
LIBTOOL_VERSION_AGE = 0
libweather_symbol_la_LDFLAGS = $(AM_LDFLAGS) -version-info $(LIBTOOL_VERSION_CURRENT):$(LIBTOOL_VERSION_REVISION):$(LIBTOOL_VERSION_AGE)

pkgconfig_DATA = libweather-symbol.pc

CLEANFILES =

EXTRA_DIST =

include src/make.mk
include test/make.mk
#include gtest.mk
