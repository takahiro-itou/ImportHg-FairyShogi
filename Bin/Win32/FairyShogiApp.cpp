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
**      An Implementation of FairyShogiApp class.
**
**      @file       Bin/Win32/FairyShogiApp.cpp
**/

#include    "FairyShogiApp.h"

#include    "FairyShogi/Win32/BitmapResource.h"

#include    "Resources.h"

#include    <stdexcept>

FAIRYSHOGI_NAMESPACE_BEGIN
namespace  Win32  {

//========================================================================
//
//    FairyShogiApp  class.
//

//========================================================================
//
//    Constructor(s) and Destructor.
//

//----------------------------------------------------------------
//    インスタンスを初期化する
//  （デフォルトコンストラクタ）。
//

FairyShogiApp::FairyShogiApp()
    : m_brBack (nullptr),
      m_brPiece(nullptr),
      m_brDice (nullptr),
      m_brIcons(nullptr)
{
}

//----------------------------------------------------------------
//    インスタンスを破棄する
//  （デストラクタ）。
//

FairyShogiApp::~FairyShogiApp()
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
//    必要な画像リソースをロードする。
//

ErrCode
FairyShogiApp::loadBitmapResources(
        const   HINSTANCE   hInst,
        const   HDC         hDC)
{
    this->m_brBack  = new  BitmapResource;
    this->m_brBack->createBitmap(832, 640, hDC);
    if ( this->m_brBack->loadBitmapResource(
                    hInst,  hDC,
                    MAKEINTRESOURCE(IDB_BACK_BITMAP) ) != ERR_SUCCESS )
    {
        return ( ERR_FAILURE );
    }

    this->m_brPiece = new  BitmapResource;
    this->m_brPiece->createBitmap(896, 128, hDC);
    if ( this->m_brDice->loadBitmapResource(
                    hInst,  hDC,
                    MAKEINTRESOURCE(IDB_PIECE_BITMAP) ) != ERR_SUCCESS )
    {
        return ( ERR_FAILURE );
    }

    this->m_brDice  = new  BitmapResource;
    this->m_brDice->createBitmap(768, 384, hDC);
    if ( this->m_brDice->loadBitmapResource(
                    hInst,  hDC,
                    MAKEINTRESOURCE(IDB_DICE_BITMAP) ) != ERR_SUCCESS )
    {
        return ( ERR_FAILURE );
    }

    this->m_brIcons = new  BitmapResource;
    this->m_brIcons->createBitmap(320, 320, hDC);
    if ( this->m_brIcons->loadBitmapResource(
                    hInst,  hDC,
                    MAKEINTRESOURCE(IDB_ICONS_BITMAP) ) != ERR_SUCCESS )
    {
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
//    盤面の画像リソースを取得する。
//

const   BitmapResource  &
FairyShogiApp::getBackBitmap()  const
{
    if ( (this->m_brBack) == (nullptr) ) {
        throw  std::logic_error("Null Pointer Exception.");
    }
    return ( *(this->m_brBack) );
}

//----------------------------------------------------------------
//    ダイスの画像リソースを取得する。
//

const   BitmapResource  &
FairyShogiApp::getDiceBitmap()  const
{
    if ( (this->m_brDice) == (nullptr) ) {
        throw  std::logic_error("Null Pointer Exception.");
    }
    return ( *(this->m_brDice) );
}

//----------------------------------------------------------------
//    その他のアイコン画像リソースを取得する。
//

const   BitmapResource  &
FairyShogiApp::getIconsBitmap()  const
{
    if ( (this->m_brIcons) == (nullptr) ) {
        throw  std::logic_error("Null Pointer Exception.");
    }
    return ( *(this->m_brIcons) );
}

//----------------------------------------------------------------
//    駒の画像リソースを取得する。
//

const   BitmapResource  &
FairyShogiApp::getPieceBitmap()  const
{
    if ( (this->m_brPiece) == (nullptr) ) {
        throw  std::logic_error("Null Pointer Exception.");
    }
    return ( *(this->m_brPiece) );
}

//========================================================================
//
//    For Internal Use Only.
//

}   //  End of namespace  Win32
FAIRYSHOGI_NAMESPACE_END
