
dnl
dnl   Check Extra (Compiler) Options.
dnl

AC_DEFUN([MYAC_CHECK_EXTRA_OPTION],
[AC_MSG_CHECKING([for Compiler Option ]$1)
saved_CFLAGS=${CFLAGS}
saved_CXXFLAGS=${CXXFLAGS}
[CFLAGS=']$1[']
[CXXFLAGS=']$1[']
AC_TRY_COMPILE(
    [],
    [],
    [[myac_]m4_bpatsubst([$1],-,_)[_enabled]='TRUE'],
    [[myac_]m4_bpatsubst([$1],-,_)[_enabled]='FALSE'])
[if test "${myac_]m4_bpatsubst([$1],-,_)[_enabled}y" = "xTRUEy" ; then]
    [CFLAGS="${saved_CFLAGS}     ]$1["]
    [CXXFLAGS="${saved_CXXFLAGS} ]$1["]
   AC_MSG_RESULT([Accept])
[else]
    [CFLAGS="${saved_CFLAGS}"]
    [CXXFLAGS="${saved_CXXFLAGS}"]
   AC_MSG_RESULT([Reject])
[fi]
])

