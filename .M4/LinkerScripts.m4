dnl----------------------------------------------------------------
dnl
dnl   Linker Scripts.
dnl   リンカスクリプトを生成する。
dnl

AC_CONFIG_FILES([Lib/libfsgEngine.a:Lib/.LinkerScript/fsgEngine.in])
AC_CONFIG_FILES([Lib/libfsgGame.a:Lib/.LinkerScript/fsgGame.in])
AC_CONFIG_FILES([Lib/libfsgInterface.a:Lib/.LinkerScript/fsgInterface.in])
AC_CONFIG_FILES([Lib/libfsgWin32.a:Lib/.LinkerScript/fsgWin32.in])

