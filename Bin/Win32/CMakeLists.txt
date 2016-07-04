
set (FSHOGI_WIN32_SOURCES
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
set (WIN32_COMMONLIBS
        fsgWin32  fsgInterface  fsgEngine  fsgGame
        Gdi32
)

add_executable (FairyShogiWin32   ${FSHOGI_WIN32_SOURCES})
target_link_libraries (FairyShogiWin32  ${WIN32_COMMONLIBS})

