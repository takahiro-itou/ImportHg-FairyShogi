
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
INCLIBDIR               =  $(INCPKGDIR)/Win32

##
##    List of Source and Header Files.
##

EXTRALIBSOURCES         =
EXTRANOINSTDATA         =
EXTRANOINSTHEADERS      =
EXTRALIBHEADERS         =

LIBCXXSOURCEFILES       =  \
        Animation.cpp       \
        BitmapImage.cpp     \
        BitmapResource.cpp  \
        DialogWindow.cpp    \
        MatchDialog.cpp     \
        $(EXTRALIBSOURCES)

LIBINSTANTIATIONS       =
LIBCXXINLINEFILES       =

LIBNOINSTDATA           =  \
        CMakeLists.txt      \
        $(EXTRANOINSTDATA)
LIBNOINSTHEADERS        =  \
        $(EXTRANOINSTHEADERS)

INCLIBHEADERS           =  \
        $(INCLIBDIR)/Animation.h         \
        $(INCLIBDIR)/BitmapImage.h       \
        $(INCLIBDIR)/BitmapResource.h    \
        $(INCLIBDIR)/CommonResources.h   \
        $(INCLIBDIR)/CommonResources.rc  \
        $(INCLIBDIR)/DialogWindow.h      \
        $(INCLIBDIR)/MatchDialog.h       \
        $(EXTRALIBHEADERS)

LIBNODISTHEADERS        =

LIBINSTALLSOURCES       =
LIBCOMPILESOURCES       =  $(LIBCXXSOURCEFILES)  $(LIBINSTANTIATIONS)

##
##    Suffix Rules.
##

SUFFIXES  =  .rc

.rc.o :
	windres  -i $<  -o $@  -I$(INCTOPDIR)

##
##    List of Libraries.
##

LIB_STATIC              =  libfsgWin32.staticd.a
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

fshogi_includedir             =  $(includedir)/FairyShogi
fshogi_libdir                 =  $(libdir)
fshogi_win32_includedir       =  $(fshogi_includedir)/Win32
fshogi_win32_libdir           =  $(fshogi_libdir)/Win32

fshogi_win32_include_HEADERS  =  $(INCLIBHEADERS)

dist_noinst_DATA              =  $(LIBNOINSTDATA)
dist_noinst_HEADERS           =  $(LIBNOINSTHEADERS)

fshogi_win32_lib_LTLIBRARIES  =  $(LIB_SHARED)
fshogi_win32_lib_LIBRARIES    =  $(LIB_STATIC)

##
##    Build Libraries.
##

libfsgWin32_staticd_a_SOURCES   =  $(LIBCOMPILESOURCES)

