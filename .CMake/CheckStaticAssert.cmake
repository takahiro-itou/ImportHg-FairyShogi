
Include (CheckCXXSourceCompiles)

Check_CXX_Source_Compiles (
   "int main () {
        static_assert(1,  \"Compile Error Message\");
        return ( 0 );
    }"
    CMAKE_CHECK_CXX_STATIC_ASSERT_ENABLED
)
If ( CMAKE_CHECK_CXX_STATIC_ASSERT_ENABLED )
    Set (CONFIG_CHECK_CXX_STATIC_ASSERT_ENABLED  1)
Else()
    Set (CONFIG_CHECK_CXX_STATIC_ASSERT_ENABLED  0)
EndIf()

