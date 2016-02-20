
##
##    List of Tests.
##

EXTRATESTS              =
TESTS                   =  \
        RuleTablesTest     \
        $(EXTRATESTS)

##
##    Compile and Link Options.
##

TESTCPPFLAGS            +=
TESTLDFLAGS             +=
TESTLIBTESTEE           +=  -lfsgGame

##
##    Test Configurations.
##

##
##    Test Programs.
##

RuleTablesTest_SOURCES  =  RuleTablesTest.cpp

