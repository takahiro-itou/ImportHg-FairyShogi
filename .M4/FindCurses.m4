
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

