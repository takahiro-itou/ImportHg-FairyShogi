
dnl----------------------------------------------------------------
dnl
dnl   Create --with-XXX Option.
dnl
AC_DEFUN([MYAC_WITH_EXT_LIB],[
AC_ARG_WITH([$2],
    AC_HELP_STRING([--with-]$2[=PATH], $3),
    [[myac_with_]m4_bpatsubst([$2],-,_)[_val=${withval}] ],
    [[myac_with_]m4_bpatsubst([$2],-,_)[_val=']$4[']])
[case  "${myac_with_]m4_bpatsubst([$2],-,_)[_val}"  in]
[  yes)  myac_with_]m4_bpatsubst([$2],-,_)[_path='']
[        myac_with_]m4_bpatsubst([$2],-,_)[_enable=TRUE  ;;]
[  no )  myac_with_]m4_bpatsubst([$2],-,_)[_path='']
[        myac_with_]m4_bpatsubst([$2],-,_)[_enable=FALSE ;;]
[  *  )  myac_with_]m4_bpatsubst([$2],-,_)[_path=${myac_with_]m4_bpatsubst([$2],-,_)[_val}]
[        myac_with_]m4_bpatsubst([$2],-,_)[_enable=TRUE  ;;]
[esac]
AM_CONDITIONAL(
    [$5],
    [[test  "x${myac_with_]m4_bpatsubst([$2],-,_)[_enable}y" = "xTRUEy"]])
])dnl   End of AC_DEFUN(MYAC_WITH_EXT_LIB)

