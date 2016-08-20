
AC_TRY_COMPILE(
   [class A { virtual void f() { } };
    class B : public A { virtual void f() override { } };
],
   [;],
   [FAIRYSHOGI_CNF_OVERRIDE=1],
   [FAIRYSHOGI_CNF_OVERRIDE=0]
)

