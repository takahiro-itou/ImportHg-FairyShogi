
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
EXTRANOINSTDATA         =
EXTRANOINSTHEADERS      =
EXTRALIBHEADERS         =

LIBCXXSOURCEFILES       =  \
        EngineBase.cpp         \
        EngineImplements.cpp   \
        EngineLevel0.cpp       \
        EngineLevel1.cpp       \
        EngineLevel2.cpp       \
        EngineLevel3.cpp       \
        EngineLevel4.cpp       \
        $(EXTRALIBSOURCES)

LIBINSTANTIATIONS       =
LIBCXXINLINEFILES       =

LIBNOINSTDATA           =  \
        CMakeLists.txt      \
        $(EXTRANOINSTDATA)
LIBNOINSTHEADERS        =  \
        EngineImplements.h     \
        EngineLevel0.h         \
        EngineLevel1.h         \
        EngineLevel2.h         \
        EngineLevel3.h         \
        EngineLevel4.h         \
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

fshogi_includedir              =  $(includedir)/FairyShogi
fshogi_libdir                  =  $(libdir)
fshogi_engine_includedir       =  $(fshogi_includedir)/Engine
fshogi_engine_libdir           =  $(fshogi_libdir)/Engine

fshogi_engine_include_HEADERS  =  $(INCLIBHEADERS)

dist_noinst_DATA               =  $(LIBNOINSTDATA)
dist_noinst_HEADERS            =  $(LIBNOINSTHEADERS)

fshogi_engine_lib_LTLIBRARIES  =  $(LIB_SHARED)
fshogi_engine_lib_LIBRARIES    =  $(LIB_STATIC)

##
##    Build Libraries.
##

libfsgEngine_staticd_a_SOURCES   =  $(LIBCOMPILESOURCES)

