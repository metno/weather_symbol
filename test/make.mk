
if HAVE_GTEST 

TESTS = weather_symbol_test

check_PROGRAMS = weather_symbol_test

weather_symbol_test_CPPFLAGS = \
	-I$(top_srcdir)/src $(gtest_CFLAGS)

weather_symbol_test_LDADD = \
	$(top_builddir)/libweather-symbol.la \
	$(gtest_LIBS) -lgtest_main 

weather_symbol_test_LDFLAGS = \
	-pthread

weather_symbol_test_SOURCES = \
	test/SimpleWeatherSymbolTest.cpp
endif
