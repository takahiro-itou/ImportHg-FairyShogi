
##
##    ライブラリのビルドとインストール。
##

##
##    List of Directories.
##

MODULE_DIR_NAME         =  Win32
SUBDIRS                 =  .  Tests

include  $(top_srcdir)/.M4/Makefile.DirList.inc

##
##    List of Source and Header Files.
##

EXTRA_LIBRARY_SOURCE_FILES  =
EXTRA_LIBRARY_HEADER_FILES  =
EXTRA_NOINST_DATA_FILES     =
EXTRA_NOINST_HEADER_FILES   =

LIBRARY_SOURCE_FILES        =  \
        Animation.cpp          \
        BitmapImage.cpp        \
        BitmapResource.cpp     \
        DialogWindow.cpp       \
        MatchDialog.cpp        \
        ${EXTRA_LIBRARY_SOURCE_FILES}

LIBRARY_INSTANTIATIONS      =
LIBRARY_INLINE_FILES        =

DIST_NOINST_DATA_FILES      =  \
        CMakeLists.txt              \
        ${EXTRA_NOINST_DATA_FILES}

DIST_NOINST_HEADER_FILES    =  \
        ${EXTRA_NOINST_HEADER_FILES}

INCLIB_HEADER_FILES         =  \
        ${INCLIB_SOURCE_DIR}/Animation.h         \
        ${INCLIB_SOURCE_DIR}/BitmapImage.h       \
        ${INCLIB_SOURCE_DIR}/BitmapResource.h    \
        ${INCLIB_SOURCE_DIR}/CommonResources.h   \
        ${INCLIB_SOURCE_DIR}/CommonResources.rc  \
        ${INCLIB_SOURCE_DIR}/DialogWindow.h      \
        ${INCLIB_SOURCE_DIR}/MatchDialog.h       \
        ${EXTRA_LIBRARY_HEADER_FILES}

INCLIB_NODIST_HEADER_FILES  =

LIBRARY_INSTALL_SRCFILES    =  \
        ${LIBRARY_INLINE_FILES}

LIBRARY_COMPILE_SRCFILES    =  \
        ${LIBRARY_SOURCE_FILES}    \
        ${LIBRARY_INSTANTIATIONS}

##
##    List of Libraries.
##

STATIC_LIBRARIES_LIST   =  libfsgWin32.staticd.a
SHARED_LIBRARIES_LIST   =

##
##    Internal Libraries.
##

##
##    Compile and Link Options.
##

AM_CPPFLAGS          =  \
        -I${INCTOP_SOURCE_DIR}
AM_CFLAGS               =
AM_CXXFLAGS             =

##
##    Include Common Install Settings.
##

include  $(top_srcdir)/.M4/Makefile.Install.inc

##
##    Build Libraries.
##

libfsgWin32_staticd_a_SOURCES   =  ${LIBRARY_SOURCE_FILES}

