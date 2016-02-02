
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
INCLIBDIR               =  $(INCPKGDIR)/Common

##
##    List of Source and Header Files.
##

EXTRALIBSOURCES         =
EXTRANOINSTHEADERS      =
EXTRALIBHEADERS         =

LIBCXXSOURCEFILES       =  \
        $(EXTRALIBSOURCES)

LIBINSTANTIATIONS       =
LIBCXXINLINEFILES       =

LIBNOINSTHEADERS        =  \
        $(EXTRANOINSTHEADERS)

INCLIBHEADERS           =  \
        $(INCLIBDIR)/FairyShogiSettings.h  \
        $(INCLIBDIR)/FairyShogiTypes.h     \
        $(INCLIBDIR)/ViewBuffer.h          \
        $(EXTRALIBHEADERS)

LIBNODISTHEADERS        =

LIBINSTALLSOURCES       =
LIBCOMPILESOURCES       =  $(LIBCXXSOURCEFILES)  $(LIBINSTANTIATIONS)

##
##    List of Libraries.
##

LIB_STATIC              =
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

fshogi_includedir              =  $(includedir)/FairyShogi
fshogi_libdir                  =  $(libdir)
fshogi_common_includedir       =  $(fshogi_includedir)/Common
fshogi_common_libdir           =  $(fshogi_libdir)/Common

fshogi_common_include_HEADERS  =  $(INCLIBHEADERS)

dist_noinst_HEADERS            =  $(LIBNOINSTHEADERS)

fshogi_common_lib_LTLIBRARIES  =  $(LIB_SHARED)
fshogi_common_lib_LIBRARIES    =  $(LIB_STATIC)

##
##    Build Libraries.
##

