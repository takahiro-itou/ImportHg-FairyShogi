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
**      An Interface of CommandInterpreter class.
**
**      @file       Bin/CommandInterpreter.h
**/

#if !defined( FAIRYSHOGI_BIN_INCLUDED_COMMAND_INTERPRETER_H )
#    define   FAIRYSHOGI_BIN_INCLUDED_COMMAND_INTERPRETER_H

#include    "FairyShogi/Common/FairyShogiTypes.h"

#include    "FairyShogi/Interface/ConsoleInterface.h"

#include    <fstream>

FAIRYSHOGI_NAMESPACE_BEGIN
namespace  Interface  {

//========================================================================
//
//    CommandInterpreter  class.
//
/**
**    コンソール版のコマンドインタープリタークラス。
**/

class  CommandInterpreter
{

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
    CommandInterpreter();

    //----------------------------------------------------------------
    /**   インスタンスを破棄する
    **  （デストラクタ）。
    **
    **/
    virtual  ~CommandInterpreter();

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
public:

    //----------------------------------------------------------------
    /**   コンソールからの入力を解釈して実行する。
    **
    **  @param [in] strLine   入力テキスト。
    **  @param[out] outStr    出力ストリーム。
    **  @return     エラーコードを返す。
    **      -   異常終了の場合は、
    **          エラーの種類を示す非ゼロ値を返す。
    **      -   正常終了の場合は、ゼロを返す。
    **/
    virtual  ErrCode
    interpretConsoleInput(
            const  std::string  &strLine,
            std::ostream        &outStr);

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
private:

    typedef     ConsoleInterface::ActionViewList    ActionList;
    typedef     ActionList::const_iterator          ActIter;

    typedef     ConsoleInterface::ActionView        ActionView;
    typedef     ConsoleInterface::ActionData        ActionData;

    typedef     CommandInterpreter                  CallbackClass;

    /**
    **    各コマンドを実行する関数を保持する関数ポインタ型。
    **/
    typedef     ErrCode  (*  LpFnExecuteCommand)(
            const  std::string  &strArgs,
            ConsoleInterface    &objGame,
            std::ostream        &outStr,
            CallbackClass       &ciClbk);

    typedef     std::vector< std::string >          TokenArray;

private:

    //----------------------------------------------------------------
    /**
    **
    **/
    static  std::ostream  &
    displayActionView(
            const  ActionView   &actView,
            const  int          flgName,
            std::ostream        &outStr);

    //----------------------------------------------------------------
    /**   コマンドを実行する。
    **
    **  @param [in]     strArgs   コマンドの引数。
    **  @param [in,out] objGame   ゲーム管理インスタンス。
    **  @param    [out] outStr    出力ストリーム。
    **  @param [in,out] ciClbk    コールバックインスタンス。
    **  @return     エラーコードを返す。
    **      -   異常終了の場合は、
    **          エラーの種類を示す非ゼロ値を返す。
    **      -   正常終了の場合は、ゼロを返す。
    **/
    static  ErrCode
    executeBackwardCommand(
            const  std::string  &strArgs,
            ConsoleInterface    &objGame,
            std::ostream        &outStr,
            CallbackClass       &ciClbk);

    //----------------------------------------------------------------
    /**   コマンドを実行する。
    **
    **  @param [in]     strArgs   コマンドの引数。
    **  @param [in,out] objGame   ゲーム管理インスタンス。
    **  @param    [out] outStr    出力ストリーム。
    **  @param [in,out] ciClbk    コールバックインスタンス。
    **  @return     エラーコードを返す。
    **      -   異常終了の場合は、
    **          エラーの種類を示す非ゼロ値を返す。
    **      -   正常終了の場合は、ゼロを返す。
    **/
    static  ErrCode
    executeDiceCommand(
            const  std::string  &strArgs,
            ConsoleInterface    &objGame,
            std::ostream        &outStr,
            CallbackClass       &ciClbk);

    //----------------------------------------------------------------
    /**   コマンドを実行する。
    **
    **  @param [in]     strArgs   コマンドの引数。
    **  @param [in,out] objGame   ゲーム管理インスタンス。
    **  @param    [out] outStr    出力ストリーム。
    **  @param [in,out] ciClbk    コールバックインスタンス。
    **  @return     エラーコードを返す。
    **      -   異常終了の場合は、
    **          エラーの種類を示す非ゼロ値を返す。
    **      -   正常終了の場合は、ゼロを返す。
    **/
    static  ErrCode
    executeFlipCommand(
            const  std::string  &strArgs,
            ConsoleInterface    &objGame,
            std::ostream        &outStr,
            CallbackClass       &ciClbk);

    //----------------------------------------------------------------
    /**   コマンドを実行する。
    **
    **  @param [in]     strArgs   コマンドの引数。
    **  @param [in,out] objGame   ゲーム管理インスタンス。
    **  @param    [out] outStr    出力ストリーム。
    **  @param [in,out] ciClbk    コールバックインスタンス。
    **  @return     エラーコードを返す。
    **      -   異常終了の場合は、
    **          エラーの種類を示す非ゼロ値を返す。
    **      -   正常終了の場合は、ゼロを返す。
    **/
    static  ErrCode
    executeForwardCommand(
            const  std::string  &strArgs,
            ConsoleInterface    &objGame,
            std::ostream        &outStr,
            CallbackClass       &ciClbk);

    //----------------------------------------------------------------
    /**   コマンドを実行する。
    **
    **  @param [in]     strArgs   コマンドの引数。
    **  @param [in,out] objGame   ゲーム管理インスタンス。
    **  @param    [out] outStr    出力ストリーム。
    **  @param [in,out] ciClbk    コールバックインスタンス。
    **  @return     エラーコードを返す。
    **      -   異常終了の場合は、
    **          エラーの種類を示す非ゼロ値を返す。
    **      -   正常終了の場合は、ゼロを返す。
    **/
    static  ErrCode
    executeGoCommand(
            const  std::string  &strArgs,
            ConsoleInterface    &objGame,
            std::ostream        &outStr,
            CallbackClass       &ciClbk);

    //----------------------------------------------------------------
    /**   コマンドを実行する。
    **
    **  @param [in]     strArgs   コマンドの引数。
    **  @param [in,out] objGame   ゲーム管理インスタンス。
    **  @param    [out] outStr    出力ストリーム。
    **  @param [in,out] ciClbk    コールバックインスタンス。
    **  @return     エラーコードを返す。
    **      -   異常終了の場合は、
    **          エラーの種類を示す非ゼロ値を返す。
    **      -   正常終了の場合は、ゼロを返す。
    **/
    static  ErrCode
    executeListCommand(
            const  std::string  &strArgs,
            ConsoleInterface    &objGame,
            std::ostream        &outStr,
            CallbackClass       &ciClbk);

    //----------------------------------------------------------------
    /**   コマンドを実行する。
    **
    **  @param [in]     strArgs   コマンドの引数。
    **  @param [in,out] objGame   ゲーム管理インスタンス。
    **  @param    [out] outStr    出力ストリーム。
    **  @param [in,out] ciClbk    コールバックインスタンス。
    **  @return     エラーコードを返す。
    **      -   異常終了の場合は、
    **          エラーの種類を示す非ゼロ値を返す。
    **      -   正常終了の場合は、ゼロを返す。
    **/
    static  ErrCode
    executePlayerCommand(
            const  std::string  &strArgs,
            ConsoleInterface    &objGame,
            std::ostream        &outStr,
            CallbackClass       &ciClbk);

    //----------------------------------------------------------------
    /**   コマンドを実行する。
    **
    **  @param [in]     strArgs   コマンドの引数。
    **  @param [in,out] objGame   ゲーム管理インスタンス。
    **  @param    [out] outStr    出力ストリーム。
    **  @param [in,out] ciClbk    コールバックインスタンス。
    **  @return     エラーコードを返す。
    **      -   異常終了の場合は、
    **          エラーの種類を示す非ゼロ値を返す。
    **      -   正常終了の場合は、ゼロを返す。
    **/
    static  ErrCode
    executePositionCommand(
            const  std::string  &strArgs,
            ConsoleInterface    &objGame,
            std::ostream        &outStr,
            CallbackClass       &ciClbk);

    //----------------------------------------------------------------
    /**   コマンドを実行する。
    **
    **  @param [in]     strArgs   コマンドの引数。
    **  @param [in,out] objGame   ゲーム管理インスタンス。
    **  @param    [out] outStr    出力ストリーム。
    **  @param [in,out] ciClbk    コールバックインスタンス。
    **  @return     エラーコードを返す。
    **      -   異常終了の場合は、
    **          エラーの種類を示す非ゼロ値を返す。
    **      -   正常終了の場合は、ゼロを返す。
    **/
    static  ErrCode
    executeRecordCommand(
            const  std::string  &strArgs,
            ConsoleInterface    &objGame,
            std::ostream        &outStr,
            CallbackClass       &ciClbk);

    //----------------------------------------------------------------
    /**   コマンドを実行する。
    **
    **  @param [in]     strArgs   コマンドの引数。
    **  @param [in,out] objGame   ゲーム管理インスタンス。
    **  @param    [out] outStr    出力ストリーム。
    **  @param [in,out] ciClbk    コールバックインスタンス。
    **  @return     エラーコードを返す。
    **      -   異常終了の場合は、
    **          エラーの種類を示す非ゼロ値を返す。
    **      -   正常終了の場合は、ゼロを返す。
    **/
    static  ErrCode
    executeRotateCommand(
            const  std::string  &strArgs,
            ConsoleInterface    &objGame,
            std::ostream        &outStr,
            CallbackClass       &ciClbk);

    //----------------------------------------------------------------
    /**   コマンドを実行する。
    **
    **  @param [in]     strArgs   コマンドの引数。
    **  @param [in,out] objGame   ゲーム管理インスタンス。
    **  @param    [out] outStr    出力ストリーム。
    **  @param [in,out] ciClbk    コールバックインスタンス。
    **  @return     エラーコードを返す。
    **      -   異常終了の場合は、
    **          エラーの種類を示す非ゼロ値を返す。
    **      -   正常終了の場合は、ゼロを返す。
    **/
    static  ErrCode
    executeSeedCommand(
            const  std::string  &strArgs,
            ConsoleInterface    &objGame,
            std::ostream        &outStr,
            CallbackClass       &ciClbk);

    //----------------------------------------------------------------
    /**   コマンドを実行する。
    **
    **  @param [in]     strArgs   コマンドの引数。
    **  @param [in,out] objGame   ゲーム管理インスタンス。
    **  @param    [out] outStr    出力ストリーム。
    **  @param [in,out] ciClbk    コールバックインスタンス。
    **  @return     エラーコードを返す。
    **      -   異常終了の場合は、
    **          エラーの種類を示す非ゼロ値を返す。
    **      -   正常終了の場合は、ゼロを返す。
    **/
    static  ErrCode
    executeSfenCommand(
            const  std::string  &strArgs,
            ConsoleInterface    &objGame,
            std::ostream        &outStr,
            CallbackClass       &ciClbk);

    //----------------------------------------------------------------
    /**   コマンドを実行する。
    **
    **  @param [in]     strArgs   コマンドの引数。
    **  @param [in,out] objGame   ゲーム管理インスタンス。
    **  @param    [out] outStr    出力ストリーム。
    **  @param [in,out] ciClbk    コールバックインスタンス。
    **  @return     エラーコードを返す。
    **      -   異常終了の場合は、
    **          エラーの種類を示す非ゼロ値を返す。
    **      -   正常終了の場合は、ゼロを返す。
    **/
    static  ErrCode
    executeShowCommand(
            const  std::string  &strArgs,
            ConsoleInterface    &objGame,
            std::ostream        &outStr,
            CallbackClass       &ciClbk);

    //----------------------------------------------------------------
    /**   入力したコマンドテキストを解析する。
    **
    **  @param [in] strText   入力テキスト。
    **  @param [in] vSeps     区切りに使う文字のリスト。
    **  @param [in] nMaxSep   最大分割数。
    **  @param[out] vTokens   分割されたトークンの配列。
    **  @return     分割されたトークンの個数を返す。
    **/
    static  size_t
    parseText(
            const  std::string  &strText,
            const  char  *      vSeps,
            const  int          nMaxSep,
            TokenArray          &vTokens);

//========================================================================
//
//    Member Variables.
//
private:

    ConsoleInterface    m_ciGameCtrl;

    std::ofstream       m_outStrSwap;

//========================================================================
//
//    Other Features.
//
private:
    typedef     CommandInterpreter      This;
    CommandInterpreter  (const  This  &);
    This &  operator =  (const  This  &);
public:
    //  テストクラス。  //
    friend  class   CommandInterpreterTest;
};

}   //  End of namespace  Interface
FAIRYSHOGI_NAMESPACE_END

#endif
