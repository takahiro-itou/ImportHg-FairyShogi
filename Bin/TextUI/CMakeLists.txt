
Set (FSHOGI_TEXTUI_SOURCES
        FairyShogiCurses.cpp
)

Set (TEXTUI_COMMONLIBS
        ${PROJECT_NAME}-${LIBRARIES_TARGET_PREFIX}TextUI
)

Add_Executable        (FairyShogiCurses  ${FSHOGI_TEXTUI_SOURCES})
Target_Link_Libraries (FairyShogiCurses  ${TEXTUI_COMMONLIBS})

