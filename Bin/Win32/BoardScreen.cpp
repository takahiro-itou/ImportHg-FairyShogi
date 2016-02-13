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
**      An Implementation of BoardScreen class.
**
**      @file       Bin/Win32/BoardScreen.cpp
**/

#include    "BoardScreen.h"

#include    "FairyShogi/Common/ActionView.h"
#include    "FairyShogi/Interface/BitmapImage.h"

FAIRYSHOGI_NAMESPACE_BEGIN
namespace  Interface  {

namespace  {

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

}   //  End of (Unnamed) namespace.

//========================================================================
//
//    BoardScreen  class.
//

//========================================================================
//
//    Constructor(s) and Destructor.
//

//----------------------------------------------------------------
//    インスタンスを初期化する
//  （デフォルトコンストラクタ）。
//

BoardScreen::BoardScreen()
    : Super(),
      m_gcGameCtrl(),
      m_scSelX(-1),
      m_scSelY(-1),
      m_scMovX(-1),
      m_scMovY(-1),
      m_biBack (nullptr),
      m_biPiece(nullptr),
      m_ofsKifu("Kifu.txt"),
      m_ddMode(DDM_CLICKS)
{
}

//----------------------------------------------------------------
//    インスタンスを指定したサイズで初期化する
//  （コンストラクタ）。
//

BoardScreen::BoardScreen(
        const  WindowCoord  wcLeft,
        const  WindowCoord  wcTop,
        const  WindowCoord  wcWidth,
        const  WindowCoord  wcHeight)
    : Super(wcLeft, wcTop, wcWidth, wcHeight),
      m_gcGameCtrl(),
      m_scSelX(-1),
      m_scSelY(-1),
      m_scMovX(-1),
      m_scMovY(-1),
      m_biBack (nullptr),
      m_biPiece(nullptr),
      m_ofsKifu("Kifu.txt"),
      m_ddMode(DDM_CLICKS)
{
}

//----------------------------------------------------------------
//    インスタンスを破棄する
//  （デストラクタ）。
//

BoardScreen::~BoardScreen()
{
}

//========================================================================
//
//    Public Member Functions (Implement Pure Virtual).
//

//----------------------------------------------------------------
//    指定したビットマップイメージ上に内容を描画する。
//

ErrCode
BoardScreen::drawScreenLayer(
        BitmapImage  *  bmpTrg)  const
{
    int     sx, sy, dx, dy;

    //  背景をコピーする。      //
    bmpTrg->copyRectangle(
            0, 0,
            VIEW_NUM_COLS * SQUARE_WIDTH,
            VIEW_NUM_ROWS * SQUARE_HEIGHT,
            *(this->m_biBack),  0,  0);

    Common::ViewBuffer  vb;
    memset(&vb, 0, sizeof(vb));
    this->m_gcGameCtrl.writeToViewBuffer(vb);

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
        bmpTrg->copyRectangle(
                dx, dy, SQUARE_WIDTH, SQUARE_HEIGHT,
                *(this->m_biPiece), sx, sy);
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
            bmpTrg->copyRectangle(
                    dx, dy, SQUARE_WIDTH, SQUARE_HEIGHT,
                    *(this->m_biPiece), sx, sy);
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
        bmpTrg->copyRectangle(
                dx, dy, SQUARE_WIDTH, SQUARE_HEIGHT,
                *(this->m_biPiece), sx, sy);
    }

    //  選択しているマスがあれば強調表示。  //
    if ( (this->m_scSelX >= 0) && (this->m_scSelY >= 0) ) {
        sx  = ((this->m_scSelX) * SQUARE_WIDTH) + LEFT_MARGIN;
        sy  = ((this->m_scSelY) * SQUARE_HEIGHT) + TOP_MARGIN;

        bmpTrg->drawTransparentRectangle(
                sx,  sy,  SQUARE_WIDTH,  SQUARE_HEIGHT,
                255, 255, 0, 192);
    }

    //  移動先として現在マウスが示しているマスを強調表示。  //
    if ( (this->m_scMovX >= 0) && (this->m_scMovY >= 0) ) {
        sx  = ((this->m_scMovX) * SQUARE_WIDTH) + LEFT_MARGIN;
        sy  = ((this->m_scMovY) * SQUARE_HEIGHT) + TOP_MARGIN;

        bmpTrg->drawTransparentRectangle(
                sx,  sy,  SQUARE_WIDTH,  SQUARE_HEIGHT,
                0, 0, 255, 192);
    }

    return ( ERR_SUCCESS );
}

//========================================================================
//
//    Public Member Functions (Overrides).
//

//========================================================================
//
//    Public Member Functions (Pure Virtual Functions).
//

//========================================================================
//
//    Public Member Functions (Virtual Functions).
//

//----------------------------------------------------------------
//    マウスの左ボタンを押した時のイベントハンドラ。
//

BoardScreen::EventResult
BoardScreen::onLButtonDown(
        const   DWORD   fwKeys,
        const   UINT    xPos,
        const   UINT    yPos)
{
    UTL_HELP_UNUSED_ARGUMENT(fwKeys);

    if ( (xPos < LEFT_MARGIN) || (yPos < TOP_MARGIN) ) {
        this->m_scSelX  = -1;
        this->m_scSelY  = -1;
        this->m_scMovX  = -1;
        this->m_scMovY  = -1;
        return ( EH_RESULT_REDRAW );
    }

    const  int  mx  = ((int)(xPos) - LEFT_MARGIN) / SQUARE_WIDTH;
    const  int  my  = ((int)(yPos) - TOP_MARGIN) / SQUARE_HEIGHT;

    if ( (VIEW_NUM_ROWS <= my) ) {
        this->m_scSelX  = -1;
        this->m_scSelY  = -1;
        this->m_scMovX  = -1;
        this->m_scMovY  = -1;
        return ( EH_RESULT_REDRAW );
    }

    if ( (my == 0) || (my == (POS_NUM_ROWS + BOARD_TOP_OFFSET)) ) {
        if ( (HANDS_WHITE_KING - HANDS_WHITE_PAWN + 1) <= mx ) {
            this->m_scSelX  = -1;
            this->m_scSelY  = -1;
            this->m_scMovX  = -1;
            this->m_scMovY  = -1;
            return ( EH_RESULT_REDRAW );
        } else {
            this->m_scSelX  = mx;
            this->m_scSelY  = my;
        }
    } else if ( (VIEW_NUM_COLS) <= mx ) {
        this->m_scSelX  = -1;
        this->m_scSelY  = -1;
    } else {
        this->m_scSelX  = mx;
        this->m_scSelY  = my;
    }

    this->m_scMovX  = -1;
    this->m_scMovY  = -1;

    return ( EH_RESULT_REDRAW );
}

//----------------------------------------------------------------
//    マウスの左ボタンを離した時のイベントハンドラ。
//

BoardScreen::EventResult
BoardScreen::onLButtonUp(
        const   DWORD   fwKeys,
        const   UINT    xPos,
        const   UINT    yPos)
{
    UTL_HELP_UNUSED_ARGUMENT(fwKeys);

    ::ReleaseCapture();

    if ( (this->m_scSelX < 0) || (this->m_scSelY < 0) ) {
        return ( EH_RESULT_SUCCESS );
    }

    Interface::GameController::ActionViewList   actList;

    const  int  mx  = ((int)(xPos) - LEFT_MARGIN) / SQUARE_WIDTH;
    const  int  my  = ((int)(yPos) - TOP_MARGIN) / SQUARE_HEIGHT;

    if ( (mx < BOARD_LEFT_OFFSET) || (my < BOARD_TOP_OFFSET)
            || (POS_NUM_COLS + BOARD_LEFT_OFFSET <= mx)
            || (POS_NUM_ROWS + BOARD_TOP_OFFSET  <= my) )
    {
        return ( EH_RESULT_REDRAW );
    }
    if ( (mx == this->m_scSelX) && (my == this->m_scSelY) ) {
        //  移動をドラッグドロップモードから、  //
        //  ダブルクリックモードに切り替える。  //
        this->m_ddMode  = DDM_CLICKS;
        return ( EH_RESULT_REDRAW );
    }

    if ( (this->m_scSelY) == 0 ) {
        //  後手の持ち駒を打つ。    //
        this->m_gcGameCtrl.playPutAction(
                mx - BOARD_LEFT_OFFSET,
                my - BOARD_TOP_OFFSET,
                s_tblHandEncWhite[this->m_scSelX - BOARD_LEFT_OFFSET]);
    } else if ( (this->m_scSelY) == POS_NUM_ROWS + BOARD_TOP_OFFSET ) {
        //  先手の持ち駒を打つ。    //
        this->m_gcGameCtrl.playPutAction(
                mx - BOARD_LEFT_OFFSET,
                my - BOARD_TOP_OFFSET,
                s_tblHandEncBlack[this->m_scSelX - BOARD_LEFT_OFFSET]);
    } else {
        //  盤上の駒を移動させる。  //
        this->m_gcGameCtrl.playMoveAction(
                this->m_scSelX - BOARD_LEFT_OFFSET,
                this->m_scSelY - BOARD_TOP_OFFSET,
                mx - BOARD_LEFT_OFFSET,
                my - BOARD_TOP_OFFSET,
                0);
    }

    //  最後の指し手を棋譜ファイルに書き込む。  //
    this->m_gcGameCtrl.writeActionList(actList);
    if ( this->m_ofsKifu.good() && !(actList.empty()) ) {
        this->m_gcGameCtrl.writeActionView(actList.back(), this->m_ofsKifu);
        this->m_ofsKifu << std::endl;
        this->m_ofsKifu.flush();
    }

    this->m_scSelX  = -1;
    this->m_scSelY  = -1;
    this->m_scMovX  = -1;
    this->m_scMovY  = -1;

    return ( EH_RESULT_REDRAW );
}

//----------------------------------------------------------------
//    マウスを移動させた時のイベントハンドラ。
//

BoardScreen::EventResult
BoardScreen::onMouseMove(
        const   DWORD   fwKeys,
        const   UINT    xPos,
        const   UINT    yPos)
{
    UTL_HELP_UNUSED_ARGUMENT(fwKeys);

    if ( (this->m_scSelX < 0) || (this->m_scSelY < 0) ) {
        return ( EH_RESULT_SUCCESS );
    }

    const  int  mx  = ((int)(xPos) - LEFT_MARGIN) / SQUARE_WIDTH;
    const  int  my  = ((int)(yPos) - TOP_MARGIN) / SQUARE_HEIGHT;
    int     mvX, mvY;

    if ( (xPos < LEFT_MARGIN) || (yPos < TOP_MARGIN) ) {
        this->m_scMovX  = -1;
        this->m_scMovY  = -1;
        return ( EH_RESULT_REDRAW );
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

    if ( (this->m_scMovX != mvX) || (this->m_scMovY != mvY) ) {
        this->m_scMovX  = mvX;
        this->m_scMovY  = mvY;
        return ( EH_RESULT_REDRAW );
    }

    return ( EH_RESULT_SUCCESS );
}

//----------------------------------------------------------------
//    盤面を初期状態に設定する。
//

ErrCode
BoardScreen::resetGame()
{
    return ( this->m_gcGameCtrl.resetGame() );
}

//----------------------------------------------------------------
//    必要な画像データを準備する。
//

ErrCode
BoardScreen::setupBitmapImages(
        const  std::string  &imgBack,
        const  std::string  &imgPiece)
{
    this->m_biBack  = new  BitmapImage;
    if ( this->m_biBack->openBitmapFile(imgBack) != ERR_SUCCESS ) {
        return ( ERR_FAILURE );
    }

    this->m_biPiece = new  BitmapImage;
    if ( this->m_biPiece->openBitmapFile(imgPiece) != ERR_SUCCESS ) {
        return ( ERR_FAILURE );
    }

    return ( ERR_SUCCESS );
}

//========================================================================
//
//    Public Member Functions.
//

//========================================================================
//
//    Accessors.
//

//========================================================================
//
//    For Internal Use Only.
//

}   //  End of namespace  Interface
FAIRYSHOGI_NAMESPACE_END
