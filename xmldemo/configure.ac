#                                               -*- Autoconf -*-
# Process this file with autoconf to produce a configure script.

AC_PREREQ([2.69])
AC_INIT(cppTest, 1.0, labula8@qq.com)
AC_CONFIG_SRCDIR([src/hello.cpp])
AC_CONFIG_HEADERS([config.h])
AM_INIT_AUTOMAKE(main, 1.0)
# Checks for programs.
#AC_PROG_CC
AC_PROG_CXX

# Checks for libraries.

# Checks for header files.

# Checks for typedefs, structures, and compiler characteristics.

# Checks for library functions.


#check for libxml2 installation

AC_ARG_WITH(libxml2,
		AC_HELP_STRING(--with-libxml2, [libxml2 install directory (default=/usr/local)]),
		[ac_with_libxml2=$withval],
		[ac_with_libxml2=/usr/local])
AC_CHECK_PROG(XML2_CONFIG, xml2-config, yes, no, "$ac_with_libxml2"/bin)
if test "x$XML2_CONFIG" = "xyes"
then
		LIBS_XML2="`${ac_with_libxml2}/bin/xml2-config --libs`"
		CXXFLAGS_XML2="`${ac_with_libxml2}/bin/xml2-config --cflags`"
else
		AC_MSG_ERROR(xml2-config not found !)
fi
AC_SUBST(LIBS_XML2)
AC_SUBST(CXXFLAGS_XML2)

AC_CONFIG_FILES([Makefile
			src/Makefile
			])

AC_OUTPUT
