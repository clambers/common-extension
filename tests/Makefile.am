# Copyright (C) 2015 Jaguar Land Rover Automotive PLC.
#
# This file is part of Common.
#
# Common is free software: you can redistribute it and/or modify
# it under the terms of the GNU Lesser General Public License as published by
# the Free Software Foundation, either version 3 of the License, or
# (at your option) any later version.
#
# Common is distributed in the hope that it will be useful,
# but WITHOUT ANY WARRANTY; without even the implied warranty of
# MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
# GNU Lesser General Public License for more details.
#
# You should have received a copy of the GNU Lesser General Public License
# along with Common.  If not, see <http://www.gnu.org/licenses/>.

TESTSUITE = $(top_srcdir)/tests/testsuite
TESTSUITE_AT = testsuite.at library.at

AUTOM4TE = $(top_srcdir)/build-aux/missing --run autom4te
AT = $(AUTOM4TE) --language=autotest
ATFLAGS = -I$(srcdir)

EXTRA_DIST = $(TESTSUITE) $(TESTSUITE_AT) atlocal.in

DISTCLEANFILES = atconfig atlocal
MAINTAINERCLEANFILES = $(TESTSUITE) package.m4

$(TESTSUITE): $(TESTSUITE_AT)
	@if [ $(AM_V_P) == false ]; then echo "  AT      `basename $(TESTSUITE)`"; fi
	$(AM_V_at)$(AT) $(ATFLAGS) -o $@.tmp $@.at
	$(AM_V_at)mv $@.tmp $@

check-local: all atconfig atlocal $(TESTSUITE)
	@if [ $(AM_V_P) == false ]; then echo "  TEST    `basename $(TESTSUITE)`"; fi
	$(AM_V_at)./$(TESTSUITE)

installcheck-local: all atconfig atlocal $(TESTSUITE)
	$(AM_V_at)./$(TESTSUITE) AUTOTEST_PATH='$(bindir)'

clean-local:
	test ! -f $(TESTSUITE) || ./$(TESTSUITE) --clean
