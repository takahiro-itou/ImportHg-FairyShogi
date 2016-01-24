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

namespace  {

constexpr   char
g_szClassName[] = "FairyShogiWindow";

/**
**    画面に表示する駒の名称。
**/

constexpr   const   char  *
s_tblPieceName[]    = {
    "",  "",
    "Pawn ",  "Sil. ",  "Gold ",  "Bis. ",  "Rook ",  "King ",
    "P.Pw ",  "P.Si ",  "P.Bi ",  "P.Rk ",
    "PawnV",  "Sil.V",  "GoldV",  "Bis.V",  "RookV",  "KingV"
    "P.PwV",  "P.SiV",  "P.BiV",  "P.RkV"
};

/**
**    画面に表示する持ち駒の名称。
**/

constexpr   const   char  *
s_tblHandName[]     =  {
    nullptr,
    "P",  "S",  "G",  "B",  "R",  "K",
    "P",  "S",  "G",  "B",  "R",  "K"
};


//
//    ダミー定数。
//

constexpr   int     POS_NUM_COLS        = 5;
constexpr   int     POS_NUM_ROWS        = 5;
constexpr   int     HANDS_WHITE_PAWN    = 0;
constexpr   int     HANDS_WHITE_KING    = 5;


constexpr   int     BOARD_TOP_OFFSET    = 1;
constexpr   int     BOARD_LEFT_OFFSET   = 0;
constexpr   int     LEFT_MARGIN         = 64;
constexpr   int     TOP_MARGIN          = 64;
constexpr   int     SQUARE_WIDTH        = 64;
constexpr   int     SQUARE_HEIGHT       = 64;
constexpr   int     VIEW_NUM_COLS       = (POS_NUM_COLS);
constexpr   int     VIEW_NUM_ROWS       = (POS_NUM_ROWS) + 2;

constexpr   int     WINDOW_WIDTH        = 832;
constexpr   int     WINDOW_HEIGHT       = 640;

constexpr   int     KIFU_VIEW_LEFT      = LEFT_MARGIN
        + ((VIEW_NUM_COLS + 1) * SQUARE_WIDTH);
constexpr   int     KIFU_VIEW_WIDTH     = WINDOW_WIDTH - KIFU_VIEW_LEFT;
constexpr   int     KIFU_FONT_HEIGHT    = 24;

int     g_selX;
int     g_selY;
int     g_movX;
int     g_movY;

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

    if ( (xPos < LEFT_MARGIN) || (yPos < TOP_MARGIN) ) {
        g_selX  = -1;
        g_selY  = -1;
        g_movX  = -1;
        g_movY  = -1;
        ::InvalidateRect(hWnd, NULL, TRUE);
        return ( 0 );
    }

    const  int  mx  = ((int)(xPos) - LEFT_MARGIN) / SQUARE_WIDTH;
    const  int  my  = ((int)(yPos) - TOP_MARGIN) / SQUARE_HEIGHT;

    if ( (VIEW_NUM_ROWS <= my) ) {
        g_selX  = -1;
        g_selY  = -1;
        g_movX  = -1;
        g_movY  = -1;
        ::InvalidateRect(hWnd, NULL, TRUE);
        return ( 0 );
    }
    if ( (my == 0) || (my == (POS_NUM_ROWS + BOARD_TOP_OFFSET)) ) {
        if ( (HANDS_WHITE_KING - HANDS_WHITE_PAWN + 1) <= mx ) {
            g_selX  = -1;
            g_selY  = -1;
            g_movX  = -1;
            g_movY  = -1;
            ::InvalidateRect(hWnd, NULL, TRUE);
            return ( 0 );
        } else {
            g_selX  = mx;
            g_selY  = my;
        }
    } else if ( (VIEW_NUM_COLS) <= mx ) {
        g_selX  = -1;
        g_selY  = -1;
    } else {
        g_selX  = mx;
        g_selY  = my;
    }

    g_movX  = -1;
    g_movY  = -1;
    ::InvalidateRect(hWnd, NULL, TRUE);

    if ( (g_selX >= 0) && (g_selY >= 0) ) {
        ::SetCapture(hWnd);
    }

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

    ::ReleaseCapture();

    if ( (g_selX < 0) || (g_selY < 0) ) {
        return ( 0 );
    }

    g_selX  = -1;
    g_selY  = -1;
    g_movX  = -1;
    g_movY  = -1;
    ::InvalidateRect(hWnd, NULL, TRUE);

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

    if ( (g_selX < 0) || (g_selY < 0) ) {
        return ( 0 );
    }

    const  int  mx  = ((int)(xPos) - LEFT_MARGIN) / SQUARE_WIDTH;
    const  int  my  = ((int)(yPos) - TOP_MARGIN) / SQUARE_HEIGHT;
    int     mvX, mvY;

    if ( (xPos < LEFT_MARGIN) || (yPos < TOP_MARGIN) ) {
        mvX = -1;
        mvY = -1;
        goto    label_redraw_board;
    }

    if ( (mx < BOARD_LEFT_OFFSET) || (my < BOARD_TOP_OFFSET)
            || (POS_NUM_COLS + BOARD_LEFT_OFFSET <= mx)
            || (POS_NUM_ROWS + BOARD_TOP_OFFSET  <= my) )
    {
        mvX = -1;
        mvY = -1;
    } else {
        mvX = mx;
        mvY = my;
    }

label_redraw_board:
    if ( (g_movX != mvX) || (g_movY != mvY) ) {
        g_movX  = mvX;
        g_movY  = mvY;
        ::InvalidateRect(hWnd, NULL, TRUE);
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
    int     sx, sy, dx, dy;

    //  盤面のマスを描画する。  //
    for ( int y = 0; y <= POS_NUM_ROWS; ++ y ) {
        sx  = ((BOARD_LEFT_OFFSET) * SQUARE_WIDTH) + LEFT_MARGIN;
        sy  = ((y + BOARD_TOP_OFFSET) * SQUARE_HEIGHT) + TOP_MARGIN;
        dx  = sx + (POS_NUM_COLS * SQUARE_WIDTH);
        dy  = sy;
        ::MoveToEx(hDC, sx, sy, NULL);
        ::LineTo  (hDC, dx, dy);
    }

    for ( int x = 0; x <= POS_NUM_COLS; ++ x ) {
        sx  = ((x + BOARD_LEFT_OFFSET) * SQUARE_WIDTH) + LEFT_MARGIN;
        sy  = ((BOARD_TOP_OFFSET) * SQUARE_HEIGHT) + TOP_MARGIN;
        dx  = sx;
        dy  = sy + (POS_NUM_ROWS * SQUARE_HEIGHT);
        ::MoveToEx(hDC, sx, sy, NULL);
        ::LineTo  (hDC, dx, dy);
    }

    //  選択しているマスがあれば強調表示。  //
    if ( (g_selX >= 0) && (g_selY >= 0) ) {
        HBRUSH  hbrBack = ::CreateSolidBrush( RGB(255, 255, 0) );
        sx  = ((g_selX) * SQUARE_WIDTH) + LEFT_MARGIN;
        sy  = ((g_selY) * SQUARE_HEIGHT) + TOP_MARGIN;

        HBRUSH  hbrOld  = (HBRUSH)::SelectObject(hDC, hbrBack);
        ::Rectangle(hDC, sx, sy, sx + SQUARE_WIDTH, sy + SQUARE_HEIGHT);
        ::SelectObject(hDC, hbrOld);
        ::DeleteObject(hbrBack);
    }

    //  移動先として現在マウスが示しているマスを強調表示。  //
    if ( (g_movX >= 0) && (g_movY >= 0) ) {
        HBRUSH  hbrBack = ::CreateSolidBrush( RGB(0, 0, 255) );
        sx  = ((g_movX) * SQUARE_WIDTH) + LEFT_MARGIN;
        sy  = ((g_movY) * SQUARE_HEIGHT) + TOP_MARGIN;

        HBRUSH  hbrOld  = (HBRUSH)::SelectObject(hDC, hbrBack);
        ::Rectangle(hDC, sx, sy, sx + SQUARE_WIDTH, sy + SQUARE_HEIGHT);
        ::SelectObject(hDC, hbrOld);
        ::DeleteObject(hbrBack);
    }

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

    //  グローバル変数を初期化する。    //
    g_selX  = -1;
    g_selY  = -1;
    g_movX  = -1;
    g_movY  = -1;

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
