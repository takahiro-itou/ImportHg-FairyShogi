
dnl----------------------------------------------------------------
dnl
dnl   Package Configurations.
dnl   パッケージ設定。
dnl

dnl
dnl   要求する autoconf のバージョンを指定する。
dnl

AC_PREREQ([2.68])

dnl
dnl   パッケージの情報を指定する。
dnl

AC_INIT(
    [FairyShogi],
    [0.0.0],
    [BUG-REPORT-ADDRESS],
    [FairyShogi])

dnl
dnl   ツールの出力ディレクトリを指定する。
dnl

AC_CONFIG_AUX_DIR([.Config])

dnl
dnl   プロジェクトの基本設定。
dnl

AM_INIT_AUTOMAKE(
    [serial-tests]
)

AC_CONFIG_SRCDIR([Makefile.am])
AC_CONFIG_HEADER([Include/.FairyShogi.Config.h:Include/FairyShogi/.Config/Config.h.in])

dnl
dnl   デフォルトのコンパイルオプション
dnl

: ${CFLAGS:='-O2  -g'}
: ${CXXFLAGS:='-O2  -g'}

CFLAGS="${CFLAGS}  -std=c++11  -Wall"
CXXFLAGS="${CXXFLAGS}  -std=c++11  -Wall  -Weffc++"

dnl
dnl   Check Programs.
dnl

AC_LANG_CPLUSPLUS
AC_PROG_CC
AC_PROG_CXX
AM_PROG_AS
AC_PROG_RANLIB

dnl
dnl   Check Header Files.
dnl

AC_CHECK_HEADER([stdint.h])

AC_CHECK_HEADER(
    [windows.h],
    [fsgcnf_have_windows_h=TRUE],
    [fsgcnf_have_windows_h=FALSE]
)

AM_CONDITIONAL(
    FAIRYSHOGI_AMCNF_ENABLE_WINDOWS_H,
    test  "x${fsgcnf_have_windows_h}" = 'xTRUE')
if  test  "x${fsgcnf_have_windows_h}" = 'xTRUE' ; then
  AC_DEFINE(
      [HAVE_WINDOWS_H], [1],
      [Define to 1 if you have the <windows.h> header file.])
fi

dnl
dnl   Check Libraries.
dnl

dnl
dnl   Check Types.
dnl

AC_TYPE_UINT64_T

dnl
dnl   Check (Extra) Compiler Options.
dnl

m4_include([M4/CheckExtraFlags.m4])

saved_CFLAGS=${CFLAGS}
saved_CXXFLAGS=${CXXFLAGS}
CFLAGS='-mwindows'
CXXFLAGS='-mwindows'
AC_TRY_COMPILE(
    [],
    [],
    [myac__mwindows_enabled='TRUE'],
    [myac__mwindows_enabled='FALSE'])
if test "x${myac__mwindows_enabled}y" = "xTRUEy" ; then
     CFLAGS="${saved_CFLAGS}      -mwindows"
     CXXFLAGS="${saved_CXXFLAGS}  -mwindows"
else
    CFLAGS=${saved_CFLAGS}
    CXXFLAGS=${saved_CFLAGS}
fi

dnl
dnl   Project Name Space.
dnl

FAIRYSHOGI_CNF_NAMESPACE=fairyshogi_ns
AC_SUBST(FAIRYSHOGI_CNF_NAMESPACE)

dnl----------------------------------------------------------------
dnl
dnl   外部パッケージの追加
dnl   Additional Packages.
dnl

AC_ARG_WITH(
    [cppunit],
    AC_HELP_STRING([--with-cppunit=PATH], [path to cppunit]),
    [myac_with_cppunit_val=${withval}],
    [myac_with_cppunit_val='yes'])

case  "${myac_with_cppunit_val}"  in
  yes)  myac_with_cppunit_path=''
        myac_with_cppunit_enable=TRUE  ;;
  no )  myac_with_cppunit_path=''
        myac_with_cppunit_enable=FALSE ;;
  *  )  myac_with_cppunit_path=${myac_with_cppunit_val}
        myac_with_cppunit_enable=FALSE ;;
esac

AM_CONDITIONAL(
    [AMCNF_CPPUNIT_ENABLED],
    [test  "x${myac_with_cppunit_enable}y" = "xTRUEy"])

dnl----------------------------------------------------------------
dnl
dnl   Outputs.
dnl   出力ファイルを設定する。
dnl

dnl
dnl   Basic Features.
dnl

AC_CONFIG_FILES([
    Makefile
    Bin/Makefile
    Bin/Win32/Makefile
    Lib/Makefile
    Lib/.Config/Makefile
    Lib/Common/Makefile
    Lib/Game/Makefile
    Lib/Interface/Makefile
])

AC_CONFIG_FILES([
    Include/FairyShogi/.Config/ConfiguredFairyShogi.h
])


AC_CONFIG_FILES([Lib/libfsgGame.a:Lib/.LinkerScript/fsgGame.in])
AC_CONFIG_FILES([Lib/libfsgInterface.a:Lib/.LinkerScript/fsgInterface.in])

dnl
dnl   Test Festures.
dnl

AC_CONFIG_FILES([
    Lib/Common/Tests/Makefile
    Lib/Game/Tests/Makefile
    Lib/Interface/Tests/Makefile
    Lib/Tests/Makefile
])

dnl
dnl   指定したファイルを生成する。
dnl

AC_OUTPUT

