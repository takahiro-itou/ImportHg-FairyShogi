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

Interface::BoardScreen  g_scrBoard;

/**   マウスのキャプチャフラグ。    **/
HWND                    g_hCapture;

/**
**    画面に表示する駒の名称。
**/

constexpr   const   char  *
s_tblPieceName[]    = {
    "",
    "Pawn ",  "Sil. ",  "Gold ",  "Bis. ",  "Rook ",  "King ",
    "P.Pw ",  "P.Si ",  "P.Bi ",  "P.Rk ",
    "PawnV",  "Sil.V",  "GoldV",  "Bis.V",  "RookV",  "KingV",
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

constexpr   int     POS_NUM_COLS        =  5;
constexpr   int     POS_NUM_ROWS        =  5;

constexpr   int     HANDS_BLACK_PAWN    = Game::BoardState::HAND_BLACK_PAWN;
constexpr   int     HANDS_BLACK_KING    = Game::BoardState::HAND_BLACK_KING;
constexpr   int     HANDS_WHITE_PAWN    = Game::BoardState::HAND_WHITE_PAWN;
constexpr   int     HANDS_WHITE_KING    = Game::BoardState::HAND_WHITE_KING;


constexpr   PieceIndex
s_tblHandEncBlack[] = {
    Game::BoardState::HAND_BLACK_PAWN,
    Game::BoardState::HAND_BLACK_SILVER,
    Game::BoardState::HAND_BLACK_GOLD,
    Game::BoardState::HAND_BLACK_BISHOP,
    Game::BoardState::HAND_BLACK_ROOK,
    Game::BoardState::HAND_BLACK_KING
};

constexpr   PieceIndex
s_tblHandEncWhite[] = {
    Game::BoardState::HAND_WHITE_PAWN,
    Game::BoardState::HAND_WHITE_SILVER,
    Game::BoardState::HAND_WHITE_GOLD,
    Game::BoardState::HAND_WHITE_BISHOP,
    Game::BoardState::HAND_WHITE_ROOK,
    Game::BoardState::HAND_WHITE_KING
};

//
//    画面に関する定数。
//

constexpr   int     BOARD_TOP_OFFSET    = 1;
constexpr   int     BOARD_LEFT_OFFSET   = 0;
constexpr   int     LEFT_MARGIN         = 64;
constexpr   int     TOP_MARGIN          = 64;
constexpr   int     SQUARE_WIDTH        = 64;
constexpr   int     SQUARE_HEIGHT       = 64;
constexpr   int     VIEW_NUM_COLS       = (POS_NUM_COLS);
constexpr   int     VIEW_NUM_ROWS       = (POS_NUM_ROWS) + 2;

constexpr   int     VIEW_BOARD_LEFT     = 64;
constexpr   int     VIEW_BOARD_TOP      = 64;
constexpr   int     VIEW_BOARD_WIDTH    = 64 * 5;
constexpr   int     VIEW_BOARD_HEIGHT   = 64 * (5 + 2);

constexpr   int     WINDOW_WIDTH        = 832;
constexpr   int     WINDOW_HEIGHT       = 640;

constexpr   int     KIFU_VIEW_LEFT      = LEFT_MARGIN
        + ((VIEW_NUM_COLS + 1) * SQUARE_WIDTH);
constexpr   int     KIFU_VIEW_WIDTH     = WINDOW_WIDTH - KIFU_VIEW_LEFT;
constexpr   int     KIFU_FONT_HEIGHT    = 24;

// int     g_selX;
// int     g_selY;
// int     g_movX;
// int     g_movY;

// std::ofstream               ofsKifu;

//Interface::GameController   gc;

Interface::BitmapImage      g_imgScreen;
Interface::BitmapImage      g_imgBoard;

// Interface::BitmapImage      g_imgBack;
// Interface::BitmapImage      g_imgPiece;

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
        evtRet  = g_scrBoard.onLButtonUp(fwKeys, xPos, yPos);

    if ( evtRet == Interface::ScreenLayer::EH_RESULT_REDRAW ) {
        //  再描画を行う。  //
        ::InvalidateRect(hWnd, NULL, FALSE);
    }

    ::SetCapture(hWnd);
    g_hCapture  = hWnd;

#if 0
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
#endif

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

    const   Interface::ScreenLayer::EventResult
        evtRet  = g_scrBoard.onLButtonUp(fwKeys, xPos, yPos);

    if ( evtRet == Interface::ScreenLayer::EH_RESULT_REDRAW ) {
        //  再描画を行う。  //
        ::InvalidateRect(hWnd, NULL, FALSE);
    }

#if 0
    if ( (g_selX < 0) || (g_selY < 0) ) {
        return ( 0 );
    }

    Interface::GameController::ActionViewList   actList;

    const  int  mx  = ((int)(xPos) - LEFT_MARGIN) / SQUARE_WIDTH;
    const  int  my  = ((int)(yPos) - TOP_MARGIN) / SQUARE_HEIGHT;

    if ( (mx < BOARD_LEFT_OFFSET) || (my < BOARD_TOP_OFFSET)
            || (POS_NUM_COLS + BOARD_LEFT_OFFSET <= mx)
            || (POS_NUM_ROWS + BOARD_TOP_OFFSET  <= my) )
    {
        goto    label_redaw_board;
    }
    if ( (mx == g_selX) && (my == g_selY) ) {
        goto    label_redaw_board;
    }

    if ( (g_selY == 0) ) {
        //  後手の持ち駒を打つ。    //
        gc.playPutAction(
                mx - BOARD_LEFT_OFFSET,
                my - BOARD_TOP_OFFSET,
                s_tblHandEncWhite[g_selX - BOARD_LEFT_OFFSET]);
    } else if ( g_selY == POS_NUM_ROWS + BOARD_TOP_OFFSET ) {
        //  先手の持ち駒を打つ。    //
        gc.playPutAction(
                mx - BOARD_LEFT_OFFSET,
                my - BOARD_TOP_OFFSET,
                s_tblHandEncBlack[g_selX - BOARD_LEFT_OFFSET]);
    } else {
        //  盤上の駒を移動させる。  //
        gc.playMoveAction(
                g_selX - BOARD_LEFT_OFFSET,
                g_selY - BOARD_TOP_OFFSET,
                mx - BOARD_LEFT_OFFSET,
                my - BOARD_TOP_OFFSET,
                0);
    }

    //  最後の指し手を棋譜ファイルに書き込む。  //
    gc.writeActionList(actList);
    if ( ofsKifu.good() && !(actList.empty()) ) {
        gc.writeActionView(actList.back(), ofsKifu);
        ofsKifu << std::endl;
        ofsKifu.flush();
    }

label_redaw_board:
    g_selX  = -1;
    g_selY  = -1;
    g_movX  = -1;
    g_movY  = -1;
    ::InvalidateRect(hWnd, NULL, TRUE);
#endif

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

#if 0

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
#endif

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
            g_scrBoard.onMouseMove(0, 0, 0);
            g_scrBoard.onLButtonUp(0, 0, 0);
        }
    }

    g_scrBoard.drawScreenLayer( &g_imgBoard );

#if 0
    Common::ViewBuffer  vb;
    memset(&vb, 0, sizeof(vb));
    gc.writeToViewBuffer(vb);

    //  後手の持ち駒を表示する。    //
    int     tx  = 0;
    for ( int c = HANDS_WHITE_PAWN; c <= HANDS_WHITE_KING; ++ c, ++ tx )
    {
        const  THandCount   numHand = vb.nHands[c];
        if ( numHand <= 0 ) { continue; }

        dx  = (tx * SQUARE_WIDTH) + LEFT_MARGIN;
        dy  = TOP_MARGIN;
        sx  = (c - HANDS_WHITE_PAWN) * SQUARE_WIDTH;
        sy  = (1) * SQUARE_HEIGHT;
        g_imgScreen.copyRectangle(
                dx, dy, SQUARE_WIDTH, SQUARE_HEIGHT, g_imgPiece, sx, sy);
    }

    //  盤上にある駒を表示する。    //
    for ( int y = 0; y < POS_NUM_ROWS; ++ y ) {
        for ( int x = 0; x < POS_NUM_COLS; ++ x ) {
            dx  = (x * SQUARE_WIDTH) + LEFT_MARGIN;
            dy  = ((y + BOARD_TOP_OFFSET) * SQUARE_HEIGHT) + TOP_MARGIN;
            const  int          pi  = (y * POS_NUM_COLS) + x;
            const  PieceIndex   dp  = vb.piBoard[pi];
            if ( dp == 0 ) { continue; }

            sx  = ((dp - 1) % 10) * SQUARE_WIDTH;
            sy  = ((dp - 1) / 10) * SQUARE_HEIGHT;
            g_imgScreen.copyRectangle(
                    dx, dy, SQUARE_WIDTH, SQUARE_HEIGHT, g_imgPiece, sx, sy);
        }
    }

    //  先手の持ち駒を表示する。    //
    tx  = 0;
    for ( int c = HANDS_BLACK_PAWN; c <= HANDS_BLACK_KING; ++ c, ++ tx )
    {
        const  THandCount   numHand = vb.nHands[c];
        if ( numHand <= 0 ) { continue; }

        dx  = (tx * SQUARE_WIDTH) + LEFT_MARGIN;
        dy  = (POS_NUM_ROWS + BOARD_TOP_OFFSET) * SQUARE_HEIGHT + TOP_MARGIN;
        sx  = (c - HANDS_BLACK_PAWN) * SQUARE_WIDTH;
        sy  = (0) * SQUARE_HEIGHT;
        g_imgScreen.copyRectangle(
                dx, dy, SQUARE_WIDTH, SQUARE_HEIGHT, g_imgPiece, sx, sy);
    }

    //  選択しているマスがあれば強調表示。  //
    if ( (g_selX >= 0) && (g_selY >= 0) ) {
        sx  = ((g_selX) * SQUARE_WIDTH) + LEFT_MARGIN;
        sy  = ((g_selY) * SQUARE_HEIGHT) + TOP_MARGIN;

        g_imgScreen.drawTransparentRectangle(
                sx,  sy,  SQUARE_WIDTH,  SQUARE_HEIGHT,
                255, 255, 0, 192);
    }

    //  移動先として現在マウスが示しているマスを強調表示。  //
    if ( (g_movX >= 0) && (g_movY >= 0) ) {
        sx  = ((g_movX) * SQUARE_WIDTH) + LEFT_MARGIN;
        sy  = ((g_movY) * SQUARE_HEIGHT) + TOP_MARGIN;

        g_imgScreen.drawTransparentRectangle(
                sx,  sy,  SQUARE_WIDTH,  SQUARE_HEIGHT,
                0, 0, 255, 192);
    }

#endif

    //  描画した内容を画面に表示する。  //
    g_imgScreen.copyRectangle(
            g_scrBoard.getLeft(),
            g_scrBoard.getTop(),
            g_scrBoard.getWidth(),
            g_scrBoard.getHeight(),
            g_imgBoard,
            0, 0);

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

    //  この瞬間に画像を準備する。      //
    if ( g_scrBoard.setupBitmapImages("Back.bmp", "Pieces.bmp")
            != ERR_SUCCESS )
    {
        ::MessageBox(hWnd,  "Graphic Files Not Found!", NULL,  MB_OK);
        return ( 0 );
    }

    HDC hDC = ::GetDC(hWnd);
    if ( g_imgScreen.createBitmap(WINDOW_WIDTH, WINDOW_HEIGHT, hDC)
            != ERR_SUCCESS )
    {
        ::MessageBox(hWnd,  "Not Enough Memory!",
                     NULL,  MB_OK);
    }
    if ( g_imgBoard.createBitmap(WINDOW_WIDTH, WINDOW_HEIGHT, 24)
            != ERR_SUCCESS )
    {
        ::MessageBox(hWnd,  "Not Enough Memory!",
                     NULL,  MB_OK);
    }
    ::ReleaseDC(hWnd, hDC);

    //  グローバル変数を初期化する。    //
    g_scrBoard.setLeft  (VIEW_BOARD_LEFT);
    g_scrBoard.setTop   (VIEW_BOARD_TOP);
    g_scrBoard.setWidth (VIEW_BOARD_WIDTH);
    g_scrBoard.setHeight(VIEW_BOARD_HEIGHT);

    g_scrBoard.resetGame();
    g_hCapture  = NULL;

    // g_selX  = -1;
    // g_selY  = -1;
    // g_movX  = -1;
    // g_movY  = -1;

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
