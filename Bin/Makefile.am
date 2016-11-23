
##
##    バイナリのビルドとインストール。
##

##
##    List of Directories.
##

MODULE_DIR_NAME         =  Binary

SUBMODULES              =

if  FAIRYSHOGI_AMCNF_ENABLE_WINDOWS_H
SUBMODULES              +=  Win32
endif

if  FAIRYSHOGI_AMCNF_ENABLE_CURSES
SUBMODULES              +=  TextUI
endif

SUBDIRS                 =  .  $(SUBMODULES)

include  $(top_srcdir)/.M4/Makefile.DirList.inc

##
##    List of Source and Header Files.
##

COMMONSOURCES           =  \
        CommandInterpreter.cpp

##
##    Internal Libraries.
##

##
##    Compile and Link Options.
##

AM_CPPFLAGS             =  \
        -I${INCTOP_SOURCE_DIR}
AM_CFLAGS               =
AM_CXXFLAGS             =
AM_LDFLAGS              =  -L${LIBTOP_BINARY_DIR}

##
##    List of Installs.
##

bin_PROGRAMS            =  \
        AutoMatch          \
        FairyShogi

dist_noinst_DATA        =  \
        CMakeLists.txt

##
##    Build Executables.
##

AutoMatch_SOURCES       =  AutoMatch.cpp   ${COMMONSOURCES}
AutoMatch_LDADD         =  -lfsgInterface

FairyShogi_SOURCES      =  FairyShogi.cpp  ${COMMONSOURCES}
FairyShogi_LDADD        =  -lfsgInterface

