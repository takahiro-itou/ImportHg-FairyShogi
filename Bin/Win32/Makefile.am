
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

EXTRALIBSOURCES         =
EXTRANOINSTHEADERS      =
EXTRALIBHEADERS         =

LIBCXXSOURCEFILES       =  \
        BoardScreen.cpp      \
        PromotionScreen.cpp  \
        Resources.cpp        \
        ScreenLayer.cpp      \
        $(EXTRALIBSOURCES)

LIBINSTANTIATIONS       =
LIBCXXINLINEFILES       =

LIBNOINSTHEADERS        =  \
        BoardScreen.h        \
        PromotionScreen.h    \
        Resources.h          \
        ScreenLayer.h        \
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
AM_CFLAGS               =  $(FAIRYSHOGI_CNF_CFLAGS_MWINDOWS)
AM_CXXFLAGS             =  $(FAIRYSHOGI_CNF_CFLAGS_MWINDOWS)
AM_LDFLAGS              =  -L$(LIBTOPDIR)

AM_CPPFLAGS             += -DFAIRYSHOGI_WIN32=1

##
##    Include Common Settings.
##

##
##    List of Installs.
##

bin_PROGRAMS            =  \
        FairyShogiWin32

dist_bin_SCRIPTS        =  \
        Back.bmp           \
        Pieces.bmp

##
##    Build Programs.
##

FairyShogiWin32_SOURCES   =  FairyShogiWin32.cpp  \
        $(LIBCOMPILESOURCES)

FairyShogiWin32_LDADD     =  -lfsgInterface  -lGdi32

