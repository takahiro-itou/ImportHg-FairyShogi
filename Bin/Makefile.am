
##
##    バイナリのビルドとインストール。
##

##
##    List of Directories.
##

SUBDIRS                 =  .  Win32

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

##
##    Include Common Settings.
##

##
##    List of Installs.
##

bin_PROGRAMS            =  \
        FairyShogi

##
##    Build Programs.
##

FairyShogi_SOURCES      =  FairyShogi.cpp
FairyShogi_LDADD        =  -lfsgInterface

