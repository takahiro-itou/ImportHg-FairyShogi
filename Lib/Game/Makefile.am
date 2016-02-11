
##
##    ライブラリのビルドとインストール。
##

##
##    List of Directories.
##

SUBDIRS                 =  .  Tests

SRCTOPDIR               =  @top_srcdir@
INCTOPDIR               =  $(SRCTOPDIR)/Include
INCPKGDIR               =  $(INCTOPDIR)/FairyShogi
INCLIBDIR               =  $(INCPKGDIR)/Game

##
##    List of Source and Header Files.
##

EXTRALIBSOURCES         =
EXTRANOINSTHEADERS      =
EXTRALIBHEADERS         =

LIBCXXSOURCEFILES       =  \
        BoardState.cpp      \
        $(EXTRALIBSOURCES)

LIBINSTANTIATIONS       =
LIBCXXINLINEFILES       =

LIBNOINSTHEADERS        =  \
        $(EXTRANOINSTHEADERS)

INCLIBHEADERS           =  \
        $(INCLIBDIR)/BitSet.h      \
        $(INCLIBDIR)/BoardState.h  \
        $(EXTRALIBHEADERS)

LIBNODISTHEADERS        =

LIBINSTALLSOURCES       =
LIBCOMPILESOURCES       =  $(LIBCXXSOURCEFILES)  $(LIBINSTANTIATIONS)

##
##    List of Libraries.
##

LIB_STATIC              =  libfsgGame.staticd.a
LIB_SHARED              =

##
##    Internal Libraries.
##

##
##    Compile and Link Options.
##

AM_CPPFLAGS             =  -I$(INCTOPDIR)
AM_CFLAGS               =
AM_CXXFLAGS             =

##
##    Include Common Settings.
##

##
##    List of Installs.
##

fshogi_includedir            =  $(includedir)/FairyShogi
fshogi_libdir                =  $(libdir)
fshogi_game_includedir       =  $(fshogi_includedir)/Game
fshogi_game_libdir           =  $(fshogi_libdir)/Game

fshogi_game_include_HEADERS  =  $(INCLIBHEADERS)

dist_noinst_HEADERS          =  $(LIBNOINSTHEADERS)

fshogi_game_lib_LTLIBRARIES  =  $(LIB_SHARED)
fshogi_game_lib_LIBRARIES    =  $(LIB_STATIC)

##
##    Build Libraries.
##

libfsgGame_staticd_a_SOURCES   =  $(LIBCOMPILESOURCES)

