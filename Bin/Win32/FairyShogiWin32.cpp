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

#if !defined( FAIRYSHOGI_WIN32_INCLUDED_SYS_WINDOWS_H )
#    define     STRICT
#    define     WIN32_LEAN_AND_MEAN
#    include    <windows.h>
#    define     FAIRYSHOGI_WIN32_INCLUDED_SYS_WINDOWS_H
#endif

#include    "FairyShogi/Common/FairyShogiTypes.h"

namespace  {

constexpr   char
g_szClassName[] = "FairyShogiWindow";

}   //  End of (Unnamed) namespace.

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
    cs.cx           =   CW_USEDEFAULT;
    cs.cy           =   CW_USEDEFAULT;

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
