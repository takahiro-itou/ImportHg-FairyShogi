
##
##    バイナリのビルドとインストール。
##

##
##    List of Directories.
##

SUBMODULES              =
if  FAIRYSHOGI_AMCNF_ENABLE_WINDOWS_H
SUBMODULES              +=  Win32
endif

SUBDIRS                 =  .  $(SUBMODULES)

SRCTOPDIR               =  @top_srcdir@
INCTOPDIR               =  $(SRCTOPDIR)/Include
INCPKGDIR               =  $(INCTOPDIR)/FairyShogi

BLDTOPDIR               =  @top_builddir@
LIBTOPDIR               =  $(BLDTOPDIR)/Lib

##
##    List of Source and Header Files.
##

EXTRALIBSOURCES         =
EXTRANOINSTHEADERS      =
EXTRALIBHEADERS         =

LIBCXXSOURCEFILES       =  \
        CommandInterpreter.cpp  \
        $(EXTRALIBSOURCES)

LIBINSTANTIATIONS       =
LIBCXXINLINEFILES       =

LIBNOINSTHEADERS        =  \
        CommandInterpreter.h   \
        $(EXTRANOINSTHEADERS)

INCLIBHEADERS           =  \
        $(EXTRALIBHEADERS)

LIBNODISTHEADERS        =

LIBINSTALLSOURCES       =
LIBCOMPILESOURCES       =  $(LIBCXXSOURCEFILES)  $(LIBINSTANTIATIONS)

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
        AutoMatch          \
        FairyShogi

dist_noinst_DATA        =  \
        CMakeLists.txt

dist_noinst_HEADERS     =  $(LIBNOINSTHEADERS)

##
##    Build Programs.
##

AutoMatch_SOURCES       =  AutoMatch.cpp   \
        $(LIBCOMPILESOURCES)
AutoMatch_LDADD         =  -lfsgInterface

FairyShogi_SOURCES      =  FairyShogi.cpp  \
        $(LIBCOMPILESOURCES)
FairyShogi_LDADD        =  -lfsgInterface

