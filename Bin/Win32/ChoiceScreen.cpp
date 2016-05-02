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
**      An Implementation of ChoiceScreen class.
**
**      @file       Bin/Win32/ChoiceScreen.cpp
**/

#include    "ChoiceScreen.h"

#include    "FairyShogi/Win32/BitmapResource.h"

FAIRYSHOGI_NAMESPACE_BEGIN
namespace  Win32  {

//========================================================================
//
//    ChoiceScreen  class.
//

//========================================================================
//
//    Constructor(s) and Destructor.
//

//----------------------------------------------------------------
//    インスタンスを初期化する
//  （デフォルトコンストラクタ）。
//

ChoiceScreen::ChoiceScreen()
    : m_prmOptions(),
      m_brPiece(nullptr),
      m_xSelCol(-1),
      m_ySelRow(-1),
      m_psSelected(-1),
      m_xImgWidth (0),
      m_yImgHeight(0),
      m_numSrcCols(0),
      m_numSrcRows(0),
      m_numSelCols(0),
      m_numSelRows(0)
{
}

//----------------------------------------------------------------
//    インスタンスを指定したサイズで初期化する
//  （コンストラクタ）。
//

ChoiceScreen::ChoiceScreen(
        const  WindowCoord  wcLeft,
        const  WindowCoord  wcTop,
        const  WindowCoord  wcWidth,
        const  WindowCoord  wcHeight)
    : Super(wcLeft, wcTop, wcWidth, wcHeight),
      m_prmOptions(),
      m_brPiece(nullptr),
      m_xSelCol(-1),
      m_ySelRow(-1),
      m_psSelected(-1),
      m_xImgWidth (0),
      m_yImgHeight(0),
      m_numSrcCols(0),
      m_numSrcRows(0),
      m_numSelCols(0),
      m_numSelRows(0)
{
}

//----------------------------------------------------------------
//    インスタンスを破棄する
//  （デストラクタ）。
//

ChoiceScreen::~ChoiceScreen()
{
    delete  this->m_brPiece;
    this->m_brPiece = (nullptr);
}

//========================================================================
//
//    Public Member Functions (Implement Pure Virtual).
//

//----------------------------------------------------------------
//    指定したビットマップイメージ上に内容を描画する。
//

ErrCode
ChoiceScreen::drawScreenLayer(
        BitmapImage  *  bmpTrg)  const
{
    typedef     OptionArray::const_iterator     OptIter;

    const  ChoiceIndex  numSrcCols  =  (this->m_numSrcCols);
    const  ChoiceSize   xImgWidth   =  (this->m_xImgWidth);
    const  ChoiceSize   yImgHeight  =  (this->m_yImgHeight);

    WindowCoord     dx  =  0;
    WindowCoord     dy  =  0;
    ChoiceIndex     ti  =  0;

    const  OptIter  itrEnd  = (this->m_prmOptions).end();
    for ( OptIter itr = this->m_prmOptions.begin(); itr != itrEnd; ++ itr )
    {
        const  ChoiceIndex  ci  =  (* itr);
        const  WindowCoord  sx  =  (ci % numSrcCols) * xImgWidth;
        const  WindowCoord  sy  =  (ci / numSrcCols) * yImgHeight;

        bmpTrg->copyRectangle(
                dx,  dy,  xImgWidth,  yImgHeight,
                *(this->m_brPiece),   sx,  sy);

        dx  +=  xImgWidth;
        ++  ti;
        if ( (this->m_numSelCols) <= ti ) {
            dx  =   0;
            ti  =   0;
            dy  +=  yImgHeight;
        }
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
//    必要な画像データを準備する。
//

ErrCode
ChoiceScreen::setupBitmapImages(
        const  HINSTANCE    hInstance,
        const  HDC          hDC,
        const  LPCTSTR      imgPiece,
        const  ChoiceIndex  numCols,
        const  ChoiceIndex  numRows,
        const  ChoiceSize   xWidth,
        const  ChoiceSize   yHeight)
{
    this->m_brPiece = new  BitmapResource;
    this->m_brPiece->createBitmap(numCols * xWidth, numRows * yHeight, hDC);

    if ( this->m_brPiece->loadBitmapResource(hInstance, hDC, imgPiece)
            != ERR_SUCCESS )
    {
        return ( ERR_FAILURE );
    }

    this->m_numSrcCols  =  numCols;
    this->m_numSrcRows  =  numRows;
    this->m_xImgWidth   =  xWidth;
    this->m_yImgHeight  =  yHeight;

    return ( ERR_SUCCESS );

}

//----------------------------------------------------------------
//    必要な画像データを準備する。
//

ErrCode
ChoiceScreen::setupBitmapImages(
        const  std::string  &imgPiece,
        const  ChoiceIndex  numCols,
        const  ChoiceIndex  numRows,
        const  ChoiceSize   xWidth,
        const  ChoiceSize   yHeight)
{
    this->m_brPiece = new  BitmapResource;
    if ( this->m_brPiece->openBitmapFile(imgPiece) != ERR_SUCCESS ) {
        return ( ERR_FAILURE );
    }

    this->m_numSrcCols  =  numCols;
    this->m_numSrcRows  =  numRows;
    this->m_xImgWidth   =  xWidth;
    this->m_yImgHeight  =  yHeight;

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

ChoiceScreen::ChoiceIndex
ChoiceScreen::getUserSelectCol()  const
{
    return ( this->m_xSelCol );
}

//----------------------------------------------------------------
//    ユーザーが選択したインデックスを取得する。
//

ChoiceScreen::ChoiceIndex
ChoiceScreen::getUserSelectIndex()  const
{
    return ( this->m_psSelected );
}

//----------------------------------------------------------------
//    ユーザーが選択したインデックスを取得する。
//

ChoiceScreen::ChoiceIndex
ChoiceScreen::getUserSelectRow()  const
{
    return ( this->m_ySelRow );
}

//----------------------------------------------------------------
//    ユーザーに示す選択肢を設定する。
//

ErrCode
ChoiceScreen::setChoiceList(
        const  OptionArray  &vSelect)
{
    this->m_prmOptions  = vSelect;
    return ( ERR_SUCCESS );
}

//----------------------------------------------------------------
//    選択肢の表示領域を設定する。
//

ErrCode
ChoiceScreen::setupChoiceDisplay(
        const  ChoiceIndex  numCols,
        const  ChoiceIndex  numRows,
        const  ChoiceSize   xWidth,
        const  ChoiceSize   yHeight)
{
    this->m_xImgWidth   =  xWidth;
    this->m_yImgHeight  =  yHeight;
    this->m_numSelCols  =  numCols;
    this->m_numSelRows  =  numRows;

    return ( ERR_SUCCESS );
}

//========================================================================
//
//    Protected Member Functions (Overrides).
//

//----------------------------------------------------------------
//    マウスの左ボタンを離した時のイベントハンドラ。
//

ChoiceScreen::EventResult
ChoiceScreen::onLButtonUp(
        const   DWORD   fwKeys,
        const   UINT    xPos,
        const   UINT    yPos)
{
    const  ChoiceSize   xImgWidth   =  (this->m_xImgWidth);
    const  ChoiceSize   yImgHeight  =  (this->m_yImgHeight);

    const  ChoiceIndex  numSelCols  =  (this->m_numSelCols);

    const  ChoiceIndex  xSelCol     =  (xPos / xImgWidth);
    const  ChoiceIndex  ySelRow     =  (yPos / yImgHeight);
    const  ChoiceIndex  iSelect     =  (ySelRow * numSelCols) + (xSelCol);
    const  ChoiceIndex  nSelMax     =  (this->m_prmOptions.size());

    if ( (iSelect < 0) || (nSelMax <= iSelect) ) {
        return ( EH_RESULT_REDRAW );
    }

    this->m_xSelCol     =  xSelCol;
    this->m_ySelRow     =  ySelRow;
    this->m_psSelected  =  iSelect;

    return ( EH_RESULT_REDRAW );
}

//========================================================================
//
//    For Internal Use Only.
//

}   //  End of namespace  Win32
FAIRYSHOGI_NAMESPACE_END
