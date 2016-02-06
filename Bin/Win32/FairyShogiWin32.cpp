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

using   namespace   FAIRYSHOGI_NAMESPACE;

namespace  {

constexpr   char
g_szClassName[] = "FairyShogiWindow";

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

Interface::GameController   gc;

Interface::BitmapImage      g_imgScreen;
Interface::BitmapImage      g_imgPiece;

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

label_redaw_board:
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

    //  何らかの理由で、マウスボタンが離された事実が、  //
    //  メインウィンドウに通知されなかった時の処理。    //
    //  例えば、マウスボタンを押して、AlT+Tab キーで    //
    //  別のウィンドウに切り替え、ボタンを離した等。    //
    if ( (g_selX >= 0) && (g_selY >= 0) ) {
        if ( ::GetCapture() != hWnd ) {
            g_selX  = -1;
            g_selY  = -1;
            g_movX  = -1;
            g_movY  = -1;
        }
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

    Common::ViewBuffer  vb;
    memset(&vb, 0, sizeof(vb));
    gc.writeToViewBuffer(vb);

    //  後手の持ち駒を表示する。    //
    int     tx  = 0;
    for ( int c = HANDS_WHITE_PAWN; c <= HANDS_WHITE_KING; ++ c, ++ tx )
    {
        const  THandCount   numHand = vb.nHands[c];
        if ( numHand <= 0 ) { continue; }

        sx  = (tx * SQUARE_WIDTH) + LEFT_MARGIN;
        sy  = TOP_MARGIN;
        if ( (g_selY != 0)
                || (g_selX != tx + BOARD_LEFT_OFFSET) )
        {
            ::Rectangle(hDC, sx, sy, sx + SQUARE_WIDTH, sy + SQUARE_HEIGHT);
        }
        sx  += (SQUARE_WIDTH  / 4);
        sy  += (SQUARE_HEIGHT / 2);
        const  char  *  pn  = s_tblHandName[c];
        ::TextOut(hDC, sx, sy, pn, strlen(pn));
    }

    //  盤上にある駒を表示する。    //
    for ( int y = 0; y < POS_NUM_ROWS; ++ y ) {
        for ( int x = 0; x < POS_NUM_COLS; ++ x ) {
            sx  = (x * SQUARE_WIDTH) + LEFT_MARGIN;
            sy  = ((y + BOARD_TOP_OFFSET) * SQUARE_HEIGHT) + TOP_MARGIN;
            dx  = sx + (SQUARE_WIDTH  / 4);
            dy  = sy + (SQUARE_HEIGHT / 2);
            const  int          pi  = (y * POS_NUM_COLS) + x;
            const  PieceIndex   dp  = vb.piBoard[pi];
            if ( dp == 0 ) { continue; }

            const  char  *      pn  = s_tblPieceName[dp];
            ::TextOut(hDC, dx, dy, pn, strlen(pn));
        }
    }

    //  先手の持ち駒を表示する。    //
    tx  = 0;
    for ( int c = HANDS_BLACK_PAWN; c <= HANDS_BLACK_KING; ++ c, ++ tx )
    {
        const  THandCount   numHand = vb.nHands[c];
        if ( numHand <= 0 ) { continue; }

        sx  = (tx * SQUARE_WIDTH) + LEFT_MARGIN;
        sy  = (POS_NUM_ROWS + BOARD_TOP_OFFSET) * SQUARE_HEIGHT + TOP_MARGIN;
        if ( (g_selY != POS_NUM_ROWS + BOARD_TOP_OFFSET)
                || (g_selX != tx + BOARD_LEFT_OFFSET) )
        {
            ::Rectangle(hDC, sx, sy, sx + SQUARE_WIDTH, sy + SQUARE_HEIGHT);
        }
        sx  += (SQUARE_WIDTH  / 4);
        sy  += (SQUARE_HEIGHT / 2);
        const  char  *  pn  = s_tblHandName[c];
        ::TextOut(hDC, sx, sy, pn, strlen(pn));
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
    if ( g_imgPiece.openBitmapFile("Pieces.bmp") != ERR_SUCCESS )
    {
        ::MessageBox(hWnd,  "Graphic File [Pieces.bmp] Not Found!",
                     NULL,  MB_OK);
    }
    {
        HDC hDC = ::GetDC(hWnd);
        if ( g_imgScreen.createBitmap(320, 320, hDC) != ERR_SUCCESS )
        {
            ::MessageBox(hWnd,  "Not Enough Memory!",
                         NULL,  MB_OK);
        }
        ::ReleaseDC(hWnd, hDC);
    }

    //  グローバル変数を初期化する。    //
    gc.resetGame();
    g_selX  = -1;
    g_selY  = -1;
    g_movX  = -1;
    g_movY  = -1;

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
