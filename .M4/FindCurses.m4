
AC_MSG_CHECKING([CURSES])

saved_CFLAGS=${CFLAGS}
saved_CXXFLAGS=${CXXFLAGS}

AC_TRY_COMPILE(
    [#include  <ncurses.h>],
    [;],
    [myac_cf_ncurses_enabled='TRUE'],
    [myac_cf_ncurses_enabled='FALSE'])
if test "x${myac_cf_ncurses_enabled}y" = "xTRUEy" ; then
    CURSES_INCLUDE_DIRS=''
    CURSES_LIBRARIES='-lncurses'
fi
CFLAGS="${saved_CFLAGS}"
CXXFLAGS="${saved_CXXFLAGS}"

AC_MSG_RESULT(${myac_cf_ncurses_enabled})
AC_MSG_RESULT(CURSES Include : ${CURSES_INCLUDE_DIRS})
AC_MSG_RESULT(CURSES Library : ${CURSES_LIBRARIES})

AM_CONDITIONAL(
    FAIRYSHOGI_AMCNF_ENABLE_CURSES,
    test  "x${myac_cf_ncurses_enabled}y" = 'xTRUEy')

if  test  "x${myac_cf_ncurses_enabled}y" = 'xTRUEy' ; then
  AC_DEFINE(
      [HAVE_CURSES], [1],
      [Define to 1 if you have the CURSES.])
  FAIRYSHOGI_CNF_CURSES_ENABLED=1
else
  FAIRYSHOGI_CNF_CURSES_ENABLED=0
fi
AC_SUBST(FAIRYSHOGI_CNF_CURSES_ENABLED)

