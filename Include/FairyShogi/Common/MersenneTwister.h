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
**      An Interface of MersenneTwister class.
**
**      @file       Common/MersenneTwister.h
**/

#if !defined( FAIRYSHOGI_COMMON_INCLUDED_MERSENNE_TWISTER_H )
#    define   FAIRYSHOGI_COMMON_INCLUDED_MERSENNE_TWISTER_H

#include    "FairyShogi/Common/FairyShogiTypes.h"

FAIRYSHOGI_NAMESPACE_BEGIN
namespace  Common  {

//========================================================================
//
//    MersenneTwister  class.
//
/**
**    乱数生成クラス。
**
**  このクラスでは、インスタンスを複製しておくことで、
**  後から同じ乱数系列を発生させることができる。
**  ただし、コピーコンストラクタと代入演算子は無効化されており、
**  暗黙的なコピーはできず、メソッドを使って明示的にコピーする。

**/

class  MersenneTwister
{

private:

    typedef     uint32_t        TSeedValue;
    typedef     uint32_t        TResultInt;

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
    MersenneTwister()
        : m_vSeeds(),
          m_sIndex(0)
    {
        setSeedValue(4357);
    }

    //----------------------------------------------------------------
    /**   インスタンスを初期化する
    **  （コンストラクタ）。
    **
    **  @param [in] uSeed   乱数系列のシード。
    **/
    MersenneTwister(
            const  TSeedValue   uSeed)
        : m_vSeeds(),
          m_sIndex(0),
    {
        setSeedValue(uSeed);
    }

    //----------------------------------------------------------------
    /**   インスタンスを破棄する
    **  （デストラクタ）。
    **
    **/
    ~MersenneTwister();

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
private:

    //  パラメータ。    //
    static  CONSTEXPR_VAR   int     N   =  624;
    static  CONSTEXPR_VAR   int     M   =  397;

    enum  {
        MATRIX_A    =  0x9908b0df,
        UPPER_MASK  =  0x80000000,
        LOWER_MASK  =  0x7FFFFFFF
    };

    enum  {
        TEMPERING_MASK_B    =  0x9d2c5680,
        TEMPERING_MASK_C    =  0xEFC60000,
        TEMPERING_SHR_U     =  11,
        TEMPERING_SHL_S     =  7,
        TEMPERING_SHL_T     =  15,
        TEMPERING_SHR_L     =  18
    };

    static  CONSTEXPR_VAR   TSeedValue
    s_tblMag[2] =  { 0,  MATRIX_A };

public:

    //----------------------------------------------------------------
    /**   乱数系列のクローンを作成する。
    **
    **  @param [in] objSrc    クローン元のインスタンス。
    **  @return     エラーコードを返す。
    **      -   異常終了の場合は、
    **          エラーの種類を示す非ゼロ値を返す。
    **      -   正常終了の場合は、ゼロを返す。
    **/
    ErrCode
    cloneFrom(
            const  MersenneTwister  &objSrc)
    {
        for ( int ii = 0; ii < N; ++ ii ) {
            this->m_vSeeds[ii]  =  objSrc.m_vSeeds[ii];
        }
        this->m_sIndex  =  objSrc.m_sIndex;

        return ( ERR_SUCCESS );
    }

    //----------------------------------------------------------------
    /**   乱数系列の次の値を取得する。
    **
    **/
    TResultInt
    getNext()
    {
        TSeedValue  *  const    vS  =  (this->m_vSeeds);
        int         idxCur  = (this->m_sIndex);
        TSeedValue  vt      = 0;
        if ( (idxCur >= N) ) {
            int     ii  = 0;
            for ( ; ii < N - M; ++ ii ) {
                vt      = (vS[ii] & UPPER_MASK) | (vS[ii+1] & LOWER_MASK);
                vS[ii]  = vS[ii + M] ^ (vt >> 1) ^ s_tblMag[vt & 0x01];
            }
            for ( ; ii < N - 1; ++ ii ) {
                vt      = (vS[ii] & UPPER_MASK) | (vS[ii+1] & LOWER_MASK);
                vS[ii]  = vS[ii+M-N] ^ (vt >> 1) ^ s_tblMag[vt & 0x01];
            }
            {
                vt      = (vS[N-1] & UPPER_MASK) | (vS[0] & LOWER_MASK);
                vS[N-1] = vS[M - 1]  ^ (vt >> 1) ^ s_tblMag[vt & 0x01];
            }
            idxCur  = 0;
        }

        vt  =   vS[idxCur];
        vt  ^=  ((vt >> TEMPERING_SHR_U));
        vt  ^=  ((vt << TEMPERING_SHL_S) & TEMPERING_MASK_B);
        vt  ^=  ((vt << TEMPERING_SHL_T) & TEMPERING_MASK_C);
        vt  ^=  ((vt >> TEMPERING_SHR_L));

        this->m_sIndex  =  (idxCur + 1);

        return ( vt );
    }

    //----------------------------------------------------------------
    /**   乱数系列のシードを設定する。
    **
    **  @param [in] uSeed   乱数系列のシード。
    **      ただし、シードにゼロを指定することはできない。
    **  @return     エラーコードを返す。
    **      -   異常終了の場合は、
    **          エラーの種類を示す非ゼロ値を返す。
    **      -   正常終了の場合は、ゼロを返す。
    **/
    ErrCode
    setSeedValue(
            const  TSeedValue   uSeed)
    {
        TSeedValue  seqVal  = (uSeed & 0xFFFFFFFF);
        this->m_vSeeds[0]   = seqVal;
        for ( int idx = 0; idx < N; ++ idx ) {
            this->m_vSeeds[idx] = seqVal = (69069 * seqVal) & 0xFFFFFFFF;
        }
        this->m_sIndex  =  N;
        return ( ERR_SUCCESS );
    }

//========================================================================
//
//    Protected Member Functions.
//

//========================================================================
//
//    For Internal Use Only.
//

//========================================================================
//
//    Member Variables.
//
private:

    TSeedValue      m_vSeeds[N];
    int             m_sIndex;

//========================================================================
//
//    Other Features.
//
private:
    typedef     MersenneTwister     This;
    MersenneTwister     (const  This  &);
    This &  operator =  (const  This  &);
public:
    //  テストクラス。  //
    friend  class   MersenneTwisterTest;
};

}   //  End of namespace  Common
FAIRYSHOGI_NAMESPACE_END

#endif
