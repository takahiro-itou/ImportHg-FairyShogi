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
#include    "PromotionScreen.h"

#include    "FairyShogi/Common/ActionView.h"
#include    "FairyShogi/Interface/BitmapImage.h"
#include    "FairyShogi/Interface/GameController.h"

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

#if !defined( UTL_HELP_UNUSED_ARGUMENT )
#    define     UTL_HELP_UNUSED_ARGUMENT(var)   (void)(var)
#endif

#include    <fstream>

using   namespace   FAIRYSHOGI_NAMESPACE;

namespace  {

constexpr   char
g_szClassName[] = "FairyShogiWindow";

Interface::BoardScreen      g_scrBoard;
Interface::PromotionScreen  g_scrProm;

/**   マウスのキャプチャフラグ。    **/
HWND                    g_hCapture;

//
//    画面に関する定数。
//

constexpr   int     POS_NUM_COLS        = 5;
constexpr   int     POS_NUM_ROWS        = 5;

constexpr   int     BOARD_TOP_OFFSET    = 1;
constexpr   int     BOARD_LEFT_OFFSET   = 0;
constexpr   int     LEFT_MARGIN         = 64;
constexpr   int     TOP_MARGIN          = 64;
constexpr   int     SQUARE_WIDTH        = 64;
constexpr   int     SQUARE_HEIGHT       = 64;
constexpr   int     VIEW_NUM_COLS       = (POS_NUM_COLS);
constexpr   int     VIEW_NUM_ROWS       = (POS_NUM_ROWS) + 2;

constexpr   int     VIEW_BOARD_LEFT     = 0;
constexpr   int     VIEW_BOARD_TOP      = 0;
constexpr   int     VIEW_BOARD_WIDTH    = (VIEW_NUM_COLS + 2) * SQUARE_WIDTH;
constexpr   int     VIEW_BOARD_HEIGHT   = 640;

constexpr   int     WINDOW_WIDTH        = 832;
constexpr   int     WINDOW_HEIGHT       = 640;

constexpr   int     KIFU_VIEW_LEFT      = LEFT_MARGIN
        + ((VIEW_NUM_COLS + 1) * SQUARE_WIDTH);
constexpr   int     KIFU_VIEW_WIDTH     = WINDOW_WIDTH - KIFU_VIEW_LEFT;
constexpr   int     KIFU_FONT_HEIGHT    = 24;

Interface::BitmapImage      g_imgScreen;
Interface::BitmapImage      g_imgBoard;
Interface::BitmapImage      g_imgPromote;

}   //  End of (Unnamed) namespace.

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

    const   Interface::ScreenLayer::EventResult
        evtRet  = g_scrBoard.onLButtonDown(fwKeys, xPos, yPos);

    if ( evtRet == Interface::ScreenLayer::EH_RESULT_REDRAW ) {
        //  再描画を行う。  //
        ::InvalidateRect(hWnd, NULL, FALSE);
    }

    ::SetCapture(hWnd);
    g_hCapture  = hWnd;

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

    const   Interface::ScreenLayer::EventResult
        evtRet  = g_scrBoard.onLButtonUp(fwKeys, xPos, yPos);

    const   Interface::BoardScreen::ScreenState
        bssCurStat  = g_scrBoard.getCurrentState();

    if ( bssCurStat == Interface::BoardScreen::BSLS_SHOW_PROMOTION )
    {
        const   Interface::BoardScreen::OptionArray
            &vOpts  = g_scrBoard.getPromotionList();
        g_scrProm.setSelectionList(vOpts);
        g_scrProm.setVisibleFlag(Interface::ScreenLayer::LV_ENABLED);
    }

    if ( evtRet == Interface::ScreenLayer::EH_RESULT_REDRAW ) {
        //  再描画を行う。  //
        ::InvalidateRect(hWnd, NULL, FALSE);
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


    const   Interface::ScreenLayer::EventResult
        evtRet  = g_scrBoard.onMouseMove(fwKeys, xPos, yPos);

    if ( evtRet == Interface::ScreenLayer::EH_RESULT_REDRAW ) {
        //  再描画を行う。  //
        ::InvalidateRect(hWnd, NULL, FALSE);
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

    //  メイン画面を描画する。  //
    g_scrBoard.drawScreenLayer( &g_imgBoard );
    g_imgScreen.copyRectangle(
            g_scrBoard.getLeft(),
            g_scrBoard.getTop(),
            g_scrBoard.getWidth(),
            g_scrBoard.getHeight(),
            g_imgBoard,
            0, 0);

    //  成り駒選択画面を表示する。      //
    if ( g_scrProm.getVisibleFlag() != Interface::ScreenLayer::LV_HIDDEN )
    {
        g_scrProm.drawScreenLayer( &g_imgPromote );
    }
    g_imgScreen.copyRectangle(
            g_scrProm.getLeft(),
            g_scrProm.getTop(),
            g_scrProm.getWidth(),
            g_scrProm.getHeight(),
            g_imgPromote,
            0, 0);

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

    CREATESTRUCT    cs;
    cs.dwExStyle    =   WS_EX_CLIENTEDGE;
    cs.style        =   WS_CAPTION | WS_SYSMENU | WS_MINIMIZEBOX;
    cs.style        |=  WS_OVERLAPPED;

    cs.x            =   CW_USEDEFAULT;
    cs.y            =   CW_USEDEFAULT;
    cs.cx           =   WINDOW_WIDTH;
    cs.cy           =   WINDOW_HEIGHT;

    //  メニューを作成する。    //
    HMENU   hMenu   = (NULL);

    //  ウィンドウを作成する。  //
    hWnd    = ::CreateWindowEx(
                    cs.dwExStyle,
                    wcEx.lpszClassName,  "Fairy Shogi (WIN32)",
                    cs.style,
                    cs.x,  cs.y,   cs.cx,  cs.cy,
                    NULL,  hMenu,  hInst,  NULL);

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

    if ( g_scrProm.setupBitmapImages("Pieces.bmp") != ERR_SUCCESS )
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
    g_scrBoard.setLeft  (VIEW_BOARD_LEFT);
    g_scrBoard.setTop   (VIEW_BOARD_TOP);
    g_scrBoard.setWidth (VIEW_BOARD_WIDTH);
    g_scrBoard.setHeight(VIEW_BOARD_HEIGHT);

    g_scrBoard.resetGame();
    g_hCapture  = NULL;

    g_scrProm.setLeft  (0);
    g_scrProm.setTop   (VIEW_BOARD_TOP);
    g_scrProm.setWidth (SQUARE_WIDTH * 10);
    g_scrProm.setHeight(SQUARE_HEIGHT * 2);

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
