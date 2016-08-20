
dnl----------------------------------------------------------------
dnl
dnl   Check Extra Compiler Options.
dnl
AC_DEFUN([MYAC_CHECK_EXTRA_COMPILER_OPTION],
[AC_MSG_CHECKING([for Compiler Option ]$3)
saved_CFLAGS=${CFLAGS}
saved_CXXFLAGS=${CXXFLAGS}
[CFLAGS=']$3[']
[CXXFLAGS=']$3[']
AC_TRY_COMPILE(
    [;],
    [;],
    [[myaccf_]m4_bpatsubst([$2],-,_)[_enabled='TRUE']],
    [[myaccf_]m4_bpatsubst([$2],-,_)[_enabled='FALSE']])
[if test "x${myaccf_]m4_bpatsubst([$2],-,_)[_enabled}y" = "xTRUEy" ; then]
    [CFLAGS="${saved_CFLAGS}"]
    [CXXFLAGS="${saved_CXXFLAGS}"]
    $1[="${]$1[}  ]$3["]
    AC_MSG_RESULT([Accept])
[else]
    [CFLAGS="${saved_CFLAGS}"]
    [CXXFLAGS="${saved_CXXFLAGS}"]
    AC_MSG_RESULT([Reject])
[fi]
])dnl   End of AC_DEFUN(MYAC_CHECK_EXTRA_COMPILER_OPTION)

dnl----------------------------------------------------------------
dnl
dnl   Check Extra Link Options.
dnl
AC_DEFUN([MYAC_CHECK_EXTRA_LINKER_OPTION],
[AC_MSG_CHECKING([for Linker Option ]$3)
saved_LDFLAGS=${LDFLAGS}
[LDFLAGS=']$3[']
AC_TRY_LINK(
    [;],
    [;],
    [[myacld_]m4_bpatsubst([$2],-,_)[_enabled='TRUE']],
    [[myacld_]m4_bpatsubst([$2],-,_)[_enabled='FALSE']])
[if test "x${myacld_]m4_bpatsubst([$2],-,_)[_enabled}y" = "xTRUEy" ; then]
    [LDFLAGS="${saved_LDFLAGS}"]
    $1[="${]$1[} ]$3["]
    AC_MSG_RESULT([Accept])
[else]
    [LDFLAGS="${saved_LDFLAGS}"]
    AC_MSG_RESULT([Reject])
[fi]
])dnl   End of AC_DEFUN(MYAC_CHECK_EXTRA_LINKER_OPTION)

