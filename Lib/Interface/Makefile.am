
##
##    ライブラリのビルドとインストール。
##

##
##    List of Directories.
##

MODULE_DIR_NAME         =  Interface
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
        ConsoleInterface.cpp    \
        GameController.cpp      \
        GraphicalInterface.cpp  \
        PixelMatrix.cpp         \
        ${EXTRA_LIBRARY_SOURCE_FILES}

LIBRARY_INSTANTIATIONS      =
LIBRARY_INLINE_FILES        =

DIST_NOINST_DATA_FILES      =  \
        CMakeLists.txt              \
        ${EXTRA_NOINST_DATA_FILES}

DIST_NOINST_HEADER_FILES    =  \
        ${EXTRA_NOINST_HEADER_FILES}

INCLIB_HEADER_FILES         =  \
        ${INCLIB_SOURCE_DIR}/ConsoleInterface.h    \
        ${INCLIB_SOURCE_DIR}/GameController.h      \
        ${INCLIB_SOURCE_DIR}/GraphicalInterface.h  \
        ${INCLIB_SOURCE_DIR}/PixelMatrix.h         \
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

STATIC_LIBRARIES_LIST   =  libfsgInterface.staticd.a
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

libfsgInterface_staticd_a_SOURCES   =  ${LIBRARY_SOURCE_FILES}

