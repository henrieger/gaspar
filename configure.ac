#                                               -*- Autoconf -*-
# Process this file with autoconf to produce a configure script.

AC_PREREQ([2.73])
AC_INIT([GASPAR], [26.09], [henriquerieger2001@gmail.com])
AC_CONFIG_SRCDIR([lib/eval/parsimony.c])
AC_CONFIG_AUX_DIR([build-aux])
AC_CONFIG_HEADERS([config.h])
AC_CONFIG_MACRO_DIRS([m4])

# Checks for programs.
AC_PROG_CC
AC_PROG_LEX([noyywrap])
AC_PROG_YACC

# Checks for libraries.
# FIXME: Replace 'main' with a function in '-lc':
AC_CHECK_LIB([c], [main])
# FIXME: Replace 'main' with a function in '-lfl':
AC_CHECK_LIB([fl], [main])
# FIXME: Replace 'main' with a function in '-lm':
AC_CHECK_LIB([m], [main])
# FIXME: Replace 'main' with a function in '-ly':
AC_CHECK_LIB([y], [main])

# Checks for header files.
AC_CHECK_HEADERS([stdint.h])

# Checks for typedefs, structures, and compiler characteristics.
AC_CHECK_HEADER_STDBOOL
AC_C_INLINE
AC_TYPE_INT32_T
AC_TYPE_INT64_T
AC_TYPE_SIZE_T
AC_TYPE_UINT32_T
AC_TYPE_UINT64_T
AC_TYPE_UINT8_T

# Checks for library functions.
AC_FUNC_MALLOC

LT_INIT
AM_INIT_AUTOMAKE([1.18.1 subdir-objects -Wall -Werror])
AC_CONFIG_FILES([\
  Makefile \
  examples/Makefile \
  include/Makefile \
  include/gaspar/Makefile \
  lib/Makefile \
  src/Makefile \
  tests/Makefile \
  tests/lib/Makefile \
  tests/src/Makefile \
  libgaspar.pc
])

AC_OUTPUT
