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
**      An Implementation of PromotionScreen class.
**
**      @file       Bin/Win32/PromotionScreen.cpp
**/

#include    "PromotionScreen.h"

#include    "FairyShogi/Interface/BitmapImage.h"

FAIRYSHOGI_NAMESPACE_BEGIN
namespace  Interface  {

//========================================================================
//
//    PromotionScreen  class.
//

//========================================================================
//
//    Constructor(s) and Destructor.
//

//----------------------------------------------------------------
//    インスタンスを初期化する
//  （デフォルトコンストラクタ）。
//

PromotionScreen::PromotionScreen()
    : m_prmOptions(),
      m_biPiece(nullptr),
      m_psSelected(-1)
{
}

//----------------------------------------------------------------
//    インスタンスを指定したサイズで初期化する
//  （コンストラクタ）。
//

PromotionScreen::PromotionScreen(
        const  WindowCoord  wcLeft,
        const  WindowCoord  wcTop,
        const  WindowCoord  wcWidth,
        const  WindowCoord  wcHeight)
    : Super(wcLeft, wcTop, wcWidth, wcHeight),
      m_prmOptions(),
      m_biPiece(nullptr),
      m_psSelected(-1)
{
}

//----------------------------------------------------------------
//    インスタンスを破棄する
//  （デストラクタ）。
//

PromotionScreen::~PromotionScreen()
{
    delete  this->m_biPiece;
    this->m_biPiece = (nullptr);
}

//========================================================================
//
//    Public Member Functions (Implement Pure Virtual).
//

//----------------------------------------------------------------
//    指定したビットマップイメージ上に内容を描画する。
//

ErrCode
PromotionScreen::drawScreenLayer(
        BitmapImage  *  bmpTrg)  const
{
    typedef     OptionArray::const_iterator     OptIter;

    const  WindowCoord  wcWidth = getWidth();
    WindowCoord         dx  = 0;
    WindowCoord         dy  = 0;

    const  OptIter  itrEnd  = (this->m_prmOptions).end();
    for ( OptIter itr = this->m_prmOptions.begin(); itr != itrEnd; ++ itr )
    {
        const  PieceIndex   pi  = (* itr);
        const  WindowCoord  sx  = ((pi - 1) % 14) * SQUARE_WIDTH;
        const  WindowCoord  sy  = ((pi - 1) / 14) * SQUARE_HEIGHT;

        bmpTrg->copyRectangle(
                dx, dy, SQUARE_WIDTH, SQUARE_HEIGHT,
                *(this->m_biPiece), sx, sy);

        dx  += SQUARE_WIDTH;
        if ( wcWidth < dx + SQUARE_WIDTH ) {
            dx  =   0;
            dy  +=  SQUARE_HEIGHT;
        }
    }

    return ( ERR_SUCCESS );
}

//========================================================================
//
//    Public Member Functions (Overrides).
//


//----------------------------------------------------------------
//    マウスの左ボタンを離した時のイベントハンドラ。
//

PromotionScreen::EventResult
PromotionScreen::onLButtonUp(
        const   DWORD   fwKeys,
        const   UINT    xPos,
        const   UINT    yPos)
{
    const  WindowCoord  wcWidth = getWidth();
    const  PieceIndex   numCols = wcWidth / SQUARE_WIDTH;

    const  PieceIndex   xSelCol = (xPos / SQUARE_WIDTH);
    const  PieceIndex   ySelRow = (yPos / SQUARE_HEIGHT);

    const  PieceIndex   iSelect = (ySelRow * numCols) + (xSelCol);
    const  PieceIndex   nSelMax = (this->m_prmOptions.size());

    if ( (iSelect < 0) || (nSelMax <= iSelect) ) {
        return ( EH_RESULT_REDRAW );
    }

    this->m_psSelected  =  iSelect;

    return ( EH_RESULT_REDRAW );
}

//========================================================================
//
//    Public Member Functions (Pure Virtual Functions).
//

//========================================================================
//
//    Public Member Functions (Virtual Functions).
//

//----------------------------------------------------------------
//    必要な画像データを準備する。
//

ErrCode
PromotionScreen::setupBitmapImages(
        const  std::string  &imgPiece)
{
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

//----------------------------------------------------------------
//    ユーザーが選択したインデックスを取得する。
//

PieceIndex
PromotionScreen::getUserSelect()  const
{
    return ( this->m_psSelected );
}

//----------------------------------------------------------------
//    ユーザーに示す選択肢を設定する。
//

ErrCode
PromotionScreen::setSelectionList(
        const  OptionArray  &vSelect)
{
    this->m_prmOptions  = vSelect;
    return ( ERR_SUCCESS );
}

//========================================================================
//
//    For Internal Use Only.
//

}   //  End of namespace  Interface
FAIRYSHOGI_NAMESPACE_END
