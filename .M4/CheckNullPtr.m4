
AC_TRY_COMPILE(
   [;],
   [void * p = nullptr;
    return ( 0 );
   ],
   [FAIRYSHOGI_CNF_NULLPTR=1],
   [FAIRYSHOGI_CNF_NULLPTR=0]
)

