
##
##    バイナリのビルドとインストール。
##

##
##    List of Directories.
##

SUBDIRS                 =  .

SRCTOPDIR               =  @top_srcdir@
INCTOPDIR               =  $(SRCTOPDIR)/Include
INCPKGDIR               =  $(INCTOPDIR)/FairyShogi

BLDTOPDIR               =  @top_builddir@
LIBTOPDIR               =  $(BLDTOPDIR)/Lib

##
##    List of Source and Header Files.
##

##
##    List of Libraries.
##

##
##    Internal Libraries.
##

##
##    Compile and Link Options.
##

AM_CPPFLAGS             =  -I$(INCTOPDIR)
AM_CFLAGS               =
AM_CXXFLAGS             =
AM_LDFLAGS              =  -L$(LIBTOPDIR)

AM_CPPFLAGS             += -DDSHOGI_WIN32=1

##
##    Include Common Settings.
##

##
##    List of Installs.
##

bin_PROGRAMS            =  \
        FairyShogiWin32

bin_SCRIPTS             =  \
        Back.bmp           \
        Pieces.bmp

##
##    Build Programs.
##

FairyShogiWin32_SOURCES   =  FairyShogiWin32.cpp
FairyShogiWin32_LDADD     =  -lfsgInterface  -lGdi32

