
include (CheckCXXSourceCompiles)

check_cxx_source_compiles (
  "constexpr  int  a = 0;
  int main () {
    return ( a );
  }"
  CNF_CXX_CONSTEXPR_ENABLED
)

