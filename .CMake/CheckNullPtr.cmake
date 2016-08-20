
include (CheckCXXSourceCompiles)

check_cxx_source_compiles (
  "int main () {
    void * p = nullptr;
    return ( 0 );
  }"
  CNF_CXX_NULLPTR_ENABLED
)

