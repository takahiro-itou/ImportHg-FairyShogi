
include (CheckCXXSourceCompiles)

check_cxx_source_compiles (
  "int main () {
    static_assert(1);
    return ( 0 );
  }"
  CNF_CXX_STATIC_ASSERT_ENABLED
)


