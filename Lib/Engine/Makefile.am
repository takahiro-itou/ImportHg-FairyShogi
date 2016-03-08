
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
INCLIBDIR               =  $(INCPKGDIR)/Engine

##
##    List of Source and Header Files.
##

EXTRALIBSOURCES         =
EXTRANOINSTHEADERS      =
EXTRALIBHEADERS         =

LIBCXXSOURCEFILES       =  \
        EngineBase.cpp         \
        EngineImplements.cpp   \
        EngineLevel0.cpp       \
        $(EXTRALIBSOURCES)

LIBINSTANTIATIONS       =
LIBCXXINLINEFILES       =

LIBNOINSTHEADERS        =  \
        EngineImplements.h     \
        EngineLevel0.h         \
        $(EXTRANOINSTHEADERS)

INCLIBHEADERS           =  \
        $(INCLIBDIR)/EngineBase.h          \
        $(EXTRALIBHEADERS)

LIBNODISTHEADERS        =

LIBINSTALLSOURCES       =
LIBCOMPILESOURCES       =  $(LIBCXXSOURCEFILES)  $(LIBINSTANTIATIONS)

##
##    List of Libraries.
##

LIB_STATIC              =  libfsgEngine.staticd.a
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
fshogi_interface_includedir       =  $(fshogi_includedir)/Engine
fshogi_interface_libdir           =  $(fshogi_libdir)/Engine

fshogi_interface_include_HEADERS  =  $(INCLIBHEADERS)

dist_noinst_HEADERS               =  $(LIBNOINSTHEADERS)

fshogi_interface_lib_LTLIBRARIES  =  $(LIB_SHARED)
fshogi_interface_lib_LIBRARIES    =  $(LIB_STATIC)

##
##    Build Libraries.
##

libfsgEngine_staticd_a_SOURCES   =  $(LIBCOMPILESOURCES)

