#                                               -*- Autoconf -*-
# Process this file with autoconf to produce a configure script.

AC_PREREQ([2.69])
AC_INIT([Remove ToUnicode CMap from PDF], [0.0.1], ,
    [pdf-rm-tuc], [https://github.com/trueroad/pdf-rm-tuc])
AM_INIT_AUTOMAKE([foreign])
AC_CONFIG_SRCDIR([src/main.cc])
AC_CONFIG_HEADERS([config.h])

PACKAGE_COPYRIGHT="Copyright (C) 2019 Masamichi Hosoda. All rights reserved."
PACKAGE_LICENSE="License: BSD-2-Clause"

AC_SUBST([PACKAGE_COPYRIGHT])
AC_SUBST([PACKAGE_LICENSE])
AC_DEFINE_UNQUOTED([PACKAGE_COPYRIGHT], ["$PACKAGE_COPYRIGHT"],
    [Define to the copyright of this package.])
AC_DEFINE_UNQUOTED([PACKAGE_LICENSE], ["$PACKAGE_LICENSE"],
    [Define to the license of this package.])

# Checks for programs.
AC_PROG_CXX

# Checks for libraries.
PKG_PROG_PKG_CONFIG
PKG_CHECK_MODULES([LIBQPDF], [libqpdf])

# Checks for header files.

# Checks for typedefs, structures, and compiler characteristics.
AX_CXX_COMPILE_STDCXX_11([noext], [mandatory])

# Checks for library functions.

AC_CONFIG_FILES([Makefile
    src/Makefile])
AC_OUTPUT
