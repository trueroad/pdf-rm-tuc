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
AC_PROG_GREP

AC_PATH_PROG([DIFF], [diff])
AS_IF([test "x$DIFF" = x],
      [AC_MSG_WARN([diff isn't found. `make check' will fail tests.])])
AC_SUBST([DIFF])

AC_PATH_PROG([PDFFONTS], [pdffonts])
AS_IF([test "x$PDFFONTS" = x],
      [AC_MSG_WARN([pdffonts isn't found. `make check' will fail tests.])])
AC_SUBST([PDFFONTS])

AC_PATH_PROG([PDFTOTEXT], [pdftotext])
AS_IF([test "x$PDFTOTEXT" = x],
      [AC_MSG_WARN([pdftotext isn't found. `make check' will fail tests.])])
AC_SUBST([PDFTOTEXT])

AC_MSG_CHECKING([for pre-generated test PDFs])
AS_IF([test ! -e ${srcdir}/test/ascii.pdf],
      [AC_MSG_RESULT([no])
       AC_PATH_PROG([LUATEX], [luatex])
       AS_IF([test "x$LUATEX" = x],
             [AC_MSG_WARN(
                  [luatex isn't found. Test PDFs cannot be generated.])
              AC_MSG_WARN(
                  [You cannot use `make check'.])],
             [AC_MSG_NOTICE(
                  [luatex is found. Test PDFs will be generated.])])],
      [AC_MSG_RESULT([yes])])
AC_SUBST([LUATEX])

AC_MSG_CHECKING([for pre-generated expected text files])
AS_IF([test ! -e ${srcdir}/test/ascii-expected.pdftotext],
      [AC_MSG_RESULT([no])
       AC_MSG_WARN(
           [Text files will be generated.])
       AC_MSG_WARN(
           [`make check' cannot compare with the correct expected results.])],
      [AC_MSG_RESULT([yes])])

# Checks for libraries.
PKG_PROG_PKG_CONFIG
PKG_CHECK_MODULES([LIBQPDF], [libqpdf])

# Checks for header files.

# Checks for typedefs, structures, and compiler characteristics.
AX_CXX_COMPILE_STDCXX_11([noext], [mandatory])

# Checks for library functions.

AC_CONFIG_FILES([Makefile
    src/Makefile
    test/Makefile])
AC_OUTPUT
