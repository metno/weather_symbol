
# Usage:
# GTEST_CHECK([compile_location])
# If gtest headers are found, but not libraries, googletest may be 
# automatically compiled in the given location - but you need to provide 
# makefiles/rules for that yourself. The path will be relative to top_builddir 
AC_DEFUN([GTEST_CHECK],
[
AC_ARG_WITH([gtest],
    [AS_HELP_STRING([--with-gtest], [Specify google test directory])],
    [gtest_base=${with_gtest}],
    [gtest_base=/usr])

AC_LANG_PUSH(C++)

includes_old="${INCLUDES}"
AS_IF([test "x$gtest_base" = "x/usr"],
    [],
    [gtest_includes="-I${gtest_base}/include"])

INCLUDES="${INCLUDES} ${gtest_includes}"
AC_CHECK_HEADER([gtest/gtest.h],
    [gtest_CFLAGS=${gtest_includes}
    have_gtest=true],
    [AC_MSG_WARN([Unable to find header gtest/gtest.h])])

INCLUDES="${includes_old}"



ldflags_old="${LDFLAGS}"
AS_IF([test "x$gtest_base" = "x/usr"],
    [],
    [gtest_ldflags="-L${gtest_base}/lib"])
LDFLAGS="${LDFLAGS} ${gtest_ldflags}"
OLD_LIBS=${LIBS}
LIBS="${LIBS} -lgtest"
AC_LINK_IFELSE([AC_LANG_PROGRAM([#include <gtest/gtest.h>], [])],
	[gtest_LIBS=-lgtest],
	[
	if test $1; then
		AC_MSG_NOTICE([Unable to find precompiled googletest libraries - must compile own version])
		must_compile_gtest=true
		gtest_LIBS="-L\$(top_builddir)/$1 -lgtest"
	else
		AC_MSG_WARN([Found headers but no precompiled googletest libraries - uanble to use googletest])
		have_gtest=false
	fi
])
LIBS=${OLD_LIBS}
AM_CONDITIONAL(HAVE_GTEST, [test x${have_gtest} = xtrue])
AM_CONDITIONAL(MUST_COMPILE_GTEST, [test x${must_compile_gtest} = xtrue])

AC_SUBST(gtest_CFLAGS)
AC_SUBST(gtest_LIBS)

AC_LANG_POP
])



AC_DEFUN([GMOCK_CHECK],
[
AC_LANG_PUSH([C++])
AC_CHECK_HEADERS([gmock.h gmock/gmock.h], [have_gmock=true])
gmock_CFLAGS=
gmock_LIBS="-lgmock \$(gtest_LIBS)"
AM_CONDITIONAL(HAVE_GMOCK, [test x${have_gmock} != x])

AC_SUBST(gmock_CFLAGS)
AC_SUBST(gmock_LIBS)

AC_LANG_POP
])


# Usage:
# GMOCK_DIST_CHECK([compile_location])
# If gtest and/or gmock headers are found, but not libraries, googletest may be 
# automatically compiled in the given location - but you need to provide 
# makefiles/rules for that yourself. The path will be relative to top_builddir 

AC_DEFUN([GMOCK_DIST_CHECK],
[
AC_ARG_WITH([gmock-dist],
    [AS_HELP_STRING([--with-gmock-dist], [Specify google gmock directory (gtest is included and compiled)])],
    [gmock_base=${with_gmock_dist}],
    [gmock_base=/usr])

AC_LANG_PUSH(C++)

CPPFLAGS_SAVED="$CPPFLAGS"
AS_IF([test "x$gmock_base" = "x/usr"],
    [gtest_src="${gmock_base}/src/gtest"],
    [gtest_includes="-I${gmock_base}/gtest/include"
     gtest_src="${gmock_base}/gtest"])

CPPFLAGS="${gtest_includes} $CPPFLAGS"
AC_CHECK_HEADER([gtest/gtest.h],
    [gtest_CFLAGS=${gtest_includes}
    have_gtest=true],
    [AC_MSG_WARN([Unable to find header gtest/gtest.h])])


AS_IF([test "x$gmock_base" = "x/usr"],
    [gmock_src="${gmock_base}/src/gmock"],
    [gmock_includes="-I${gmock_base}/include";gmock_src="${gmock_base}"])

CPPFLAGS="${gmock_includes} $CPPFLAGS"
AC_CHECK_HEADER([gmock/gmock.h],
    [gmock_CFLAGS=${gmock_includes}
    have_gmock=true],
    [AC_MSG_WARN([Unable to find header gmock/gmock.h])])

CPPFLAGS=$CPPFLAGS_SAVED


ldflags_old="${LDFLAGS}"
AS_IF([test "x$gmock_base" = "x/usr"],
    [],
    [gtest_ldflags="-L${gtest_base}/lib"])
LDFLAGS="${LDFLAGS} ${gtest_ldflags}"
OLD_LIBS=${LIBS}
LIBS="${LIBS} -lgtest"
AC_LINK_IFELSE([AC_LANG_PROGRAM([#include <gtest/gtest.h>], [])],
	[gtest_LIBS=-lgtest],
	[
	if test -n "$1"; then
		AC_MSG_NOTICE([Unable to find precompiled googletest libraries - must compile own version])
		must_compile_gtest=true
		gtest_LIBS="-L\$(top_builddir)/$1 -lgtest"
	else
		AC_MSG_WARN([Found headers but no precompiled googletest libraries - unable to use googletest])
		have_gtest=false
	fi
])

AS_IF([test "x$gmock_base" = "x/usr"],
    [],
    [gmock_ldflags="-L${gmock_base}/lib"])
LDFLAGS="${LDFLAGS} ${gmock_ldflags}"
LIBS="${OLD_LIBS} -lgmock"
AC_LINK_IFELSE([AC_LANG_PROGRAM([#include <gmock/gmock.h>], [])],
	[gmock_LIBS=-lgmock],
	[
	if test -n "$1"; then
		AC_MSG_NOTICE([Unable to find precompiled googlemock libraries - must compile own version])
		must_compile_gmock=true
		gmock_LIBS="-L\$(top_builddir)/$1 -lgmock"
		AC_PATH_PROG(CMAKE, cmake)
	else
		AC_MSG_WARN([Found headers but no precompiled googlemock libraries - unable to use googlemock])
		have_gmock=false
	fi
])

LIBS=${OLD_LIBS}
LDFLAGS=${ldflags_old}

AM_CONDITIONAL(HAVE_GTEST, [test x${have_gtest} = xtrue])
AM_CONDITIONAL(HAVE_GMOCK, [test x${have_gmock} = xtrue])
AM_CONDITIONAL(MUST_COMPILE_GTEST, [test x${must_compile_gtest} = xtrue -a x${have_gtest} = xtrue])
AM_CONDITIONAL(MUST_COMPILE_GMOCK, [test x${must_compile_gmock} = xtrue -a x${have_gmock} = xtrue])

AC_SUBST(gtest_src)
AC_SUBST(gmock_src)
AC_SUBST(gtest_CFLAGS)
AC_SUBST(gtest_LIBS)
AC_SUBST(gmock_CFLAGS)
AC_SUBST(gmock_LIBS)


AC_LANG_POP
])
