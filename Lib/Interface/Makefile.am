
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
INCLIBDIR               =  $(INCPKGDIR)/Interface

##
##    List of Source and Header Files.
##

EXTRALIBSOURCES         =
EXTRANOINSTDATA         =
EXTRANOINSTHEADERS      =
EXTRALIBHEADERS         =

LIBCXXSOURCEFILES       =  \
        ConsoleInterface.cpp    \
        GameController.cpp      \
        GraphicalInterface.cpp  \
        PixelMatrix.cpp         \
        $(EXTRALIBSOURCES)

LIBINSTANTIATIONS       =
LIBCXXINLINEFILES       =

LIBNOINSTDATA           =  \
        CMakeLists.txt      \
        $(EXTRANOINSTDATA)
LIBNOINSTHEADERS        =  \
        $(EXTRANOINSTHEADERS)

INCLIBHEADERS           =  \
        $(INCLIBDIR)/ConsoleInterface.h    \
        $(INCLIBDIR)/GameController.h      \
        $(INCLIBDIR)/GraphicalInterface.h  \
        $(INCLIBDIR)/PixelMatrix.h         \
        $(EXTRALIBHEADERS)

LIBNODISTHEADERS        =

LIBINSTALLSOURCES       =
LIBCOMPILESOURCES       =  $(LIBCXXSOURCEFILES)  $(LIBINSTANTIATIONS)

##
##    List of Libraries.
##

LIB_STATIC              =  libfsgInterface.staticd.a
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

fshogi_includedir                 =  $(includedir)/FairyShogi
fshogi_libdir                     =  $(libdir)
fshogi_interface_includedir       =  $(fshogi_includedir)/Interface
fshogi_interface_libdir           =  $(fshogi_libdir)/Interface

fshogi_interface_include_HEADERS  =  $(INCLIBHEADERS)

dist_noinst_DATA                  =  $(LIBNOINSTDATA)
dist_noinst_HEADERS               =  $(LIBNOINSTHEADERS)

fshogi_interface_lib_LTLIBRARIES  =  $(LIB_SHARED)
fshogi_interface_lib_LIBRARIES    =  $(LIB_STATIC)

##
##    Build Libraries.
##

libfsgInterface_staticd_a_SOURCES   =  $(LIBCOMPILESOURCES)

