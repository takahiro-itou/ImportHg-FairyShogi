//  -*-  coding: utf-8; mode: c++  -*-  //
/*************************************************************************
**                                                                      **
**                      ---  Fairy Shogi Game  ---                      **
**                                                                      **
**                                                                      **
**          Copyright (C), 2015-2016, Takahiro Itou                     **
**          All Rights Reserved.                                        **
**                                                                      **
*************************************************************************/

/**
**      アプリケーション本体。
**
**      @file       Bin/Win32/FairyShogiWin32.cpp
**/

#include    "FairyShogi/Common/FairyShogiTypes.h"

#include    "BoardScreen.h"
#include    "DiceScreen.h"
#include    "PromotionScreen.h"
#include    "Resources.h"

#include    "FairyShogi/Common/ActionView.h"
#include    "FairyShogi/Common/HelperMacros.h"
#include    "FairyShogi/Common/MersenneTwister.h"
#include    "FairyShogi/Interface/BitmapImage.h"

#if !defined( FAIRYSHOGI_WIN32_INCLUDED_SYS_WINDOWS_H )
#    define     STRICT
#    define     WIN32_LEAN_AND_MEAN
#    include    <windows.h>
#    define     FAIRYSHOGI_WIN32_INCLUDED_SYS_WINDOWS_H
#endif

#if !defined( FAIRYSHOGI_WIN32_INCLUDED_SYS_WINGDI_H )
#    include    <Wingdi.h>
#    define     FAIRYSHOGI_WIN32_INCLUDED_SYS_WINGDI_H
#endif

#include    <cstdlib>
#include    <fstream>
#include    <sstream>
#include    <time.h>

using   namespace   FAIRYSHOGI_NAMESPACE;

namespace  {

constexpr   char
g_szClassName[] = "FairyShogiWindow";

Interface::BoardScreen      g_scrBoard;
Interface::DiceScreen       g_scrDice;
Interface::PromotionScreen  g_scrProm;

/**   マウスのキャプチャフラグ。    **/
HWND                    g_hCapture;

//
//    画面に関する定数。
//

CONSTEXPR_VAR   int     POS_NUM_COLS        =  5;
CONSTEXPR_VAR   int     POS_NUM_ROWS        =  5;

CONSTEXPR_VAR   int     BOARD_TOP_OFFSET    =  1;
CONSTEXPR_VAR   int     BOARD_LEFT_OFFSET   =  0;
CONSTEXPR_VAR   int     LEFT_MARGIN         =  64;
CONSTEXPR_VAR   int     TOP_MARGIN          =  64;
CONSTEXPR_VAR   int     SQUARE_WIDTH        =  64;
CONSTEXPR_VAR   int     SQUARE_HEIGHT       =  64;
CONSTEXPR_VAR   int     VIEW_NUM_COLS       =  (POS_NUM_COLS);
CONSTEXPR_VAR   int     VIEW_NUM_ROWS       =  (POS_NUM_ROWS) + 2;

CONSTEXPR_VAR   int     VIEW_BOARD_LEFT     =  0;
CONSTEXPR_VAR   int     VIEW_BOARD_TOP      =  0;
CONSTEXPR_VAR   int
VIEW_BOARD_WIDTH    = (VIEW_NUM_COLS + 2) * SQUARE_WIDTH;

CONSTEXPR_VAR   int     VIEW_BOARD_HEIGHT   =  640;

CONSTEXPR_VAR   int     WINDOW_WIDTH        =  832;
CONSTEXPR_VAR   int     WINDOW_HEIGHT       =  640;

CONSTEXPR_VAR   int     DICE_WIDTH          =  128;
CONSTEXPR_VAR   int     DICE_HEIGHT         =  128;

CONSTEXPR_VAR   int     DICE_SCREEN_WIDTH   =  384;
CONSTEXPR_VAR   int     DICE_SCREEN_HEIGHT  =  384;

CONSTEXPR_VAR   int     KIFU_VIEW_LEFT      =  LEFT_MARGIN
        + ((VIEW_NUM_COLS + 1) * SQUARE_WIDTH);

CONSTEXPR_VAR   int     KIFU_VIEW_WIDTH     =  WINDOW_WIDTH - KIFU_VIEW_LEFT;
CONSTEXPR_VAR   int     KIFU_FONT_HEIGHT    =  24;

CONSTEXPR_VAR   int
CURRENT_DICE_LEFT       =  KIFU_VIEW_WIDTH + SQUARE_WIDTH;

CONSTEXPR_VAR   int
CURRENT_DICE_TOP        =  SQUARE_HEIGHT;

CONSTEXPR_VAR   int
CURRENT_DICE_RIGHT      =  CURRENT_DICE_LEFT + DICE_WIDTH;

CONSTEXPR_VAR   int
CURRENT_DICE_BOTTOM     =  CURRENT_DICE_TOP + DICE_HEIGHT;

CONSTEXPR_VAR   int
START_ENGINE_LEFT       =  CURRENT_DICE_RIGHT + 32;

CONSTEXPR_VAR   int
START_ENGINE_TOP        =  CURRENT_DICE_TOP;

CONSTEXPR_VAR   int
START_ENGINE_RIGHT      =  START_ENGINE_LEFT + DICE_WIDTH;

CONSTEXPR_VAR   int
START_ENGINE_BOTTOM     =  START_ENGINE_TOP + DICE_HEIGHT;

CONSTEXPR_VAR   int
UNDO_BUTTON_LEFT        =  CURRENT_DICE_LEFT;

CONSTEXPR_VAR   int
UNDO_BUTTON_TOP         =  CURRENT_DICE_BOTTOM + 32;

CONSTEXPR_VAR   int
UNDO_BUTTON_RIGHT       =  UNDO_BUTTON_LEFT + DICE_WIDTH;

CONSTEXPR_VAR   int
UNDO_BUTTON_BOTTOM      =  UNDO_BUTTON_TOP + DICE_HEIGHT;

CONSTEXPR_VAR   int
RESOURCE_ID_RUN_ENGINE  =  16;

CONSTEXPR_VAR   int
RESOURCE_ID_UNDO        =  14;


Interface::BitmapImage      g_imgScreen;
Interface::BitmapImage      g_imgDice;
Interface::BitmapImage      g_imgWork;

Interface::BitmapImage      g_imgBoard;
Interface::BitmapImage      g_imgPromote;

//
//  乱数。
//

typedef     Common::MersenneTwister             RandomGenerator;
typedef     RandomGenerator::TResultInt         RandResult;

static  CONSTEXPR_VAR   RandResult
RANDOM_MAX_VALUE    = RandomGenerator::MaxValue<28>::VALUE;

RandomGenerator             g_rndGen;

}   //  End of (Unnamed) namespace.

//----------------------------------------------------------------
/**   メニュー項目を選択した時のイベントハンドラ。
**
**/

LRESULT
onCommandMenuClick(
        const   HWND    hWnd,
        const   UINT    wID,
        const   UINT    wNotify)
{
    Interface::BoardScreen  & scrBoard  = g_scrBoard;

    switch ( wID ) {
    case  MENU_ID_FILE_EXIT:
        if ( ::MessageBox(
                        hWnd,
                        "Exit OK?", NULL,
                        MB_YESNO | MB_ICONQUESTION) == IDYES )
        {
            ::PostQuitMessage(0);
        }
        break;

    case  MENU_ID_DICE_MANUAL:
        break;
    case  MENU_ID_DICE_AUTO:
        break;

    case  MENU_ID_BLACK_MAN:
        break;
    case  MENU_ID_BLACK_FIRST + 0:
    case  MENU_ID_BLACK_FIRST + 1:
    case  MENU_ID_BLACK_FIRST + 2:
    case  MENU_ID_BLACK_FIRST + 3:
    case  MENU_ID_BLACK_FIRST + 4:
        scrBoard.setComputerLevel(
                Common::PLAYER_BLACK,   wID - MENU_ID_BLACK_FIRST);
        break;

    case  MENU_ID_WHITE_MAN:
        break;
    case  MENU_ID_WHITE_FIRST + 0:
    case  MENU_ID_WHITE_FIRST + 1:
    case  MENU_ID_WHITE_FIRST + 2:
    case  MENU_ID_WHITE_FIRST + 3:
    case  MENU_ID_WHITE_FIRST + 4:
        scrBoard.setComputerLevel(
                Common::PLAYER_WHITE,   wID - MENU_ID_WHITE_FIRST);
        break;

    case  MENU_ID_TURN_BLACK:
        break;
    case  MENU_ID_TURN_WHITE:
        break;
    }

    return ( 0 );
}

//----------------------------------------------------------------
/**   マウスボタンを押した時のイベントハンドラ。
**
**/

LRESULT
onLButtonDown(
        const   HWND    hWnd,
        const   DWORD   fwKeys,
        const   UINT    xPos,
        const   UINT    yPos)
{
    UTL_HELP_UNUSED_ARGUMENT(fwKeys);

    Interface::ScreenLayer::EventResult
            evtRet  = Interface::ScreenLayer::EH_RESULT_SUCCESS;

    if ( g_scrDice.getVisibleFlag() == Interface::ScreenLayer::LV_ENABLED )
    {
        //  ダイス選択中。  //
        return ( 0 );
    }

    if ( g_scrProm.getVisibleFlag() == Interface::ScreenLayer::LV_ENABLED )
    {
        //  成り駒選択中。  //
        return ( 0 );
    }

    {
        evtRet  = g_scrBoard.onLButtonDown(fwKeys, xPos, yPos);
    }

    if ( evtRet == Interface::ScreenLayer::EH_RESULT_REDRAW ) {
        //  再描画を行う。  //
        ::InvalidateRect(hWnd, NULL, FALSE);
        ::UpdateWindow(hWnd);
    }

    return ( 0 );
}

//----------------------------------------------------------------
/**   マウスボタンを離した時のイベントハンドラ。
**
**/

LRESULT
onLButtonUpInDiceScreen()
{
    Interface::BoardScreen  & scrBoard  = g_scrBoard;

    const  Interface::ChoiceScreen::ChoiceIndex
        pidSel  = g_scrDice.getUserSelect();

    if ( pidSel == 8 ) {
        //  待ったをする。  //
        scrBoard.playBackward();
        g_scrDice.setVisibleFlag(Interface::ScreenLayer::LV_HIDDEN);
        return ( 0 );
    }

    if ( pidSel == 7 ) {
        //  乱数を初期化する。  //
        g_rndGen.setSeedValue(::time(nullptr));
        ::MessageBox(NULL,  "Set Random Seed By Current Time", "OK", MB_OK);
    }
    if ( pidSel >= 6 ) {
        //  乱数を使う。    //
        g_scrDice.setVisibleFlag(Interface::ScreenLayer::LV_HIDDEN);
        const  uint32_t
            rv  =  (g_rndGen.getNext() & RANDOM_MAX_VALUE);
        const  int  rn
            =  (rv * Common::DICE_MAX_VALUE) / (RANDOM_MAX_VALUE + 1);
        scrBoard.setConstraint(rn + 1);
    } else if ( pidSel >= 0 ) {
        g_scrDice.setVisibleFlag(Interface::ScreenLayer::LV_HIDDEN);
        scrBoard.setConstraint(pidSel + 1);
    }

    scrBoard.clearSelection();
    scrBoard.updateHighLightInfo();

    return ( 0 );
}

//----------------------------------------------------------------
/**   マウスボタンを離した時のイベントハンドラ。
**
**/

LRESULT
onLButtonUp(
        const   HWND    hWnd,
        const   DWORD   fwKeys,
        const   UINT    xPos,
        const   UINT    yPos)
{
    UTL_HELP_UNUSED_ARGUMENT(fwKeys);

    g_hCapture  = (NULL);
    ::ReleaseCapture();

    Interface::ScreenLayer::EventResult
            evtRet  = Interface::ScreenLayer::EH_RESULT_SUCCESS;

    Interface::BoardScreen  & scrBoard  = g_scrBoard;
    Interface::BoardScreen::GameInterface  &
            giGame  = scrBoard.getGameController();

    //  ダイス選択中。  //
    if ( g_scrDice.getVisibleFlag() == Interface::ScreenLayer::LV_ENABLED )
    {
        evtRet  = g_scrDice.dispatchLButtonUp(fwKeys, xPos, yPos);
        onLButtonUpInDiceScreen();
        ::InvalidateRect(hWnd, NULL, FALSE);
        ::UpdateWindow(hWnd);
        return ( 0 );
    }

    //  成り駒選択中。  //
    if ( g_scrProm.getVisibleFlag() == Interface::ScreenLayer::LV_ENABLED )
    {
        evtRet  = g_scrProm.dispatchLButtonUp(fwKeys, xPos, yPos);
        const  PieceIndex   pidSel  = g_scrProm.getUserSelect();
        if ( pidSel >= 0 ) {
            g_scrProm.setVisibleFlag(Interface::ScreenLayer::LV_HIDDEN);
            scrBoard.setPromotionOption(pidSel);
        }
        ::InvalidateRect(hWnd, NULL, FALSE);
        ::UpdateWindow(hWnd);
        return ( 0 );
    }

    //  ダイス選択画面を表示する。  //
    if ( (CURRENT_DICE_LEFT <= xPos) && (xPos < CURRENT_DICE_RIGHT)
            && (CURRENT_DICE_TOP <= yPos) && (yPos < CURRENT_DICE_BOTTOM) )
    {
        if ( giGame.isCheckState(giGame.getCurrentPlayer()) ) {
            giGame.setConstraint(Common::DICE_ANY_MOVE);
            ::InvalidateRect(hWnd, NULL, FALSE);
            ::UpdateWindow(hWnd);
            ::MessageBox(hWnd, "CHECK", NULL, MB_OK);
            return ( 0 );
        }

        g_scrDice.setSelectionList(giGame.getCurrentPlayer());
        g_scrDice.setVisibleFlag(Interface::ScreenLayer::LV_ENABLED);
        ::InvalidateRect(hWnd, NULL, FALSE);
        ::UpdateWindow(hWnd);
        return ( 0 );
    }

    //  思考エンジン起動。  //
    if (      (START_ENGINE_LEFT <= xPos) && (xPos < START_ENGINE_RIGHT)
            && (START_ENGINE_TOP <= yPos) && (yPos < START_ENGINE_BOTTOM) )
    {
        Common::ActionView  actData;
        std::stringstream   ss;

        scrBoard.clearSelection();

        if ( giGame.computeBestAction(actData) != ERR_SUCCESS ) {
            ::MessageBox(hWnd, "No Legal Actions", "GAME OVER", MB_OK);
            ::InvalidateRect(hWnd, NULL, FALSE);
            return ( 0 );
        }
        ss  <<  (actData.xDispOldCol)   <<  (actData.yDispOldRow)
            <<  (actData.xDispNewCol)   <<  (actData.yDispNewRow);
        ss  <<  "\n# DEBUG : "
            <<  "\nxPlayOldCol = "  <<  (actData.xPlayOldCol)
            <<  "\nyPlayOldRow = "  <<  (actData.yPlayOldRow)
            <<  "\nxPlayNewCol = "  <<  (actData.xPlayNewCol)
            <<  "\nyPlayNewRow = "  <<  (actData.yPlayNewRow)
            <<  "\nfpAfter     = "  <<  (actData.fpAfter)
            <<  "\nfpMoved     = "  <<  (actData.fpMoved)
            <<  "\nfpCatch     = "  <<  (actData.fpCatch)
            <<  "\nhpiDrop     = "  <<  (actData.hpiDrop);
        if ( ::MessageBox(
                        hWnd, ss.str().c_str(), "Best Move",
                        MB_OKCANCEL) == IDOK )
        {
            scrBoard.playForward(actData);
        }
        ::InvalidateRect(hWnd, NULL, FALSE);
        ::UpdateWindow(hWnd);
        return ( 0 );
    }


    //  待ったボタン。  //
    if (      (UNDO_BUTTON_LEFT <= xPos) && (xPos < UNDO_BUTTON_RIGHT)
            && (UNDO_BUTTON_TOP <= yPos) && (yPos < UNDO_BUTTON_BOTTOM) )
    {
        //  待ったをする。  //
        scrBoard.playBackward();
        g_scrDice.setVisibleFlag(Interface::ScreenLayer::LV_HIDDEN);
        ::InvalidateRect(hWnd, NULL, FALSE);
        ::UpdateWindow(hWnd);
        return ( 0 );
    }

    evtRet  = scrBoard.onLButtonUp(fwKeys, xPos, yPos);
    const   Interface::BoardScreen::ScreenState
        bssCurStat  = scrBoard.getCurrentState();

    if ( bssCurStat == Interface::BoardScreen::BSLS_SHOW_PROMOTION )
    {
        const   Interface::BoardScreen::OptionArray
            &vOpts  = scrBoard.getPromotionList();
        g_scrProm.setSelectionList(vOpts);
        g_scrProm.setVisibleFlag(Interface::ScreenLayer::LV_ENABLED);
    }

    if ( evtRet == Interface::ScreenLayer::EH_RESULT_REDRAW ) {
        //  再描画を行う。  //
        ::InvalidateRect(hWnd, NULL, FALSE);
        ::UpdateWindow(hWnd);
    }

    return ( 0 );
}

//----------------------------------------------------------------
/**   マウスを移動させた時のイベントハンドラ。
**
**/

LRESULT
onMouseMove(
        const   HWND    hWnd,
        const   DWORD   fwKeys,
        const   UINT    xPos,
        const   UINT    yPos)
{
    UTL_HELP_UNUSED_ARGUMENT(fwKeys);

    Interface::ScreenLayer::EventResult
            evtRet  = Interface::ScreenLayer::EH_RESULT_SUCCESS;

    if ( g_scrProm.getVisibleFlag() == Interface::ScreenLayer::LV_ENABLED )
    {
        //  成り駒選択中。  //
        return ( 0 );
    }

    evtRet  = g_scrBoard.onMouseMove(fwKeys, xPos, yPos);
    if ( evtRet == Interface::ScreenLayer::EH_RESULT_REDRAW ) {
        //  再描画を行う。  //
        ::InvalidateRect(hWnd, NULL, FALSE);
        ::UpdateWindow(hWnd);
    }

    return ( 0 );
}

//----------------------------------------------------------------
/**   画面描画イベントハンドラ。
**
**/

LRESULT
onPaint(
        const   HWND    hWnd,
        const   HDC     hDC)
{
    //  何らかの理由で、マウスボタンが離された事実が、  //
    //  メインウィンドウに通知されなかった時の処理。    //
    //  例えば、マウスボタンを押して、AlT+Tab キーで    //
    //  別のウィンドウに切り替え、ボタンを離した等。    //
    if ( (g_hCapture) == hWnd ) {
        if ( ::GetCapture() != g_hCapture ) {
            g_scrBoard.clearSelection();
        }
    }

    g_imgScreen.drawRectangle(
            0, 0,
            WINDOW_WIDTH, WINDOW_HEIGHT,
            0, 0, 0);

    //  メイン画面を描画する。  //
    {
        Interface::BitmapImage  &  imgWork  =  g_imgBoard;
        g_scrBoard.drawScreenLayer( & imgWork );
        g_imgScreen.copyRectangle(
                g_scrBoard.getLeft(),
                g_scrBoard.getTop(),
                g_scrBoard.getWidth(),
                g_scrBoard.getHeight(),
                imgWork,
                0, 0);
    }

    //  現在のダイスを表示する。    //
    {
        int     idxCol, idxRow;
        g_scrBoard.getDiceDisplayIndex(&idxCol, &idxRow);
#if 0
        const  Interface::BoardScreen::GameInterface  &
            giGame  =  g_scrBoard.getGameController();
        const  PlayerIndex  curTurn = giGame.getCurrentPlayer();

        int     curDice = giGame.getConstraint() - 1;
        if ( (curDice < 0) || (Common::DICE_MAX_VALUE <= curDice) ) {
            curDice = Common::DICE_DEFAULT_VALUE;
        }
#endif
        g_imgScreen.copyRectangle(
                CURRENT_DICE_LEFT,  CURRENT_DICE_TOP,
                DICE_WIDTH,         DICE_HEIGHT,
                g_imgDice,
                (idxCol * DICE_WIDTH),
                (idxRow * DICE_HEIGHT) );
    }

    //  現在のエンジンを表示する。  //
    {
        g_imgScreen.copyRectangle(
                START_ENGINE_LEFT,  START_ENGINE_TOP,
                DICE_WIDTH,         DICE_HEIGHT,
                g_imgDice,
                ((RESOURCE_ID_RUN_ENGINE % 6) * DICE_WIDTH),
                ((RESOURCE_ID_RUN_ENGINE / 6) * DICE_HEIGHT) );
    }

    //  待ったボタンを表示する。    //
    {
        g_imgScreen.copyRectangle(
                UNDO_BUTTON_LEFT,   UNDO_BUTTON_TOP,
                DICE_WIDTH,         DICE_HEIGHT,
                g_imgDice,
                ((RESOURCE_ID_UNDO % 6) * DICE_WIDTH),
                ((RESOURCE_ID_UNDO / 6) * DICE_HEIGHT) );
    }

    //  ダイス選択画面を表示する。  //
    if ( g_scrDice.getVisibleFlag() != Interface::ScreenLayer::LV_HIDDEN )
    {
        Interface::BitmapImage  &  imgWork  =  g_imgWork;

        g_imgScreen.drawTransparentRectangle(
                g_scrDice.getLeft() - 4,
                g_scrDice.getTop () - 4,
                g_scrDice.getWidth () + 8,
                g_scrDice.getHeight() + 8,
                255,  0,  0,  0);

        g_scrDice.drawScreenLayer( & imgWork );
        g_imgScreen.copyRectangle(
                g_scrDice.getLeft(),
                g_scrDice.getTop(),
                g_scrDice.getWidth(),
                g_scrDice.getHeight(),
                imgWork,
                0,  0);
    }

    //  成り駒選択画面を表示する。  //
    if ( g_scrProm.getVisibleFlag() != Interface::ScreenLayer::LV_HIDDEN )
    {
        Interface::BitmapImage  &  imgWork  =  g_imgPromote;

        g_scrProm.drawScreenLayer( & imgWork );
        g_imgScreen.copyRectangle(
                g_scrProm.getLeft(),
                g_scrProm.getTop(),
                g_scrProm.getWidth(),
                g_scrProm.getHeight(),
                imgWork,
                0, 0);
    }

    //  描画した内容を画面に表示する。  //
    g_imgScreen.drawBitmap(hDC, 0, 0, WINDOW_WIDTH, WINDOW_HEIGHT);

    return ( 0 );
}

//----------------------------------------------------------------
/**   画面描画用のイベントハンドラを呼び出す。
**
**/

LRESULT
callPaintHandler(
        const   HWND    hWnd)
{
    PAINTSTRUCT     psWork;
    const  HDC      hDC     = ::BeginPaint(hWnd, &psWork);
    const  LRESULT  retVal  = onPaint(hWnd, hDC);
    ::EndPaint(hWnd, &psWork);

    return ( retVal );
}

//----------------------------------------------------------------
/**   ウィンドウプロシージャ。
**
**/

LRESULT CALLBACK
WindowProc(
        HWND    hWnd,
        UINT    uMsg,
        WPARAM  wParam,
        LPARAM  lParam)
{
    switch ( uMsg ) {
    case  WM_COMMAND:
        if ( lParam == 0 ) {
            return ( onCommandMenuClick(
                             hWnd, LOWORD(wParam), HIWORD(wParam)) );
        }
        break;

    case  WM_DESTROY:
        //  ウィンドウを閉じた場合の処理。  //
        //  メインウィンドウを閉じたら、    //
        //  アプリケーションを終了する。    //
        ::PostQuitMessage(0);
        break;

    case  WM_LBUTTONDOWN:
        return ( onLButtonDown(
                         hWnd,  wParam, LOWORD(lParam), HIWORD(lParam)) );
        break;
    case  WM_LBUTTONUP:
        return ( onLButtonUp(
                         hWnd,  wParam, LOWORD(lParam), HIWORD(lParam)) );
        break;

    case  WM_MOUSEMOVE:
        return ( onMouseMove(
                         hWnd,  wParam, LOWORD(lParam), HIWORD(lParam)) );

    case  WM_PAINT:
        return ( callPaintHandler(hWnd) );
        break;

    default:
        return ( ::DefWindowProc(hWnd, uMsg, wParam, lParam) );
    }

    return ( 0 );
}

//----------------------------------------------------------------
/**   アプリケーションのエントリポイント。
**
**/

int  APIENTRY
WinMain(
        HINSTANCE   hInst,
        HINSTANCE,
        LPSTR       lpCmdLine,
        int         nCmdShow)
{
    HWND        hWnd;
    WNDCLASSEX  wcEx;

    //  ウィンドウクラスを登録する。    //
    wcEx.cbSize         = sizeof(WNDCLASSEX);
    wcEx.style          = CS_HREDRAW | CS_VREDRAW;
    wcEx.lpfnWndProc    = (WNDPROC)WindowProc;
    wcEx.cbClsExtra     = 0;
    wcEx.cbWndExtra     = 0;
    wcEx.hInstance      = hInst;
    wcEx.hIcon          = NULL;
    wcEx.hCursor        = ::LoadCursor(NULL, IDC_ARROW);
    wcEx.hbrBackground  = (HBRUSH)(COLOR_WINDOW + 1);
    wcEx.lpszMenuName   = NULL;
    wcEx.lpszClassName  = g_szClassName;
    wcEx.hIconSm        = 0;

    if ( ::RegisterClassEx(&wcEx) == 0 ) {
        return ( 0 );
    }

    //  メニューを作成する。    //
    HMENU   hmMain  =  (NULL);  //createMainMenu();

    //  ウィンドウ作成情報。    //
    CREATESTRUCT    cs;
    cs.dwExStyle    =   WS_EX_CLIENTEDGE;
    cs.style        =   WS_CAPTION | WS_SYSMENU | WS_MINIMIZEBOX;
    cs.style        |=  WS_OVERLAPPED;

    cs.x            =   CW_USEDEFAULT;
    cs.y            =   CW_USEDEFAULT;
    cs.cx           =   WINDOW_WIDTH;
    cs.cy           =   WINDOW_HEIGHT;

    //  ウィンドウのサイズを調整する。  //
    RECT    recWnd  =  { 0, 0, WINDOW_WIDTH, WINDOW_HEIGHT };
    ::AdjustWindowRectEx(&recWnd,  cs.style,  TRUE,  cs.dwExStyle);
    const  int  mw  =  (recWnd.right - recWnd.left);
    const  int  mh  =  (recWnd.bottom - recWnd.top);
    cs.cx           =  mw;
    cs.cy           =  mh;

    //  ウィンドウを作成する。  //
    hWnd    = ::CreateWindowEx(
                    cs.dwExStyle,
                    wcEx.lpszClassName,  "Fairy Shogi (WIN32)",
                    cs.style,
                    cs.x,  cs.y,    cs.cx,  cs.cy,
                    NULL,  hmMain,  hInst,  NULL);

    if ( hWnd == 0 ) {
        return ( 0 );
    }

    //  この瞬間に画像を準備する。  //
    if ( g_scrBoard.setupBitmapImages("Back.bmp", "Pieces.bmp")
            != ERR_SUCCESS )
    {
        ::MessageBox(hWnd,  "Graphic Files Not Found!", NULL,  MB_OK);
        return ( 0 );
    }

    if ( g_scrDice.setupBitmapImages("Dice.bmp") != ERR_SUCCESS )
    {
        ::MessageBox(hWnd,  "Graphic Files Not Found!", NULL,  MB_OK);
        return ( 0 );
    }

    if ( g_scrProm.setupBitmapImages("Pieces.bmp") != ERR_SUCCESS )
    {
        ::MessageBox(hWnd,  "Graphic Files Not Found!", NULL,  MB_OK);
        return ( 0 );
    }

    if ( g_imgDice.openBitmapFile("Dice.bmp")
            != ERR_SUCCESS )
    {
        ::MessageBox(hWnd,  "Graphic Files Not Found!", NULL,  MB_OK);
        return ( 0 );
    }

    //  バックバッファも準備する。  //
    HDC hDC = ::GetDC(hWnd);
    if ( g_imgScreen.createBitmap(WINDOW_WIDTH, WINDOW_HEIGHT, hDC)
            != ERR_SUCCESS )
    {
        ::MessageBox(hWnd,  "Not Enough Memory!",   NULL,  MB_OK);
    }

    if ( g_imgWork.createBitmap(WINDOW_WIDTH, WINDOW_HEIGHT, 24)
            != ERR_SUCCESS )
    {
        ::MessageBox(hWnd,  "Not Enough Memory!",   NULL,  MB_OK);
    }

    if ( g_imgBoard.createBitmap(WINDOW_WIDTH, WINDOW_HEIGHT, 24)
            != ERR_SUCCESS )
    {
        ::MessageBox(hWnd,  "Not Enough Memory!",   NULL,  MB_OK);
    }

    if ( g_imgPromote.createBitmap(WINDOW_WIDTH, WINDOW_HEIGHT, 24)
            != ERR_SUCCESS )
    {
        ::MessageBox(hWnd,  "Not Enough Memory!",   NULL,  MB_OK);
    }
    ::ReleaseDC(hWnd, hDC);

    //  グローバル変数を初期化する。    //
    g_rndGen.setSeedValue(13579);

    g_scrBoard.setLeft  (VIEW_BOARD_LEFT);
    g_scrBoard.setTop   (VIEW_BOARD_TOP);
    g_scrBoard.setWidth (VIEW_BOARD_WIDTH);
    g_scrBoard.setHeight(VIEW_BOARD_HEIGHT);

    g_scrProm.setLeft  (0);
    g_scrProm.setTop   (VIEW_BOARD_TOP);
    g_scrProm.setWidth (SQUARE_WIDTH * 10);
    g_scrProm.setHeight(SQUARE_HEIGHT * 2);

    g_scrDice.setSelectionList(Common::PLAYER_BLACK);
    g_scrDice.setLeft( (WINDOW_WIDTH  - DICE_SCREEN_WIDTH)  / 2 );
    g_scrDice.setTop ( (WINDOW_HEIGHT - DICE_SCREEN_HEIGHT) / 2 );
    g_scrDice.setWidth (DICE_SCREEN_WIDTH);
    g_scrDice.setHeight(DICE_SCREEN_HEIGHT);

    g_scrBoard.resetGame();
    g_hCapture  = NULL;

    //  ウィンドウを表示する。  //
    ::ShowWindow(hWnd, nCmdShow);
    ::UpdateWindow(hWnd);

    int     ret;
    MSG     msg;
    for (;;) {
        ret = ::GetMessage(&msg, NULL, 0, 0);
        if ( ret == 0 || ret == -1 ) {
            break;
        }
        ::TranslateMessage(&msg);
        ::DispatchMessage (&msg);
    }

    return ( msg.wParam );
}
