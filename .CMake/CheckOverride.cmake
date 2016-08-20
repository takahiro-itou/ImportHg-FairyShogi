
include (CheckCXXSourceCompiles)

check_cxx_source_compiles (
  "class A {
    virtual void f() { }
  };
  class B : public A {
    virtual void f()  override { }
  };
  int main () {
    return ( 0 );
  }"
  CNF_CXX_OVERRIDE_ENABLED
)


