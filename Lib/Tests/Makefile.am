
##
##    ライブラリの単体テストドライバ。
##

##
##    List of Directories.
##

BLDTOPDIR               =  @top_builddir@
SRCTOPDIR               =  @top_srcdir@
INCTOPDIR               =  $(SRCTOPDIR)/Include

DRIVER_LIBDIR           =  $(BLDTOPDIR)/Lib/Tests
DRIVER_SRCDIR           =  $(SRCTOPDIR)/Lib/Tests

TESTEE_LIBDIR           =  ..
TESTEE_SRCDIR           =  @srcdir@/..

##
##    Initialize Test Configurations.
##

TESTDRIVERS             =
LIBNOINSTHEADERS        =
EXTRADRIVERS            =
LDTESTDRIVERS           =
TESTCPPFLAGS            =
TESTLDFLAGS             =

##
##    Test Configurations.
##

include  @srcdir@/TestConf.mak

##
##    List of Source and Header Files.
##

TESTDRIVERS             +=  TestDriver.cpp
LIBNOINSTHEADERS        +=  TestDriver.h
EXTRADRIVERS            +=
LDTESTDRIVERS           +=

##
##    Compile and Link Options.
##

if  AMCNF_CPPUNIT_ENABLED
TESTXUNITCPPFLAGS       =  -DHAVE_CPPUNIT=1
TESTXUNITLDFLAGS        =
else
TESTXUNITCPPFLAGS       =  -DHAVE_CPPUNIT=0
TESTXUNITLDFLAGS        =
endif

AM_CPPFLAGS             =  \
        -I$(TESTEE_SRCDIR)  \
        -I$(INCTOPDIR)      \
        -I$(DRIVER_SRCDIR)  \
        $(TEST_CPPFLAGS)

AM_CFLAGS               =  $(TESTXUNITCPPFLAGS)
AM_CXXFLAGS             =  $(TESTXUNITCPPFLAGS)
AM_LDFLAGS              =  \
        $(LDTESTDRIVERS)     \
        $(TESTLDFLAGS)       \
        $(TESTXUNITLDFLAGS)

##
##    List of Installs.
##

LIBTESTDRIVER           =  libTestDriver.a

dist_noinst_HEADERS     =  $(EXTRATESTDRIVERS)  $(LIBNOINSTHEADERS)
check_PROGRAMS          =  $(TESTS)
noinst_LIBRARIES        =  $(LIBTESTDRIVER)

##
##    Build of Test Drivers.
##

libTestDriver_a_SOURCES     =  $(TESTDRIVERS)

