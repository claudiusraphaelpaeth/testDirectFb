#############################################################################
#* Makefile.am
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

AM_CXXFLAGS = \
	-DPACKAGE_LOCALE_DIR=\""$(localedir)"\" \
	-DPACKAGE_SRC_DIR=\""$(srcdir)"\" \
	-DPACKAGE_DATA_DIR=\""$(pkgdatadir)"\"

AM_CFLAGS =\
	 -W\
	 -Wall\
	 -Werror\
	 -g

testDirectFb_PROGRAMS = testDirectFb
testDirectFbdir = $(prefix)/bin

testDirectFb_SOURCES = $(top_srcdir)/src/testDirectFb.c
testDirectFb_CFLAGS = $(libLog_CFLAGS) $(libDFB_CFLAGS)
testDirectFb_LDFLAGS = $(libLog_LIBS) $(libDFB_LIBS)
testDirectFb_LDADD = $(libLog_LIBS) $(libDFB_LIBS)

check-local:
# It should continue if there are cppcheck errors
ERR_EXITCODE = 0
# Check options (all for all options)
CHECK_OPTS = style,performance,portability,information,missingInclude
# Include an extra check for the source code.
if HAVE_CPPCHECK
	@echo "--- cppcheck enabled ---"
	@# Print cppcheck version for information/log
	@cppcheck --version
	@cppcheck -q --force --enable=$(CHECK_OPTS) --std=posix --platform=unix32 \
	--inline-suppr --suppress=variableScope --error-exitcode=$(ERR_EXITCODE) \
	-I$(top_srcdir)/inc -I$(top_srcdir)/test $(testDirectFb_SOURCES) \
	&& echo "--- cppcheck passed ---" \
	|| (echo "--- cppcheck failed! ---" && exit 1)
else
	@echo "--- cppcheck disabled (not installed on host) ---"
endif
