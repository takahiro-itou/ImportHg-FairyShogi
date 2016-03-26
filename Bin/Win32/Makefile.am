
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
        ChoiceScreen.cpp     \
        DiceScreen.cpp       \
        EngineProcess.cpp    \
        PromotionScreen.cpp  \
        Resources.rc         \
        ScreenLayer.cpp      \
        $(EXTRALIBSOURCES)

LIBINSTANTIATIONS       =
LIBCXXINLINEFILES       =

LIBNOINSTHEADERS        =  \
        BoardScreen.h        \
        ChoiceScreen.h       \
        DiceScreen.h         \
        EngineProcess.h      \
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
##    Suffix Rules.
##

SUFFIXES  =  .rc

.rc.o :
	windres  -i $<  -o $@

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
        Dice.bmp           \
        Pieces.bmp

dist_noinst_HEADERS     =  $(LIBNOINSTHEADERS)

##
##    Build Programs.
##

FairyShogiWin32_SOURCES   =  FairyShogiWin32.cpp  \
        $(LIBCOMPILESOURCES)

FairyShogiWin32_LDADD     =  -lfsgInterface  -lfsgWin32  -lGdi32

##
##    Resource Files.
##

all-local :
	for  file  in  Back.bmp  Dice.bmp  Pieces.bmp  ; do  \
        if  test ! -e  $${file} ; then                   \
            cp     -pv  $(srcdir)/$${file}  .  ;         \
        fi ;                                             \
    done

