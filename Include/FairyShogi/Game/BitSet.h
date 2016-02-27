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
    BitSet()
        : m_bsBlock(0)
    { }

    //----------------------------------------------------------------
    /**   インスタンスを破棄する
    **  （デストラクタ）。
    **
    **/
    ~BitSet()
    { }

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
public:

    //----------------------------------------------------------------
    /**   全てのビットを零にリセットする。
    **
    **  @return     エラーコードを返す。
    **      -   異常終了の場合は、
    **          エラーの種類を示す非ゼロ値を返す。
    **      -   正常終了の場合は、ゼロを返す。
    **/
    ErrCode
    clearAllBits();

//========================================================================
//
//    Accessors.
//
public:

    //----------------------------------------------------------------
    /**   インデックスで指定した場所の値を取得する。
    **
    **  @param [in] fiPos   インデックス。
    **  @return     指定した場所のビットを返す。
    **/
    ReturnType
    getBitValue(
            const  FieldIndex   fiPos);

    //----------------------------------------------------------------
    /**   ブロックの値をまとめて取得する。
    **
    **  @return     指定したブロックの値を返す。
    **/
    TBlockElem
    getValueBlock()  const;

    //----------------------------------------------------------------
    /**   指定したインデックスの値を零にリセットする。
    **
    **  @param [in] fiPos   インデックス。
    **  @return     エラーコードを返す。
    **      -   異常終了の場合は、
    **          エラーの種類を示す非ゼロ値を返す。
    **      -   正常終了の場合は、ゼロを返す。
    **/
    ErrCode
    resetBitValue(
            const  FieldIndex   fiPos);

    //----------------------------------------------------------------
    /**   指定したインデックスの値を壱にセットする。
    **
    **  @param [in] fiPos   インデックス。
    **  @return     エラーコードを返す。
    **      -   異常終了の場合は、
    **          エラーの種類を示す非ゼロ値を返す。
    **      -   正常終了の場合は、ゼロを返す。
    **/
    ErrCode
    setBitValue(
            const  FieldIndex   fiPos);

//========================================================================
//
//    For Internal Use Only.
//

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
//    全てのビットを零にリセットする。
//

inline  ErrCode
BitSet::clearAllBits()
{
    this->m_bsBlock = 0;
    return ( ERR_SUCCESS );
}

//----------------------------------------------------------------
//    インデックスで指定した場所の値を取得する。
//

inline  BitSet::ReturnType
BitSet::getBitValue(
        const  FieldIndex   fiPos)
{
    return ( ((this->m_bsBlock) >> (fiPos)) & 1 );
}

//----------------------------------------------------------------
//    ブロックの値をまとめて取得する。
//

inline  BitSet::TBlockElem
BitSet::getValueBlock()  const
{
    return ( (this->m_bsBlock) );
}

//----------------------------------------------------------------
//    指定したインデックスの値を零にリセットする。
//

inline  ErrCode
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

inline  ErrCode
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
