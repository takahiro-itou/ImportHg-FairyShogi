
##----------------------------------------------------------------
##
##    テストの設定。
##

Add_Test (NAME  FooTest
    COMMAND  $<TARGET_FILE:RuleTablesTest>
)

##----------------------------------------------------------------
##
##    テストプログラムのビルド。
##

Add_Executable (RuleTablesTest  RuleTablesTest.cpp)

