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

CONSTEXPR_VAR   PieceIndex
s_tblHandDecode[]   =  {
    0,

    Common::HAND_BLACK_PAWN,
    Common::HAND_BLACK_SILVER,
    Common::HAND_BLACK_GOLD,
    Common::HAND_BLACK_BISHOP,
    Common::HAND_BLACK_ROOK,
    Common::HAND_BLACK_KING,

    Common::HAND_WHITE_PAWN,
    Common::HAND_WHITE_SILVER,
    Common::HAND_WHITE_GOLD,
    Common::HAND_WHITE_BISHOP,
    Common::HAND_WHITE_ROOK,
    Common::HAND_WHITE_KING
};

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
      m_bsState(BSLS_NOTHING),
      m_bcSelX(-1),
      m_bcSelY(-1),
      m_bcMovX(-1),
      m_bcMovY(-1),
      m_bcSrcX(-1),
      m_bcSrcY(-1),
      m_bcTrgX(-1),
      m_bcTrgY(-1),
      m_prmOptions(),
      m_biBack (nullptr),
      m_biPiece(nullptr),
      m_ofsKifu("Kifu.txt"),
      m_ddMode(DDM_NOT_START)
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
      m_bsState(BSLS_NOTHING),
      m_bcSelX(-1),
      m_bcSelY(-1),
      m_bcMovX(-1),
      m_bcMovY(-1),
      m_bcSrcX(-1),
      m_bcSrcY(-1),
      m_bcTrgX(-1),
      m_bcTrgY(-1),
      m_prmOptions(),
      m_biBack (nullptr),
      m_biPiece(nullptr),
      m_ofsKifu("Kifu.txt"),
      m_ddMode(DDM_NOT_START)
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
            this->m_biBack->getWidth(),
            this->m_biBack->getHeight(),
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

            sx  = ((dp - 1) % 14) * SQUARE_WIDTH;
            sy  = ((dp - 1) / 14) * SQUARE_HEIGHT;
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
    if ( (this->m_bcSelX >= 0) && (this->m_bcSelY >= 0) ) {
        sx  = ((this->m_bcSelX) * SQUARE_WIDTH) + LEFT_MARGIN;
        sy  = ((this->m_bcSelY) * SQUARE_HEIGHT) + TOP_MARGIN;

        bmpTrg->drawTransparentRectangle(
                sx,  sy,  SQUARE_WIDTH,  SQUARE_HEIGHT,
                255, 255, 0, 192);
    }

    //  移動先として現在マウスが示しているマスを強調表示。  //
    if ( (this->m_bcMovX >= 0) && (this->m_bcMovY >= 0) ) {
        sx  = ((this->m_bcMovX) * SQUARE_WIDTH) + LEFT_MARGIN;
        sy  = ((this->m_bcMovY) * SQUARE_HEIGHT) + TOP_MARGIN;

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

    if ( (this->m_ddMode) == DDM_CLICKS ) {
        //  クリックモードになっている時は何もしない。  //
        return ( EH_RESULT_SUCCESS );
    }

    if ( (xPos < LEFT_MARGIN) || (yPos < TOP_MARGIN) ) {
        //  範囲外の場合。  //
        clearSelection();
        return ( EH_RESULT_REDRAW );
    }

    const  int  mx  = ((int)(xPos) - LEFT_MARGIN) / SQUARE_WIDTH;
    const  int  my  = ((int)(yPos) - TOP_MARGIN) / SQUARE_HEIGHT;

    if ( (VIEW_NUM_ROWS <= my) ) {
        clearSelection();
        return ( EH_RESULT_REDRAW );
    }

    if ( (my == 0) || (my == (POS_NUM_ROWS + BOARD_TOP_OFFSET)) ) {
        //  持ち駒の表示エリアの場合。  //
        if ( (HANDS_WHITE_KING - HANDS_WHITE_PAWN + 1) <= mx ) {
            clearSelection();
            return ( EH_RESULT_REDRAW );
        } else {
            this->m_bcSelX  = mx;
            this->m_bcSelY  = my;
        }
    } else if ( (VIEW_NUM_COLS) <= mx ) {
        //  盤の外を選択しようとした場合。  //
        clearSelection();
        return ( EH_RESULT_REDRAW );
    } else {
        this->m_bcSelX  = mx;
        this->m_bcSelY  = my;

#if 0
        //  選択したマスの駒が、移動できない場合はキャンセル。  //
        const  Game::BoardState  &
            gbs = this->m_gcGameCtrl.getBoardState();
        const  PieceIndex   piMove  = gbs.getFieldPiece(
                mx - BOARD_LEFT_OFFSET,
                my - BOARD_TOP_OFFSET);
        if ( piMove == Game::BoardState::FIELD_EMPTY_SQUARE ) {
            clearSelection();
            return ( EH_RESULT_REDRAW );
        }
#endif
    }

    this->m_bcMovX  = -1;
    this->m_bcMovY  = -1;

    if ( (this->m_ddMode) == DDM_NOT_START ) {
        this->m_ddMode  = DDM_SELECT_SOURCE;
    }

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

    if ( (this->m_bcSelX < 0) || (this->m_bcSelY < 0) ) {
        return ( EH_RESULT_SUCCESS );
    }

    const  BoardCoord   mx  = ((int)(xPos) - LEFT_MARGIN) / SQUARE_WIDTH;
    const  BoardCoord   my  = ((int)(yPos) - TOP_MARGIN) / SQUARE_HEIGHT;

    //  画面の範囲外でマウスボタンを離した場合は、キャンセルする。  //
    if ( (mx < BOARD_LEFT_OFFSET) || (my < BOARD_TOP_OFFSET)
            || (POS_NUM_COLS + BOARD_LEFT_OFFSET <= mx)
            || (POS_NUM_ROWS + BOARD_TOP_OFFSET  <= my) )
    {
        clearSelection();
        return ( EH_RESULT_REDRAW );
    }

    //  クリックモードになっている場合は、移動先を指定する。    //
    if ( (this->m_ddMode) == DDM_CLICKS ) {
        if ( (this->m_bcMovX == mx) && (this->m_bcMovY == my) ) {
            //  同じ場所を二回クリックしたので処理を確定する。  //
            setActionInput(this->m_bcSelX, this->m_bcSelY, mx, my);
            clearSelection();
        } else {
            //  違う場所をクリックしたので、その場所を強調。    //
            this->m_bcMovX  = mx;
            this->m_bcMovY  = my;
        }
        return ( EH_RESULT_REDRAW );
    }

    if ( (this->m_ddMode) == DDM_SELECT_SOURCE ) {
        //  ダブルクリックモードに切り替える。  //
        this->m_bcMovX  = -1;
        this->m_bcMovY  = -1;
        this->m_ddMode  = DDM_CLICKS;
        return ( EH_RESULT_REDRAW );
    }

    if ( (this->m_ddMode) == DDM_DRAG_AND_DROP ) {
        setActionInput(this->m_bcSelX, this->m_bcSelY, mx, my);
        clearSelection();
    }

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

    if ( ((this->m_ddMode) == DDM_NOT_START)
            || ((this->m_ddMode) == DDM_CLICKS) )
    {
        //  クリックモードになっている時は何もしない。  //
        //  また、操作を開始していない時も何もしない。  //
        return ( EH_RESULT_SUCCESS );
    }

    if ( (this->m_bcSelX < 0) || (this->m_bcSelY < 0) ) {
        return ( EH_RESULT_SUCCESS );
    }

    const  BoardCoord   mx  = ((int)(xPos) - LEFT_MARGIN) / SQUARE_WIDTH;
    const  BoardCoord   my  = ((int)(yPos) - TOP_MARGIN) / SQUARE_HEIGHT;
    BoardCoord  mvX,  mvY;

    //  最初に選択したマスから外れた場合は、    //
    //  ドラッグドロップモードに完全移行する。  //
    if ( ((this->m_bcSelX) != mx) || ((this->m_bcSelY) != my) ) {
        this->m_ddMode  = DDM_DRAG_AND_DROP;
    }

    if ( (xPos < LEFT_MARGIN) || (yPos < TOP_MARGIN) ) {
        this->m_bcMovX  = -1;
        this->m_bcMovY  = -1;
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

    if ( (this->m_bcMovX != mvX) || (this->m_bcMovY != mvY) ) {
        this->m_bcMovX  = mvX;
        this->m_bcMovY  = mvY;
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
    clearSelection();
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

//----------------------------------------------------------------
//    マスの選択をクリアする。
//

ErrCode
BoardScreen::clearSelection()
{
    this->m_bcSelX  = -1;
    this->m_bcSelY  = -1;
    this->m_bcMovX  = -1;
    this->m_bcMovY  = -1;
    this->m_ddMode  = DDM_NOT_START;

    return ( ERR_SUCCESS );
}

//----------------------------------------------------------------
//    ユーザーが選択した成り駒を指定する。
//

ErrCode
BoardScreen::setPromotionOption(
        const  PieceIndex   idxSel)
{
    const  PieceIndex   pidSel  = (this->m_prmOptions)[idxSel];

    this->m_bsState = BSLS_NOTHING;

    return ( playAction(
                     this->m_bcSrcX,  this->m_bcSrcY,
                     this->m_bcTrgX,  this->m_bcTrgY,  pidSel) );
}

//========================================================================
//
//    Accessors.
//

//----------------------------------------------------------------
//    現在の状態を示すフラグを取得する。
//

BoardScreen::ScreenState
BoardScreen::getCurrentState()  const
{
    return ( this->m_bsState );
}

//----------------------------------------------------------------
//    成り駒の選択肢を取得する。
//

const   BoardScreen::OptionArray  &
BoardScreen::getPromotionList()  const
{
    return ( this->m_prmOptions );
}

//========================================================================
//
//    For Internal Use Only.
//

//----------------------------------------------------------------
//    指定したマスに対してプレイを行う。
//

ErrCode
BoardScreen::playAction(
        const  BoardCoord   srcX,
        const  BoardCoord   srcY,
        const  BoardCoord   trgX,
        const  BoardCoord   trgY,
        const  PieceIndex   iPrm)
{
    ActionView  actView;
    PromoteList plDummy;

    setupActionView(
            this->m_gcGameCtrl,  srcX,  srcY,  trgX,  trgY,
            &plDummy,   &actView );
    actView.fpAfter = iPrm;
    this->m_gcGameCtrl.playForward(actView);

    this->m_bcSrcX  = -1;
    this->m_bcSrcY  = -1;
    this->m_bcTrgX  = -1;
    this->m_bcTrgY  = -1;
    clearSelection();

    //  最後の指し手を棋譜ファイルに書き込む。  //
    Interface::GameController::ActionViewList   actList;

    this->m_gcGameCtrl.writeActionList(actList);
    if ( this->m_ofsKifu.good() && !(actList.empty()) ) {
        this->m_gcGameCtrl.writeActionView(actList.back(), this->m_ofsKifu);
        this->m_ofsKifu << std::endl;
        this->m_ofsKifu.flush();
    }

    return ( ERR_SUCCESS );
}


//----------------------------------------------------------------
//    移動先を指定して、移動可能性と成り駒選択肢を検査する。
//

ErrCode
BoardScreen::setActionInput(
        const  BoardCoord   srcX,
        const  BoardCoord   srcY,
        const  BoardCoord   trgX,
        const  BoardCoord   trgY)
{
    this->m_bcSrcX  = srcX;
    this->m_bcSrcY  = srcY;
    this->m_bcTrgX  = trgX;
    this->m_bcTrgY  = trgY;

    this->m_prmOptions.clear();
    setupActionView(
            this->m_gcGameCtrl,     srcX,  srcY,  trgX,  trgY,
            &(this->m_prmOptions),  nullptr );

    this->m_bsState = BSLS_NOTHING;
    const  size_t   numOpt  = this->m_prmOptions.size();
    if ( numOpt == 0 ) {
        return ( ERR_FAILURE );
    }
    if ( numOpt == 1 ) {
        return ( playAction(srcX, srcY, trgX, trgY, this->m_prmOptions[0]) );
    }

    this->m_bsState = BSLS_SHOW_PROMOTION;
    return ( ERR_SUCCESS );
}

//----------------------------------------------------------------
//    移動元と移動先から、指し手データを構築する。
//

ErrCode
BoardScreen::setupActionView(
        const  GameInterface  & giCtrl,
        const  BoardCoord       srcX,
        const  BoardCoord       srcY,
        const  BoardCoord       trgX,
        const  BoardCoord       trgY,
        PromoteList  *  const   vProms,
        ActionView   *  const   ptrAct)
{
    vProms->clear();

    if ( (srcY) == 0 ) {
        giCtrl.setupPutActionFromMouse(
                trgX - BOARD_LEFT_OFFSET,
                trgY - BOARD_TOP_OFFSET,
                s_tblHandEncWhite[srcX - BOARD_LEFT_OFFSET],
                vProms,  ptrAct );
    } else if ( (srcY) == POS_NUM_ROWS + BOARD_TOP_OFFSET ) {
        //  先手の持ち駒を打つ。    //
        giCtrl.setupPutActionFromMouse(
                trgX - BOARD_LEFT_OFFSET,
                trgY - BOARD_TOP_OFFSET,
                s_tblHandEncBlack[srcX - BOARD_LEFT_OFFSET],
                vProms,  ptrAct );
    } else {
        //  盤上の駒を移動させる。  //
        giCtrl.setupMoveActionFromMouse(
                srcX - BOARD_LEFT_OFFSET,
                srcY - BOARD_TOP_OFFSET,
                trgX - BOARD_LEFT_OFFSET,
                trgY - BOARD_TOP_OFFSET,
                vProms,  ptrAct );
    }

    return ( ERR_SUCCESS );
}

}   //  End of namespace  Interface
FAIRYSHOGI_NAMESPACE_END
