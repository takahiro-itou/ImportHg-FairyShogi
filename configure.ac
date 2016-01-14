
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

AM_INIT_AUTOMAKE

AC_CONFIG_SRCDIR([Makefile.am])

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

AC_CHECK_HEADERS([stdint.h])

dnl
dnl   Check Libraries.
dnl

dnl
dnl   Check Types.
dnl

AC_TYPE_UINT64_T

dnl
dnl   Project Name Space.
dnl

FAIRYSHOGI_CNF_NAMESPACE=fairyshogi_ns
AC_SUBST(FAIRYSHOGI_CNF_NAMESPACE)

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
])

dnl
dnl   Test Festures.
dnl

dnl
dnl   指定したファイルを生成する。
dnl

AC_OUTPUT

