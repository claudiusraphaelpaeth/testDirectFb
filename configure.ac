#############################################################################
#* configure.ac
#* Copyright (C) 2016 Elyes ABEDA <elyes.abeda@gmail.com>
#* 
#* testDirectFb is free software: you can redistribute it and/or modify it
#* under the terms of the GNU General Public License as published by the
#* Free Software Foundation, either version 3 of the License, or
#* (at your option) any later version.
#* 
#* testDirectFb is distributed in the hope that it will be useful, but
#* WITHOUT ANY WARRANTY; without even the implied warranty of
#* MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.
#* See the GNU General Public License for more details.
#* 
#* You should have received a copy of the GNU General Public License along
#* with this program.  If not, see <http://www.gnu.org/licenses/>.
#############################################################################

#For the latest tag on all the branches (not just the latest branch)
m4_define([VERSION_NUMBER],[m4_esyscmd_s([git describe --tags $(git rev-list --tags --max-count=1)])])

AC_PREREQ(2.59)
AC_INIT(testDirectFb, [VERSION_NUMBER], [elyes.abeda@gmail.com])

AC_CANONICAL_SYSTEM
AM_INIT_AUTOMAKE()

AC_PROG_CC

#############################################
################## FLAGS ####################
#############################################

CFLAGS="$CFLAGS -W -Wall -Werror"
LDFLAGS=""

#############################################
################ CHECKING ###################
#############################################

# Checks for header files
AC_CHECK_HEADERS([stdlib.h])
# Checks for libraries
AC_CHECK_LIB([])
# Checks for library functions
AC_CHECK_FUNCS()

#############################################
################# OPTIONS ###################
#############################################

#
# cppcheck
#
AM_CONDITIONAL(HAVE_CPPCHECK, [test `which cppcheck`])
#AC_CHECK_PROG(HAVE_CPPCHECK, cppcheck, cppcheck)
#[[ -z $HAVE_CPPCHECK ]] && AC_MSG_ERROR([cppcheck not found])

#
# --enable-gcov
#
AC_ARG_ENABLE(gcov,
	AS_HELP_STRING([--enable-gcov],
		[build gcov, default:no]),
		       [],
			[enable_gcov=no])
if test x$enable_gcov = xyes; then
    AC_DEFINE([GCOV], [1], [gcov enabled])
    CFLAGS+=" --coverage"
    CXXFLAGS+=" --coverage"
    LDFLAGS+=" --coverage -lgcov"
fi
AM_CONDITIONAL(ENABLE_GCOV, test x$enable_gcov = xyes)

#
# --enable-debug
#
AC_ARG_ENABLE(debug,
	AS_HELP_STRING([--enable-debug],
			[build debug, default:no]),
					       [],
			[enable_debug=no],
	[
		if test x$enable_debug == xyes ; then
	       AC_DEFINE([DEBUG], [], [Enable debug symbols])
	       CFLAGS="$CFLAGS -g -ggdb -W -Wall -O0"
	       CXXFLAGS=$CFLAGS
	       debug=true
		else
			CFLAGS="$CFLAGS -W -Wall -DNDEBUG"
			CXXFLAGS=$CFLAGS
			debug=false
		fi
	],
	[
		CFLAGS="$CFLAGS -Wall"
		CXXFLAGS=$CFLAGS
		debug=false
	])
AM_CONDITIONAL(DEBUG, test x$enable_debug != xno)

#############################################
################# MODULES ###################
#############################################

PKG_CHECK_MODULES(libLog, libLog >= 1.7.0)
PKG_CHECK_MODULES(libDFB, directfb >= 1.2.10)

REQUIRED_PKG_CONFIG=""
AC_SUBST([REQUIRED_PKG_CONFIG], ${REQUIRED_PKG_CONFIG})
REQUIRED_PRIVATE_PKG_CONFIG=""
REQUIRED_PRIVATE_PKG_CONFIG+="libLog "
REQUIRED_PRIVATE_PKG_CONFIG+="directfb "
AC_SUBST([REQUIRED_PRIVATE_PKG_CONFIG], ${REQUIRED_PRIVATE_PKG_CONFIG})

#############################################
################# PROCESS ###################
#############################################

AC_CONFIG_FILES(Makefile)
AC_CONFIG_FILES(src/Makefile)

AC_OUTPUT

# ####### Summary of configured options #######
AC_MSG_NOTICE([************ Summary ************])
AC_MSG_NOTICE([PACKAGE     : $PACKAGE_NAME])
AC_MSG_NOTICE([VERSION     : $PACKAGE_VERSION])
AC_MSG_NOTICE([DEBUG       : $enable_debug])
AC_MSG_NOTICE([GCOV        : $enable_gcov])
AC_MSG_NOTICE([*********************************])
# #############################################
