
Set (COMMONSOURCES  CommandInterpreter.cpp)
Set (COMMONLIBS
        ${PROJECT_NAME}-${LIBRARIES_TARGET_PREFIX}Interface
)

Add_Executable (AutoMatch   AutoMatch.cpp   ${COMMONSOURCES})
Add_Executable (FairyShogi  FairyShogi.cpp  ${COMMONSOURCES})

Target_Link_Libraries (AutoMatch   ${COMMONLIBS})
Target_Link_Libraries (FairyShogi  ${COMMONLIBS})

##----------------------------------------------------------------
##
##    サブディレクトリの追加。
##

If ( ENABLE_WIN32 )
  Add_Subdirectory (Win32)
EndIf ()

If ( CURSES_FOUND )
  Add_SubDirectory (TextUI)
EndIf ()

