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
**      An Implementation of DiceScreen class.
**
**      @file       Bin/Win32/DiceScreen.cpp
**/

#include    "DiceScreen.h"

#include    "FairyShogi/Common/FairyShogiConst.h"
#include    "FairyShogi/Interface/BitmapImage.h"

FAIRYSHOGI_NAMESPACE_BEGIN
namespace  Interface  {

//========================================================================
//
//    DiceScreen  class.
//

//========================================================================
//
//    Constructor(s) and Destructor.
//

//----------------------------------------------------------------
//    インスタンスを初期化する
//  （デフォルトコンストラクタ）。
//

DiceScreen::DiceScreen()
    : Super()
{
}

//----------------------------------------------------------------
//    インスタンスを指定したサイズで初期化する
//  （コンストラクタ）。
//

DiceScreen::DiceScreen(
        const  WindowCoord  wcLeft,
        const  WindowCoord  wcTop,
        const  WindowCoord  wcWidth,
        const  WindowCoord  wcHeight)
    : Super(wcLeft, wcTop, wcWidth, wcHeight)
{
}

//----------------------------------------------------------------
//    インスタンスを破棄する
//  （デストラクタ）。
//

DiceScreen::~DiceScreen()
{
}

//========================================================================
//
//    Public Member Functions (Implement Pure Virtual).
//

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
DiceScreen::setupBitmapImages(
        const  std::string  &imgDice)
{
    return ( Super::setupBitmapImages(imgDice, Common::DICE_MAX_VALUE, 2) );
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

DiceScreen::ChoiceIndex
DiceScreen::getUserSelect()  const
{
    return ( Super::getUserSelectIndex() );
}

//----------------------------------------------------------------
//    ユーザーに示す選択肢を設定する。
//

ErrCode
DiceScreen::setSelectionList(
        const  PlayerIndex  piTurn)
{
    OptionArray     vOpts;

    setupChoiceDisplay(3, 2, 128, 128);

    vOpts.clear();
    for ( ChoiceIndex i = 0; i < Common::DICE_MAX_VALUE; ++ i ) {
        vOpts.push_back(piTurn * Common::DICE_MAX_VALUE + i);
    }

    return ( Super::setChoiceList(vOpts) );
}

//========================================================================
//
//    For Internal Use Only.
//

}   //  End of namespace  Interface
FAIRYSHOGI_NAMESPACE_END
