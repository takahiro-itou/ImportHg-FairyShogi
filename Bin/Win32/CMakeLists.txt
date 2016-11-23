
Set (FSHOGI_WIN32_SOURCES
        BoardScreen.cpp
        ChoiceScreen.cpp
        DiceScreen.cpp
        EngineProcess.cpp
        FairyShogiApp.cpp
        FairyShogiWin32.cpp
        PromotionScreen.cpp
        ScreenLayer.cpp
        Resources.rc
)

Set (WIN32_COMMONLIBS
        ${PROJECT_NAME}-${LIBRARIES_TARGET_PREFIX}Win32
        Gdi32
)

Add_Executable (FairyShogiWin32   WIN32  ${FSHOGI_WIN32_SOURCES})
Target_Link_Libraries (FairyShogiWin32   ${WIN32_COMMONLIBS})

