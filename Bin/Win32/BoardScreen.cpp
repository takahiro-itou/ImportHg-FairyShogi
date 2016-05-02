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
#include    "FairyShogi/Common/HelperMacros.h"
#include    "FairyShogi/Win32/BitmapResource.h"

#include    <iostream>

FAIRYSHOGI_NAMESPACE_BEGIN
namespace  Win32  {

namespace  {

CONSTEXPR_VAR   const  char  *
s_tblEngineNames[]  =  {
    "level0",   "level1",   "level2",   "level3"
};

CONSTEXPR_VAR   Common::EHandPiece
s_tblHandEncBlack[] = {
    Common::HAND_BLACK_PAWN,
    Common::HAND_BLACK_SILVER,
    Common::HAND_BLACK_GOLD,
    Common::HAND_BLACK_BISHOP,
    Common::HAND_BLACK_ROOK,
    Common::HAND_BLACK_KING
};

CONSTEXPR_VAR   Common::EHandPiece
s_tblHandEncWhite[] = {
    Common::HAND_WHITE_PAWN,
    Common::HAND_WHITE_SILVER,
    Common::HAND_WHITE_GOLD,
    Common::HAND_WHITE_BISHOP,
    Common::HAND_WHITE_ROOK,
    Common::HAND_WHITE_KING
};

CONSTEXPR_VAR   BoardScreen::BoardCoord
s_tblHandSelX[Common::NUM_HAND_TYPES]  =  {
    -1,
    0, -1, -1, 1, 2, 3, 4, 5,
    0, -1, -1, 1, 2, 3, 4, 5
};

CONSTEXPR_VAR   BoardScreen::BoardCoord
s_tblHandSelY[Common::NUM_HAND_TYPES]  =  {
    -1,
    6, -1, -1, 6, 6, 6, 6, 6,
    0, -1, -1, 0, 0, 0, 0, 0
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
      m_tblHighLight(),
      m_bcLastSrcX(-1),
      m_bcLastSrcY(-1),
      m_bcLastTrgX(-1),
      m_bcLastTrgY(-1),
      m_prmOptions(),
      m_brBack (nullptr),
      m_brPiece(nullptr),
      m_ofsKifu("Kifu.txt"),
      m_flgDiceRoll(DICE_NOT_ROLLED),
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
      m_tblHighLight(),
      m_bcLastSrcX(-1),
      m_bcLastSrcY(-1),
      m_bcLastTrgX(-1),
      m_bcLastTrgY(-1),
      m_prmOptions(),
      m_brBack (nullptr),
      m_brPiece(nullptr),
      m_ofsKifu("Kifu.txt"),
      m_flgDiceRoll(DICE_NOT_ROLLED),
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
            this->m_brBack->getWidth(),
            this->m_brBack->getHeight(),
            *(this->m_brBack),  0,  0);

    Common::ViewBuffer  vb;
    memset(&vb, 0, sizeof(vb));
    this->m_gcGameCtrl.writeToViewBuffer(vb);

    //  直前の着手を表示する。  //
    if ( (this->m_bcLastSrcX >= 0) && (this->m_bcLastSrcY >= 0) ) {
        sx  = ((this->m_bcLastSrcX) * SQUARE_WIDTH) + LEFT_MARGIN;
        sy  = ((this->m_bcLastSrcY) * SQUARE_HEIGHT) + TOP_MARGIN;

        bmpTrg->drawRectangle(
                sx + 2,  sy + 2,
                SQUARE_WIDTH - 4,  SQUARE_HEIGHT - 4,
                255, 0, 0);
    }
    if ( (this->m_bcLastTrgX >= 0) && (this->m_bcLastTrgY >= 0) ) {
        sx  = ((this->m_bcLastTrgX) * SQUARE_WIDTH) + LEFT_MARGIN;
        sy  = ((this->m_bcLastTrgY) * SQUARE_HEIGHT) + TOP_MARGIN;

        bmpTrg->drawRectangle(
                sx + 2,  sy + 2,
                SQUARE_WIDTH - 3,  SQUARE_HEIGHT - 3,
                255, 0, 0);
    }

    //  盤上にある駒を表示する。    //
    for ( int y = 0; y < POS_NUM_ROWS; ++ y ) {
        for ( int x = 0; x < POS_NUM_COLS; ++ x ) {
            dx  = (x * SQUARE_WIDTH) + LEFT_MARGIN;
            dy  = ((y + BOARD_TOP_OFFSET) * SQUARE_HEIGHT) + TOP_MARGIN;
            const  PieceIndex   dp  = vb.fpBoard[y][x];
            if ( dp == 0 ) { continue; }

            sx  = ((dp - 1) % 14) * SQUARE_WIDTH;
            sy  = ((dp - 1) / 14) * SQUARE_HEIGHT;
            bmpTrg->copyRectangleWithTransparentColor(
                    dx, dy, SQUARE_WIDTH, SQUARE_HEIGHT,
                    *(this->m_brPiece), sx, sy,
                    255, 255, 255);
        }
    }

    //  後手の持ち駒を表示する。    //
    for ( PlayerIndex i = 0; i < vb.numPlayers; ++ i ) {
        const  PieceIndex  numHand  =  vb.numHandTypes[i];
        for ( PieceIndex c = 0;  c < numHand;  ++ c )
        {
            const   Common::EHandPiece  piHand  =  vb.hpIndex[i][c];
            const   THandCount          hcHand  =  vb.hpCount[i][c];
            if ( hcHand <= 0 )  { continue; }

            dx  = (c * SQUARE_WIDTH) + LEFT_MARGIN;
            dy  = TOP_MARGIN;
            if ( i == 0 ) {
                dy  += (POS_NUM_ROWS + BOARD_TOP_OFFSET) * SQUARE_HEIGHT;
                sx  =  (piHand - Common::HAND_BLACK_PAWN) * SQUARE_WIDTH;
            } else {
                sx  =  (piHand - Common::HAND_WHITE_PAWN) * SQUARE_WIDTH;
            }

            sy  = (i) * SQUARE_HEIGHT;
            bmpTrg->copyRectangle(
                    dx, dy, SQUARE_WIDTH, SQUARE_HEIGHT,
                    *(this->m_brPiece), sx, sy);
        }
    }

    //  移動できるマスを強調表示する。  //
    for ( int y = 0; y < POS_NUM_ROWS; ++ y ) {
        for ( int x = 0; x < POS_NUM_COLS; ++ x ) {
            if ( this->m_tblHighLight[y][x] == BOOL_TRUE ) {
                continue;
            }
            dx  = (x * SQUARE_WIDTH) + LEFT_MARGIN;
            dy  = ((y + BOARD_TOP_OFFSET) * SQUARE_HEIGHT) + TOP_MARGIN;

            bmpTrg->drawTransparentRectangle(
                    dx,  dy,  SQUARE_WIDTH,  SQUARE_HEIGHT,
                    0,  0,  0,  128);
        }
    }

    //  選択しているマスがあれば強調表示。  //
    if ( (this->m_bcSelX >= 0) && (this->m_bcSelY >= 0) ) {
        sx  = ((this->m_bcSelX) * SQUARE_WIDTH) + LEFT_MARGIN;
        sy  = ((this->m_bcSelY) * SQUARE_HEIGHT) + TOP_MARGIN;

        bmpTrg->drawTransparentRectangle(
                sx,  sy,  SQUARE_WIDTH,  SQUARE_HEIGHT,
                0,  255,  0,    128);
    }

    //  移動先として現在マウスが示しているマスを強調表示。  //
    if ( (this->m_bcMovX >= 0) && (this->m_bcMovY >= 0) ) {
        sx  = ((this->m_bcMovX) * SQUARE_WIDTH) + LEFT_MARGIN;
        sy  = ((this->m_bcMovY) * SQUARE_HEIGHT) + TOP_MARGIN;

        bmpTrg->drawTransparentRectangle(
                sx,  sy,  SQUARE_WIDTH,  SQUARE_HEIGHT,
                0,  0,  255,    128);
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
        const  DWORD        fwKeys,
        const  WindowCoord  xPos,
        const  WindowCoord  yPos)
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
        if ( 5 /* (HANDS_WHITE_KING - HANDS_WHITE_PAWN + 1)*/  <= mx ) {
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
        updateHighLightInfo();
    }

    return ( EH_RESULT_REDRAW );
}

//----------------------------------------------------------------
//    マウスの左ボタンを離した時のイベントハンドラ。
//

BoardScreen::EventResult
BoardScreen::onLButtonUp(
        const  DWORD        fwKeys,
        const  WindowCoord  xPos,
        const  WindowCoord  yPos)
{
    UTL_HELP_UNUSED_ARGUMENT(fwKeys);

    ::ReleaseCapture();

    if ( (this->m_bcSelX < 0) || (this->m_bcSelY < 0) ) {
        return ( EH_RESULT_SUCCESS );
    }

    const  BoardCoord   mx  = ((int)(xPos) - LEFT_MARGIN) / SQUARE_WIDTH;
    const  BoardCoord   my  = ((int)(yPos) - TOP_MARGIN) / SQUARE_HEIGHT;

    //  画面の範囲外でマウスボタンを離した場合は、キャンセルする。  //
    if ( (mx < BOARD_LEFT_OFFSET) || (my < 0)
            || (POS_NUM_COLS + BOARD_LEFT_OFFSET <= mx)
            || (VIEW_NUM_ROWS <= my) )
    {
        clearSelection();
        return ( EH_RESULT_REDRAW );
    }
    if ( (my == 0) || (my == (POS_NUM_ROWS + BOARD_TOP_OFFSET)) ) {
        //  持ち駒の表示エリアの場合。  //
        if ( (this->m_ddMode) != DDM_SELECT_SOURCE ) {
            clearSelection();
            return ( EH_RESULT_REDRAW );
        }
    }

    //  クリックモードになっている場合は、移動先を指定する。    //
    if ( (this->m_ddMode) == DDM_CLICKS ) {
        if ( (this->m_bcSelX == mx) && (this->m_bcSelY == my) ) {
            //  移動元と同じ場所を選択した場合は、キャンセル。  //
            clearSelection();
        } else if ( (this->m_bcMovX == mx) && (this->m_bcMovY == my) ) {
            //  同じ場所を二回クリックしたので処理を確定する。  //
            setActionInput(
                    this->m_bcSelX, this->m_bcSelY, mx, my,
                    Common::ALF_LEGAL_ACTION);
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
        setActionInput(
                this->m_bcSelX, this->m_bcSelY, mx, my,
                Common::ALF_LEGAL_ACTION);
        clearSelection();
    }

    return ( EH_RESULT_REDRAW );
}

//----------------------------------------------------------------
//    マウスを移動させた時のイベントハンドラ。
//

BoardScreen::EventResult
BoardScreen::onMouseMove(
        const  DWORD        fwKeys,
        const  WindowCoord  xPos,
        const  WindowCoord  yPos)
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
    ErrCode     retErr  =  this->m_gcGameCtrl.resetGame();
    updateHighLightInfo();
    return ( retErr );
}

//----------------------------------------------------------------
//    必要な画像データを準備する。
//

ErrCode
BoardScreen::setupBitmapImages(
        const   HINSTANCE   hInstance,
        const   HDC         hDC,
        const   LPCTSTR     imgBack,
        const   LPCTSTR     imgPiece)
{
    this->m_brBack  = new  BitmapResource;
    this->m_brBack->createBitmap(832, 640, hDC);
    if ( this->m_brBack->loadBitmapResource(hInstance, hDC, imgBack)
            != ERR_SUCCESS )
    {
        return ( ERR_FAILURE );
    }

    this->m_brPiece = new  BitmapResource;
    this->m_brPiece->createBitmap(896, 128, hDC);
    if ( this->m_brPiece->loadBitmapResource(hInstance, hDC, imgPiece)
            != ERR_SUCCESS )
    {
        return ( ERR_FAILURE );
    }

    return ( ERR_SUCCESS );
}

//----------------------------------------------------------------
//    必要な画像データを準備する。
//

ErrCode
BoardScreen::setupBitmapImages(
        const  std::string  &imgBack,
        const  std::string  &imgPiece)
{
    this->m_brBack  = new  BitmapResource;
    if ( this->m_brBack->openBitmapFile(imgBack) != ERR_SUCCESS ) {
        return ( ERR_FAILURE );
    }

    this->m_brPiece = new  BitmapResource;
    if ( this->m_brPiece->openBitmapFile(imgPiece) != ERR_SUCCESS ) {
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

    updateHighLightInfo();

    return ( ERR_SUCCESS );
}

//----------------------------------------------------------------
//    最後に入力した指し手で盤面を戻す。
//

ErrCode
BoardScreen::playBackward()
{
    BoardScreen::GameInterface  &
            giGame  =  this->getGameController();

    const  ErrCode  retErr  = giGame.playBackward();
    if ( retErr != ERR_SUCCESS ) {
        ::MessageBox(
                NULL,  "Cannot Rewind!\nBut Changed Player.",
                NULL,  MB_OK);
    }
    giGame.setPlayerToNext();
    giGame.setConstraint(Common::DICE_DEFAULT_VALUE);
    this->m_flgDiceRoll = DICE_NOT_ROLLED;

    this->m_bcSrcX  = -1;
    this->m_bcSrcY  = -1;
    this->m_bcTrgX  = -1;
    this->m_bcTrgY  = -1;
    clearSelection();

    //  強調表示を行うための情報を更新する。    //
    ActionViewList  actList;
    giGame.writeActionList(actList);

    updateHighLightInfo();
    if ( !(actList.empty()) ) {
        updateLastActionHighLights(actList.back());
    } else {
        this->m_bcLastSrcX  = -1;
        this->m_bcLastSrcY  = -1;
        this->m_bcLastTrgX  = -1;
        this->m_bcLastTrgY  = -1;
    }

    return ( retErr );
}

//----------------------------------------------------------------
//    指定した指し手で盤面を進める。
//

ErrCode
BoardScreen::playForward(
        const  ActionView   &actFwd)
{
    BoardScreen::GameInterface  &
            giGame  =  this->getGameController();

    giGame.playForward(actFwd);
    giGame.setPlayerToNext();
    giGame.setConstraint(Common::DICE_DEFAULT_VALUE);
    this->m_flgDiceRoll = DICE_NOT_ROLLED;

    this->m_bcSrcX  = -1;
    this->m_bcSrcY  = -1;
    this->m_bcTrgX  = -1;
    this->m_bcTrgY  = -1;
    clearSelection();

    //  最後の指し手を棋譜ファイルに書き込む。  //
    ActionViewList  actList;
    giGame.writeActionList(actList);

    if ( this->m_ofsKifu.good() && !(actList.empty()) ) {
        giGame.writeActionViewSfen(
                actList.back(), BOOL_TRUE, this->m_ofsKifu);
        this->m_ofsKifu << std::endl;
        this->m_ofsKifu.flush();
    }

    //  強調表示を行うための情報を更新する。    //
    updateHighLightInfo();
    if ( !(actList.empty()) ) {
        updateLastActionHighLights(actList.back());
    }

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

//----------------------------------------------------------------
//    ハイライト表示用の情報を更新する。
//

ErrCode
BoardScreen::updateHighLightInfo()
{
    for ( PosRow y = 0; y < POS_NUM_ROWS; ++ y ) {
        for ( PosCol x = 0; x < POS_NUM_COLS; ++ x ) {
            this->m_tblHighLight[y][x]  = BOOL_FALSE;
        }
    }

    ActionViewList  actList;
    const  GameInterface  & giGame  = (this->m_gcGameCtrl);
    giGame.makeLegalActionList(
            Common::ALF_LEGAL_ACTION, giGame.getConstraint(), actList);

    int    cSx  =  (-1);
    int    rSy  =  (-1);
    if ( (this->m_ddMode) != DDM_NOT_START ) {
        ActionView      actSrc;
        PromoteList     plDummy;
        setupActionView(
                giGame, this->m_bcSelX, this->m_bcSelY, 1, 1,
                &plDummy,   &actSrc);
        cSx = actSrc.xPlayOldCol;
        rSy = actSrc.yPlayOldRow;
    }

    const  ActIter  itrEnd  = actList.end();
    for ( ActIter itr = actList.begin(); itr != itrEnd; ++ itr ) {
        if ( (cSx >= 0) && ((itr->xPlayOldCol) != cSx) ) { continue; }
        if ( (rSy >= 0) && ((itr->yPlayOldRow) != rSy) ) { continue; }

        const  int  cNx = (POS_NUM_COLS - itr->xPlayNewCol);
        const  int  rNy = (itr->yPlayNewRow - 1);
        const  int  cOx = (POS_NUM_COLS - itr->xPlayOldCol);
        const  int  rOy = (itr->yPlayOldRow - 1);

        if ( (cOx < POS_NUM_COLS) && (0 <= rOy) ) {
            this->m_tblHighLight[rOy][cOx]  = BOOL_TRUE;
        }
        this->m_tblHighLight[rNy][cNx]  = BOOL_TRUE;
    }

    return ( ERR_FAILURE );
}

//----------------------------------------------------------------
//    直前の指し手を強調表示するための情報を更新する。
//

ErrCode
BoardScreen::updateLastActionHighLights(
        const  ActionView   &actView)
{
    if ( (actView.hpiDrop) == Common::HAND_EMPTY_PIECE ) {
        this->m_bcLastSrcX  = (POS_NUM_COLS - actView.xPlayOldCol);
        this->m_bcLastSrcY  = actView.yPlayOldRow;
    } else {
        this->m_bcLastSrcX  = s_tblHandSelX[actView.hpiDrop];
        this->m_bcLastSrcY  = s_tblHandSelY[actView.hpiDrop];
    }

    this->m_bcLastTrgX  = (POS_NUM_COLS - actView.xPlayNewCol);
    this->m_bcLastTrgY  = actView.yPlayNewRow;

    return ( ERR_SUCCESS );
}

//========================================================================
//
//    Accessors.
//

//----------------------------------------------------------------
//    思考エンジンの番号を取得する。
//

BoardScreen::EngineLevel
BoardScreen::getComputerLevel(
        const  PlayerIndex  cPlayer)  const
{
    return ( this->m_engLevels[cPlayer] );
}

//----------------------------------------------------------------
//    思考エンジンの番号を設定する。
//

ErrCode
BoardScreen::setComputerLevel(
        const  PlayerIndex  cPlayer,
        const  EngineLevel  eLevel)
{
    CONSTEXPR_VAR   EngineLevel
            NUM_ENGINES = getArraySize(s_tblEngineNames);
    if ( (eLevel < 0) || (NUM_ENGINES <= eLevel) )
    {
        return ( ERR_FAILURE );
    }

    this->m_engLevels[cPlayer]  =  eLevel;
    ErrCode     retErr  = ERR_SUCCESS;

    retErr  = this->m_gcGameCtrl.setComputerEngine(
                    cPlayer,  s_tblEngineNames[eLevel]);
    return ( retErr );
}

//----------------------------------------------------------------
//    合法手の制約を取得する。
//

BoardScreen::TConstraint
BoardScreen::getConstraint()  const
{
    return ( this->m_gcGameCtrl.getConstraint() );
}

//----------------------------------------------------------------
//    合法手の制約を指定する。
//

ErrCode
BoardScreen::setConstraint(
        const  TConstraint  vCons)
{
    BoardScreen::GameInterface  &
            giGame  =  this->getGameController();
    this->m_flgDiceRoll = DICE_ROLLED;

    return ( giGame.setConstraint(vCons) );
}

//----------------------------------------------------------------
//    現在の状態を示すフラグを取得する。
//

BoardScreen::ScreenState
BoardScreen::getCurrentState()  const
{
    return ( this->m_bsState );
}

//----------------------------------------------------------------
//    現在のダイスを表示するためのアイコンを取得する。
//

ErrCode
BoardScreen::getDiceDisplayIndex(
        int  *  const   pColIdx,
        int  *  const   pRowIdx)  const

{
    if ( (this->m_flgDiceRoll) == DICE_NOT_ROLLED ) {
        (*pColIdx)  = (15 % 6);
        (*pRowIdx)  = (15 / 6);
        return ( ERR_SUCCESS );
    }

    const   GameInterface    &  giGame  = getGameController();
    GameInterface::TConstraint  ccDice  = getConstraint() - 1;

    if ( (ccDice < 0) || (Common::DICE_MAX_VALUE <= ccDice) ) {
        ccDice  = Common::DICE_DEFAULT_VALUE;
    }
    (*pColIdx)  = ccDice;
    (*pRowIdx)  = giGame.getCurrentPlayer();

    return ( ERR_SUCCESS );
}

//----------------------------------------------------------------
//    現在のターンで、ダイスが振られたか否かを取得する。
//

Boolean
BoardScreen::isDiceRolled()  const
{
    return ( (this->m_flgDiceRoll == DICE_ROLLED)
             ? BOOL_TRUE : BOOL_FALSE );
}

//----------------------------------------------------------------
//    ゲームコントローラのインスタンスを取得する。
//

const   BoardScreen::GameInterface  &
BoardScreen::getGameController()  const
{
    return ( this->m_gcGameCtrl );
}

//----------------------------------------------------------------
//    ゲームコントローラのインスタンスを取得する。
//

BoardScreen::GameInterface  &
BoardScreen::getGameController()
{
    return ( this->m_gcGameCtrl );
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
    BoardScreen::GameInterface  &
            giGame  =  this->getGameController();

    ActionView  actView;
    PromoteList plDummy;

    setupActionView(
            giGame,     srcX,  srcY,  trgX,  trgY,
            &plDummy,   &actView);
    actView.fpAfter = iPrm;

    return ( playForward(actView) );
}

//----------------------------------------------------------------
//    移動先を指定して、移動可能性と成り駒選択肢を検査する。
//

ErrCode
BoardScreen::setActionInput(
        const  BoardCoord   srcX,
        const  BoardCoord   srcY,
        const  BoardCoord   trgX,
        const  BoardCoord   trgY,
        const  ActionFlag   fLeg)
{
    BoardScreen::GameInterface  &
            giGame  =  this->getGameController();

    if ( (srcX == trgX) && (srcY == trgY) ) {
        //  移動元と移動先が同じ場合はエラー。  //
        return ( ERR_FAILURE );
    }

    this->m_bcSrcX  = srcX;
    this->m_bcSrcY  = srcY;
    this->m_bcTrgX  = trgX;
    this->m_bcTrgY  = trgY;

    ActionView  actView;

    this->m_prmOptions.clear();
    setupActionView(
            giGame,   srcX,  srcY,  trgX,  trgY,
            &(this->m_prmOptions),  &actView);

    //  合法手のリストを取得して比較する。  //
    ActionViewList  actList;
    giGame.makeLegalActionList(fLeg, giGame.getConstraint(), actList);

    this->m_prmOptions.clear();
    const  ActIter  itrEnd  = actList.end();
    for ( ActIter itr = actList.begin(); itr != itrEnd; ++ itr ) {
        if (       ( (actView.xPlayNewCol) != (itr->xPlayNewCol) )
                || ( (actView.yPlayNewRow) != (itr->yPlayNewRow) )
                || ( (actView.xPlayOldCol) != (itr->xPlayOldCol) )
                || ( (actView.yPlayOldRow) != (itr->yPlayOldRow) )
                || ( (actView.hpiDrop)     != (itr->hpiDrop)     ) )
        {
            continue;
        }
        this->m_prmOptions.push_back(itr->fpAfter);
    }

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

}   //  End of namespace  Win32
FAIRYSHOGI_NAMESPACE_END
