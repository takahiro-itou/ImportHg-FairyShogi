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
**      An Interface of BitSet class.
**
**      @file       Game/BitSet.h
**/

#if !defined( FAIRYSHOGI_GAME_INCLUDED_BIT_SET_H )
#    define   FAIRYSHOGI_GAME_INCLUDED_BIT_SET_H

#include    "FairyShogi/Common/FairyShogiTypes.h"

FAIRYSHOGI_NAMESPACE_BEGIN
namespace  Game  {

//========================================================================
//
//    BitSet  class.
//
/**
**    盤面の各座標に対応するビットセットクラス。
**/

class  BitSet
{
private:
    typedef     uint32_t        TBlockElem;

public:
    typedef     TBlockElem      ReturnType;

//========================================================================
//
//    Constructor(s) and Destructor.
//
public:

    //----------------------------------------------------------------
    /**   インスタンスを初期化する
    **  （デフォルトコンストラクタ）。
    **
    **/
    BitSet();

    //----------------------------------------------------------------
    /**   インスタンスを破棄する
    **  （デストラクタ）。
    **
    **/
    ~BitSet();

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

//========================================================================
//
//    Public Member Functions.
//

//========================================================================
//
//    Accessors.
//
public:

    //----------------------------------------------------------------
    /**   指定したインデックスの値を取得する。
    **
    **/
    ReturnType
    getBitValue(
            const  FieldIndex   fiPos);

    //----------------------------------------------------------------
    /**   指定したインデックスの値を零にリセットする。
    **
    **  @param [in] fiPos   インデックス。
    **  @return     void.
    **/
    ErrCode
    resetBitValue(
            const  FieldIndex   fiPos);

    //----------------------------------------------------------------
    /**   指定したインデックスの値を壱にセットする。
    **
    **  @param [in] fiPos   インデックス。
    **  @retval     書き込んだ値を返す。
    **/
    ErrCode
    setBitValue(
            const  FieldIndex   fiPos);

//========================================================================
//
//    For Internal Use Only.
//
private:

//========================================================================
//
//    Member Variables.
//
private:

    /**   ビットセット。    **/
    TBlockElem      m_bsBlock;

//========================================================================
//
//    Other Features.
//
private:

public:
    //  テストクラス。  //
    friend  class   BitSetTest;
};

//========================================================================
//
//    Implementation of Inline Functions.
//

//----------------------------------------------------------------
//    指定したインデックスの値を取得する。
//

ReturnType
BitSet::getBitValue(
        const  FieldIndex   fiPos)
{
    return ( ((this->m_bsBlock) >> (fiPos)) & 1 );
}

//----------------------------------------------------------------
//    指定したインデックスの値を零にリセットする。
//

ErrCode
BitSet::resetBitValue(
        const  FieldIndex   fiPos)
{
    const   TBlockElem  bWrite  = (static_cast<TBlockElem>(1) << fiPos);
    this->m_bsBlock &= (~ bWrite);
    return ( ERR_SUCCESS );
}

//----------------------------------------------------------------
//    指定したインデックスの値を壱にセットする。
//

ErrCode
BitSet::setBitValue(
        const  FieldIndex   fiPos)
{
    const   TBlockElem  bWrite  = (static_cast<TBlockElem>(1) << fiPos);
    this->m_bsBlock |= (bWrite);
    return ( ERR_SUCCESS );
}


}   //  End of namespace  Game
FAIRYSHOGI_NAMESPACE_END

#endif
