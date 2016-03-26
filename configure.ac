
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
dnl   適当なバージョンの automake を設定
dnl

m4_include([M4/InitAutomake.m4])

dnl
dnl   プロジェクトの基本設定。
dnl

AC_CONFIG_SRCDIR([Makefile.am])
AC_CONFIG_HEADER([Include/.FairyShogi.Config.h:Include/FairyShogi/.Config/Config.h.in])

dnl
dnl   デフォルトのコンパイルオプション
dnl

: ${CFLAGS:='-O0  -g  -D_DEBUG'}
: ${CXXFLAGS:='-O0  -g  -D_DEBUG'}

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
  FAIRYSHOGI_CNF_WIN32_API=1
else
  FAIRYSHOGI_CNF_WIN32_API=0
fi
AC_SUBST(FAIRYSHOGI_CNF_WIN32_API)

dnl
dnl   Check Libraries.
dnl

dnl
dnl   Check Types.
dnl

AC_TYPE_UINT64_T

dnl
dnl   Check Extra Compiler/Linker Options.
dnl

m4_include([M4/CheckExtraFlags.m4])

MYAC_CHECK_EXTRA_COMPILER_OPTION(
    [FAIRYSHOGI_CNF_CFLAGS_MWINDOWS], [mwindows], [-mwindows])
MYAC_CHECK_EXTRA_LINKER_OPTION(
    [LDFLAGS], [static-libstdcxx], [-static-libstdc++])
MYAC_CHECK_EXTRA_LINKER_OPTION(
    [LDFLAGS], [static-libgcc],    [-static-libgcc])
AC_SUBST(FAIRYSHOGI_CNF_CFLAGS_MWINDOWS)

dnl
dnl   Project Name Space.
dnl

FAIRYSHOGI_CNF_NAMESPACE=fairyshogi_ns
AC_SUBST(FAIRYSHOGI_CNF_NAMESPACE)

dnl----------------------------------------------------------------
dnl
dnl   Additional Packages.
dnl   外部パッケージの追加
dnl

m4_include([M4/WithExtLibs.m4])

MYAC_WITH_EXT_LIB(
    [CPPUNIT], [cppunit], [path to cppunit], [yes],
    [AMCNF_CPPUNIT_ENABLED])

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
    Lib/Engine/Makefile
    Lib/Game/Makefile
    Lib/Interface/Makefile
    Lib/Win32/Makefile
])

AC_CONFIG_FILES([
    Include/FairyShogi/.Config/ConfiguredFairyShogi.h
])

AC_CONFIG_FILES([Lib/libfsgEngine.a:Lib/.LinkerScript/fsgEngine.in])
AC_CONFIG_FILES([Lib/libfsgGame.a:Lib/.LinkerScript/fsgGame.in])
AC_CONFIG_FILES([Lib/libfsgInterface.a:Lib/.LinkerScript/fsgInterface.in])
AC_CONFIG_FILES([Lib/libfsgWin32.a:Lib/.LinkerScript/fsgWin32.in])

dnl
dnl   Test Festures.
dnl

AC_CONFIG_FILES([
    Lib/Common/Tests/Makefile
    Lib/Engine/Tests/Makefile
    Lib/Game/Tests/Makefile
    Lib/Interface/Tests/Makefile
    Lib/Tests/Makefile
    Lib/Win32/Tests/Makefile
])

dnl
dnl   指定したファイルを生成する。
dnl

AC_OUTPUT

