
##
##    ライブラリのビルドとインストール。
##

##
##    List of Directories.
##

SRCTOPDIR               =  @top_srcdir@
INCTOPDIR               =  $(SRCTOPDIR)/Include
INCPKGDIR               =  $(INCTOPDIR)/FairyShogi
INCLIBDIR               =  $(INCPKGDIR)/.Config

CNF_SRCTOPDIR           =  @top_builddir@
CNF_INCTOPDIR           =  $(CNF_SRCTOPDIR)/Include
CNF_INCPKGDIR           =  $(CNF_INCTOPDIR)/FairyShogi
CNF_INCLIBDIR           =  $(CNF_INCPKGDIR)/.Config

##
##    List of Source and Header Files.
##

EXTRALIBSOURCES         =
EXTRANOINSTDATA         =
EXTRANOINSTHEADERS      =
EXTRALIBHEADERS         =

LIBCXXSOURCEFILES       =  \
        $(EXTRALIBSOURCES)

LIBINSTANTIATIONS       =
LIBCXXINLINEFILES       =

LIBNOINSTDATA           =  \
        CMakeLists.txt      \
        $(EXTRANOINSTDATA)
LIBNOINSTHEADERS        =  \
        $(EXTRANOINSTHEADERS)

INCLIBHEADERS           =  \
        $(EXTRALIBHEADERS)

LIBNODISTHEADERS        =  \
        $(CNF_INCLIBDIR)/ConfiguredFairyShogi.h

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
##    List of Installs.
##

fshogi_includedir               =  $(includedir)/FairyShogi
fshogi_libdir                   =  $(libdir)
fshogi_config_includedir        =  $(fshogi_includedir)/.Config
fshogi_config_libdir            =  $(fshogi_libdir)/.Config

fshogi_config_include_HEADERS   =  $(INCLIBHEADERS)

dist_noinst_DATA                =  $(LIBNOINSTDATA)
dist_noinst_HEADERS             =  $(LIBNOINSTHEADERS)

fshogi_config_lib_LTLIBRARIES   =  $(LIB_SHARED)
fshogi_config_lib_LIBRARIES     =  $(LIB_STATIC)

##
##    List of (No Dist) Installs.
##

nodist_fshogi_config_include_HEADERS    =  $(LIBNODISTHEADERS)

##
##    Build Libraries.
##

