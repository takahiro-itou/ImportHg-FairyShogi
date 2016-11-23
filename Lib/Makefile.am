
##
##    List of Directories.
##

SUBLIBS  =  Common  Helper  Game  Engine  Interface

if  FAIRYSHOGI_AMCNF_ENABLE_WINDOWS_H
SUBLIBS  +=  Win32
endif

if  FAIRYSHOGI_AMCNF_ENABLE_CURSES
SUBLIBS  +=  TextUI
endif

SUBDIRS  =  Tests  .Config  $(SUBLIBS)  .

##
##    List of Installs.
##

dist_noinst_DATA        =  \
        CMakeLists.txt

