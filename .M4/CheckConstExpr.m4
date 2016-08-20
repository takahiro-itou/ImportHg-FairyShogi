
AC_TRY_COMPILE(
   [],
   [constexpr  int  a = 0;
    return ( a );
   ],
   [FAIRYSHOGI_CNF_CONSTEXPR=1],
   [FAIRYSHOGI_CNF_CONSTEXPR=0]
)

