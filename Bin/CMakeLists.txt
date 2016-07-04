
set (COMMONSOURCES  CommandInterpreter.cpp)
set (COMMONLIBS     fsgInterface  fsgEngine  fsgGame)

add_executable (AutoMatch   AutoMatch.cpp   ${COMMONSOURCES})
add_executable (FairyShogi  FairyShogi.cpp  ${COMMONSOURCES})

target_link_libraries (AutoMatch   ${COMMONLIBS})
target_link_libraries (FairyShogi  ${COMMONLIBS})

##----------------------------------------------------------------
##
##    サブディレクトリの追加。
##

if ( ENABLE_WIN32 )
  add_subdirectory (Win32)
endif()

