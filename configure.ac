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

AC_PREREQ([2.69])
AC_INIT([Common], [0.1],
[https://github.com/clambers/common-extension/issues], [],
[https://github.com/clambers/common-extension])
AC_COPYRIGHT([Copyright (C) 2015 Jaguar Land Rover Automotive PLC.])
AC_CONFIG_SRCDIR([lib/common.c])
AC_CONFIG_AUX_DIR([build-aux])
AC_CONFIG_MACRO_DIR([m4])

AM_INIT_AUTOMAKE([1.14 foreign -Wall -Werror -Wno-portability])
AM_SILENT_RULES([yes])

AM_PROG_AR
LT_INIT

AC_PROG_CC
AM_PROG_CC_C_O
PKG_CHECK_MODULES([DLog], [dlog])
PKG_CHECK_MODULES([Jansson], [jansson])

AC_SUBST([COMMON_PATH], [/usr/share/common])
AC_DEFINE_UNQUOTED([COMMON_PATH], ["$COMMON_PATH"],
[Filesystem location of common assets.])

AC_CONFIG_TESTDIR([tests])
AC_CONFIG_HEADERS([config.h])
AC_CONFIG_FILES([Makefile common.pc lib/Makefile common/Makefile
tests/Makefile tests/package.m4 tests/atlocal])

AC_OUTPUT
