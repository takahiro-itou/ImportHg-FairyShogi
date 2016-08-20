
AC_TRY_COMPILE(
   [;],
   [static_assert(1);
    return ( 0 );
   ],
   [FAIRYSHOGI_CNF_STATIC_ASSERT=1],
   [FAIRYSHOGI_CNF_STATIC_ASSERT=0]
)

