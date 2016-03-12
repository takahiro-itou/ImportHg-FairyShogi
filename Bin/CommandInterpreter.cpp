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
**      An Implementation of CommandInterpreter class.
**
**      @file       Bin/CommandInterpreter.cpp
**/

#include    "CommandInterpreter.h"

#include    "FairyShogi/Common/ActionView.h"
#include    "FairyShogi/Common/HelperMacros.h"
#include    "FairyShogi/Common/ViewBuffer.h"

#include    <iostream>
#include    <limits>
#include    <cstdlib>
#include    <cstring>
#include    <fstream>
#include    <time.h>
#include    <vector>

FAIRYSHOGI_NAMESPACE_BEGIN
namespace  Interface  {

namespace  {

CONSTEXPR_VAR   const   char  *
s_tblPieceName[]    = {
    "  ",
    " P",  " L",  " N",  " S",  " G",  " B",  " R",  " K",
    "+P",  "+L",  "+N",  "+S",         "+B",  "+R",
    " p",  " l",  " n",  " s",  " g",  " b",  " r",  " k",
    "+p",  "+l",  "+n",  "+s",         "+b",  "+r"
};

CONSTEXPR_VAR   const   char  *
s_tblPieceName2[]   = {
    "W",
    "P" ,  "L",  "N",  "S",  "G",  "B",  "R",  "K",
    "+P", "+L", "+N", "+S",       "+B", "+R",
    "p" ,  "l",  "n",  "s",  "g",  "b",  "r",  "k",
    "+p", "+l", "+n", "+s",       "+b", "+r"
};

CONSTEXPR_VAR   const   char  *
s_tblSfenName[]     = {
    "1",
    "P" ,  "L",  "N",  "S",  "G",  "B",  "R",  "K",
    "+P", "+L", "+N", "+S",       "+B", "+R",
    "p" ,  "l",  "n",  "s",  "g",  "b",  "r",  "k",
    "+p", "+l", "+n", "+s",       "+b", "+r"
};

CONSTEXPR_VAR   const   char  *
s_tblHandName[]     = {
    "WALL",
    "P", "L", "N", "S", "G", "B", "R", "K",
    "p", "l", "n", "s", "g", "b", "r", "k"
};

CONSTEXPR_VAR   char
s_tblPlayerName[2]  = { 'b', 'w' };

}   //  End of (Unnamed) namespace.

//========================================================================
//
//    CommandInterpreter  class.
//

//========================================================================
//
//    Constructor(s) and Destructor.
//

//----------------------------------------------------------------
//    インスタンスを初期化する
//  （デフォルトコンストラクタ）。
//

CommandInterpreter::CommandInterpreter()
    : m_ciGameCtrl(),
      m_outStrSwap()
{
    //  ゲームをリセットする。  //
    this->m_ciGameCtrl.resetGame();

    //  緊急用スワップファイルを準備する。  //
    this->m_outStrSwap.open(".backup.swp");
    this->m_outStrSwap  <<  "#  Initial Position.\n";
    this->m_outStrSwap  <<  "position ";
    executeSfenCommand(
            "",  this->m_ciGameCtrl,  this->m_outStrSwap,  * this);
    this->m_outStrSwap  <<  "\n#  Command History"  <<  std::endl;
}

//----------------------------------------------------------------
//    インスタンスを破棄する
//  （デストラクタ）。
//

CommandInterpreter::~CommandInterpreter()
{
    this->m_outStrSwap.close();
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
//    コンソールからの入力を解釈して実行する。
//

ErrCode
CommandInterpreter::interpretConsoleInput(
        const  std::string  &strLine,
        std::ostream        &outStr)
{
    ConsoleInterface    &  objGame  =  (this->m_ciGameCtrl);
    LpFnExecuteCommand  pfnExecCmd  =  (nullptr);

    std::vector<std::string>    vTokens;

    vTokens.clear();
    vTokens.reserve(2);

    parseText(
            strLine,  " \t",  1,  vTokens);
    if ( vTokens.empty() ) {
        return ( ERR_INVALID_COMMAND );
    }

    if ( vTokens[0] == "go" ) {
        vTokens.push_back("");
        pfnExecCmd  =  &(executeGoCommand);
    } else if ( vTokens[0] == "dice" ) {
        vTokens.push_back("get");
        pfnExecCmd  =  &(executeDiceCommand);
    } else if ( vTokens[0] == "position" ) {
        vTokens.push_back("");
        pfnExecCmd  =  &(executePositionCommand);
    } else if ( vTokens[0] == "fwd" ) {
        vTokens.push_back("");
        pfnExecCmd  =  &(executeForwardCommand);
    } else if ( vTokens[0] == "sfen" ) {
        vTokens.push_back("");
        pfnExecCmd  =  &(executeSfenCommand);
    } else if ( vTokens[0] == "show" ) {
        vTokens.push_back("");
        pfnExecCmd  =  &(executeShowCommand);
    } else if ( vTokens[0] == "list" ) {
        vTokens.push_back("cur");
        pfnExecCmd  =  &(executeListCommand);
    } else if ( vTokens[0] == "player") {
        vTokens.push_back("next");
        pfnExecCmd  =  &(executePlayerCommand);
    } else if ( vTokens[0] == "flip" ) {
        vTokens.push_back("change");
        pfnExecCmd  =  &(executeFlipCommand);
    } else if ( vTokens[0] == "seed" ) {
        vTokens.push_back("");
        pfnExecCmd  =  &(executeSeedCommand);
    } else if ( (vTokens[0] == "bwd") || (vTokens[0] == "back") ) {
        vTokens.push_back("");
        pfnExecCmd  =  &(executeBackwardCommand);
    } else if ( (vTokens[0] == "record") )  {
        vTokens.push_back("");
        pfnExecCmd  =  &(executeRecordCommand);
    }

    if ( pfnExecCmd == (nullptr) ) {
        std::cerr   <<  "Invalid Command."  << std::endl;
        return ( ERR_INVALID_COMMAND );
    }

    ErrCode     retErr  =  ERR_INVALID_COMMAND;
    retErr  =  (* pfnExecCmd)(vTokens[1],  objGame,  outStr,  *this);

    return ( retErr );
}

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

//----------------------------------------------------------------
//    コマンドを実行する。
//

ErrCode
CommandInterpreter::executeBackwardCommand(
        const  std::string  &strArgs,
        ConsoleInterface    &objGame,
        std::ostream        &outStr,
        CallbackClass       &ciClbk)
{
    const  ErrCode  retErr  =  objGame.playBackward();
    executePlayerCommand("next",  objGame,  outStr,  ciClbk);
    objGame.setConstraint(6);
    return ( retErr );
}

//----------------------------------------------------------------
//    コマンドを実行する。
//

ErrCode
CommandInterpreter::executeDiceCommand(
        const  std::string  &strArgs,
        ConsoleInterface    &objGame,
        std::ostream        &outStr,
        CallbackClass       &ciClbk)
{
    std::vector<FieldIndex>     bbFrom;

    const  Game::BoardState  &bsCur = objGame.getBoardState();
    const  size_t
        numChk  = bsCur.isCheckState(objGame.getCurrentPlayer(), bbFrom);
    if ( numChk == 1 ) {
        std::cerr   <<  "* CHECK!"  <<  std::endl;
        objGame.setConstraint(6);
        return ( ERR_SUCCESS );
    } else if ( numChk >= 2 ) {
        std::cerr   <<  "** DOUBLE CHECK!"  <<  std::endl;
        objGame.setConstraint(6);
        return ( ERR_SUCCESS );
    }

    if ( strArgs[0] == 'g' ) {
        std::cout   <<  "Current Constraint. Dice = "
                    <<  objGame.getConstraint()
                    <<  std::endl;
        return ( ERR_SUCCESS );
    }

    if ( strArgs[0] == 'r' ) {
        const  int  rn  =  ((std::rand() >> 8) % 6) + 1;
        std::cout   <<  rn  <<  std::endl;
        objGame.setConstraint(rn);
        return ( ERR_SUCCESS );
    }

    const  int  dr  =  strArgs[0] - '0';
    if ( (dr < 0) || (6 < dr) ) {
        outStr  <<  "# ERROR : Invalid Arguments."  <<  std::endl;
        return ( ERR_INVALID_COMMAND );
    }
    objGame.setConstraint(dr);

    return ( ERR_SUCCESS );
}

//----------------------------------------------------------------
//    コマンドを実行する。
//

ErrCode
CommandInterpreter::executeFlipCommand(
        const  std::string  &strArgs,
        ConsoleInterface    &objGame,
        std::ostream        &outStr,
        CallbackClass       &ciClbk)
{
    int     flgNow  = objGame.getShowFlag();

    if ( strArgs[0] == 'c' ) {
        //  Change.
        flgNow  ^=  GameController::SCF_FLIP_COLUMNS;
    } else if ( strArgs[0] == 'n' ) {
        //  Normal.
        flgNow  &=  (~ GameController::SCF_FLIP_COLUMNS);
    } else if ( strArgs[0] == 'r' ) {
        //  Reverse.
        flgNow  |=  GameController::SCF_FLIP_COLUMNS;
    } else {
        return ( ERR_INVALID_COMMAND );
    }

    return ( objGame.setShowFlag(flgNow) );
}

//----------------------------------------------------------------
//    コマンドを実行する。
//

ErrCode
CommandInterpreter::executeForwardCommand(
        const  std::string  &strArgs,
        ConsoleInterface    &objGame,
        std::ostream        &outStr,
        CallbackClass       &ciClbk)
{
    ActionView  actView;

    if ( objGame.parseActionText(strArgs, &actView) != ERR_SUCCESS )
    {
        outStr  <<  "# ERROR : Invalid Arguments."  <<  std::endl;
        return ( ERR_INVALID_COMMAND );
    }

    std::cerr   <<  "# DEBUG (USI) : ";
    objGame.writeActionViewSfen(actView, BOOL_TRUE, std::cerr)
            <<  std::endl;
    std::cerr   <<  "# DEBUG (CSA) : ";
    objGame.writeActionViewCsa(actView, std::cerr)  <<  std::endl;

    ActionList      actList;
    objGame.makeLegalActionList(0, -1, actList);
    const  ActIter  itrEnd  = actList.end();

    ActionFlag      flgLeg  =  Common::ALF_ILLEGAL_MOVE;
    for ( ActIter itr = actList.begin(); itr != itrEnd; ++ itr ) {
        if ( GameController::isEquals(* itr, actView) ) {
            flgLeg  = (itr->fLegals);
            break;
        }
    }

    if ( flgLeg != Common::ALF_LEGAL_ACTION ) {
        std::cerr   <<  "Not Legal Move."   <<  std::endl;
        if ( strArgs[strArgs.length() - 1] != '!' ) {
            return ( ERR_ILLEGAL_ACTION );
        }
    }

    ciClbk.m_outStrSwap  <<  "dice "
                        <<  objGame.getConstraint()
                        <<  "\nfwd ";
    objGame.writeActionViewSfen(
            actView,  BOOL_TRUE,  ciClbk.m_outStrSwap);
    if ( flgLeg != Common::ALF_LEGAL_ACTION ) {
        ciClbk.m_outStrSwap  <<  '!';
    }
    ciClbk.m_outStrSwap  <<  std::endl;

    objGame.playForward(actView);

    executePlayerCommand("next",  objGame,  outStr,  ciClbk);
    objGame.setConstraint(6);

    return ( ERR_SUCCESS );
}

//----------------------------------------------------------------
//    コマンドを実行する。
//

ErrCode
CommandInterpreter::executeGoCommand(
        const  std::string  &strArgs,
        ConsoleInterface    &objGame,
        std::ostream        &outStr,
        CallbackClass       &ciClbk)
{
    UTL_HELP_UNUSED_ARGUMENT(strArgs);
    UTL_HELP_UNUSED_ARGUMENT(ciClbk);

    ActionView  actData;

    if ( objGame.computeBestAction(actData) != ERR_SUCCESS ) {
        std::cerr   <<  "No Legal Actions"  <<  std::endl;
        return ( ERR_SUCCESS );
    }

    outStr      <<  "bestmove ";
    objGame.writeActionViewSfen(actData,  BOOL_FALSE,  outStr)
            <<  std::endl;
    std::cerr   <<  "#  COM (USI) : ";
    objGame.writeActionViewSfen(actData,  BOOL_TRUE,  std::cerr)
            <<  std::endl;
    std::cerr   <<  "#  COM (CSA) : ";
    objGame.writeActionViewCsa(actData, std::cerr)  <<  std::endl;

    return ( ERR_SUCCESS );
}

//----------------------------------------------------------------
//    コマンドを実行する。
//

ErrCode
CommandInterpreter::executeListCommand(
        const  std::string  &strArgs,
        ConsoleInterface    &objGame,
        std::ostream        &outStr,
        CallbackClass       &ciClbk)
{
    int     dc  =  objGame.getConstraint();
    if ( strArgs[0] == 'a' ) {
        dc  =  6;
    } else if ( ('0' <= strArgs[0]) && (strArgs[0] <= '6') ) {
        dc  =  strArgs[0] - '0';
    }
    ActionFlag  fLegal  =  Common::ALF_LEGAL_ACTION;
    if ( strArgs[ strArgs.length() - 1 ] == '!' ) {
        fLegal  =  Common::ALF_ALL_FLAGS;
    }
    std::cerr   <<  "List For Dice = "  <<  dc  <<  std::endl;

    ActionList      vActs;
    objGame.makeLegalActionList(fLegal, dc, vActs);
    const  ActIter  itrEnd  =  vActs.end();

    int     cntDisp = 0;
    int     cntLeg  = 0;
    int     cntBad  = 0;
    int     cntChk  = 0;
    int     cntDFs  = 0;

    for ( ActIter itr = vActs.begin(); itr != itrEnd; ++ itr )
    {
        objGame.writeActionViewSfen( (* itr), BOOL_TRUE, outStr );
        if ( (itr->fLegals) != Common::ALF_LEGAL_ACTION ) {
            ++  cntBad;
            outStr  <<  '!';
        } else {
            ++  cntLeg;
        }

        if ( (itr->fLegals) & Common::ALF_IGNORE_CHECK ) { ++  cntChk; }
        if ( (itr->fLegals) & Common::ALF_DOUBLE_PAWNS ) { ++  cntDFs; }

        outStr  <<  ", ";
        ++  cntDisp;
        if ( cntDisp >= 8 ) {
            outStr  <<  std::endl;
            cntDisp -=  8;
        }
    }

    outStr  <<  std::endl   <<  (vActs.size())
            <<  "  Actions."  <<  std::endl;
    outStr  <<  cntLeg  <<  "  Legals,  "
            <<  cntBad  <<  "  Illegals,  "
            <<  cntChk  <<  "  IC/SCs,  "
            <<  cntDFs  <<  "  DFs"
            <<  std::endl;
    return ( ERR_SUCCESS );
}

//----------------------------------------------------------------
//    コマンドを実行する。
//

ErrCode
CommandInterpreter::executePlayerCommand(
        const  std::string  &strArgs,
        ConsoleInterface    &objGame,
        std::ostream        &outStr,
        CallbackClass       &ciClbk)
{
    if ( strArgs == "next" ) {
        const  PlayerIndex  pi  =  objGame.getCurrentPlayer();
        objGame.setCurrentPlayer(pi ^ 1);
        std::cerr   <<  s_tblPlayerName[ objGame.getCurrentPlayer() ]
                    <<  std::endl;
        return ( ERR_SUCCESS );
    }
    if ( strArgs == "get" ) {
        std::cout   <<  s_tblPlayerName[ objGame.getCurrentPlayer() ]
                    <<  std::endl;
        return ( ERR_SUCCESS );
    }

    for ( PlayerIndex i = 0; i < 2; ++ i ) {
        if ( (strArgs[0] == '0' + i) || (strArgs[0] == s_tblPlayerName[i]) )
        {
            objGame.setCurrentPlayer(i);
            return ( ERR_SUCCESS );
        }
    }

    outStr  <<  "# ERROR : Invalid Arguments."  <<  std::endl;
    return ( ERR_INVALID_COMMAND );
}

//----------------------------------------------------------------
//    コマンドを実行する。
//

ErrCode
CommandInterpreter::executePositionCommand(
        const  std::string  &strArgs,
        ConsoleInterface    &objGame,
        std::ostream        &outStr,
        CallbackClass       &ciClbk)
{
    return ( ERR_INVALID_COMMAND );
}

//----------------------------------------------------------------
//    コマンドを実行する。
//

ErrCode
CommandInterpreter::executeRecordCommand(
        const  std::string  &strArgs,
        ConsoleInterface    &objGame,
        std::ostream        &outStr,
        CallbackClass       &ciClbk)
{
    ActionList  actList;
    ErrCode     retErr  =  ERR_SUCCESS;

    retErr  =  objGame.writeActionList(actList);
    if ( retErr != ERR_SUCCESS ) {
        return ( retErr );
    }

    std::ostream  *    pOutStr  =  &(std::cout);
    std::ofstream      ofsRec;
    if ( !(strArgs.empty()) ) {
        ofsRec.open( strArgs.c_str() );
        if ( !ofsRec ) {
            std::cerr   <<  "File Open Failure. ["  <<  strArgs
                        <<  "]"     <<  std::endl;
        } else {
            pOutStr =  &(ofsRec);
        }
    }

    const  ActIter  itrEnd  =  actList.end();
    for ( ActIter itr = actList.begin(); itr != itrEnd; ++ itr )
    {
        objGame.writeActionViewSfen( * itr, BOOL_TRUE,  * pOutStr )
                <<  std::endl;
    }

    return ( ERR_SUCCESS );
}

//----------------------------------------------------------------
//    コマンドを実行する。
//

ErrCode
CommandInterpreter::executeRotateCommand(
        const  std::string  &strArgs,
        ConsoleInterface    &objGame,
        std::ostream        &outStr,
        CallbackClass       &ciClbk)
{
    if ( strArgs[0] == 'c' ) {
        //  Change Rotate.

    } else if ( strArgs[0] == 'n' ) {
        //  Normal.
    } else if ( strArgs[0] == 'r' ) {
        //  Reverse.
    }

    return ( ERR_INVALID_COMMAND );
}

//----------------------------------------------------------------
//    コマンドを実行する。
//

ErrCode
CommandInterpreter::executeSeedCommand(
        const  std::string  &strArgs,
        ConsoleInterface    &objGame,
        std::ostream        &outStr,
        CallbackClass       &ciClbk)
{
    UTL_HELP_UNUSED_ARGUMENT(strArgs);
    UTL_HELP_UNUSED_ARGUMENT(objGame);
    UTL_HELP_UNUSED_ARGUMENT(outStr);
    UTL_HELP_UNUSED_ARGUMENT(ciClbk);

    std::srand( time(nullptr) );

    return ( ERR_SUCCESS );
}

//----------------------------------------------------------------
//    コマンドを実行する。
//

ErrCode
CommandInterpreter::executeSfenCommand(
        const  std::string  &strArgs,
        ConsoleInterface    &objGame,
        std::ostream        &outStr,
        CallbackClass       &ciClbk)
{
    Common::ViewBuffer  vb;
    ::memset( &vb, 0, sizeof(vb) );
    objGame.writeToViewBuffer(vb);

    //  盤面を表示する。    //
    for ( int y = 0; y < 5; ++ y ) {
        if ( y > 0 ) {
            outStr  <<  "/";
        }
        for ( int x = 0; x < 5; ++ x ) {
            const  PieceIndex   dp  = vb.fpBoard[y][x];
            outStr  <<  s_tblSfenName[dp];
        }

    }

    //  手番を表示する。    //
//    outStr  <<  ;
    outStr  <<  " b ";

    //  持ち駒を表示する。  //
    int     flg = 0;
    for ( PlayerIndex i = 0; i < vb.numPlayers; ++ i ) {
        const  PieceIndex  numHand  =  vb.numHandTypes[i];
        for ( PieceIndex c = 0; c < numHand;  ++ c )
        {
            const  Common::EHandPiece   piHand  =  vb.hpIndex[i][c];
            const  THandCount           hcHand  =  vb.hpCount[i][c];
            if ( hcHand <= 0 ) { continue; }
            flg = 1;
            if ( hcHand > 1 ) {
                outStr  <<  (hcHand);
            }
            outStr  <<  s_tblHandName[piHand];
        }
    }
    if ( flg == 0 ) {
        outStr  <<  "-";
    }

    outStr  <<  " 1\n";

    return ( ERR_SUCCESS );
}

//----------------------------------------------------------------
//    コマンドを実行する。
//

ErrCode
CommandInterpreter::executeShowCommand(
        const  std::string  &strArgs,
        ConsoleInterface    &objGame,
        std::ostream        &outStr,
        CallbackClass       &ciClbk)
{
    CONSTEXPR_VAR   const  char  *  s_tblHandOwnerNames[2]  =  {
        "\nBLACK:",
        "\nWHITE:"
    };

    const   GameController::ShowCoordFlags
        flgShow = objGame.getShowFlag();

    Common::ViewBuffer  vb;
    ::memset( &vb, 0, sizeof(vb) );
    objGame.writeToViewBuffer(vb);

    //  盤面を表示する。    //
    if ( (flgShow == GameController::SCF_FLIP_COLUMNS)
            || (flgShow == GameController::SCF_ROTATE_BOARD) )
    {
        outStr  <<  "| 1| 2| 3| 4| 5|\n";
    } else {
        outStr  <<  "| 5| 4| 3| 2| 1|\n";
    }

    outStr  <<  "----------------\n";
    for ( int y = 0; y < 5; ++ y ) {
        for ( int x = 0; x < 5; ++ x ) {
            const  PieceIndex   dp  = vb.fpBoard[y][x];
            outStr  <<  "|"  <<  s_tblPieceName[dp];
        }
        if ( (flgShow) & GameController::SCF_ROTATE_BOARD ) {
            outStr  <<  "|"  <<  (5-y)  <<  "\n";
        } else {
            outStr  <<  "|"  <<  (y+1)  <<  "\n";
        }
        outStr  <<  "----------------\n";
    }

    //  持ち駒を表示する。  //
    for ( PlayerIndex i = 0; i < vb.numPlayers; ++ i ) {
        outStr  <<  s_tblHandOwnerNames[i];
        const  PieceIndex  numHand  =  vb.numHandTypes[i];
        for ( PieceIndex c = 0; c < numHand;  ++ c )
        {
            const  Common::EHandPiece   piHand  =  vb.hpIndex[i][c];
            const  THandCount           hcHand  =  vb.hpCount[i][c];
            if ( hcHand <= 0 ) { continue; }
            outStr  <<  s_tblHandName[piHand]
                    <<  hcHand
                    <<  ", ";
        }
    }
    outStr  <<  std::endl;

    return ( ERR_SUCCESS );
}

//----------------------------------------------------------------
//    入力したコマンドテキストを解析する。
//

size_t
CommandInterpreter::parseText(
        const  std::string  &strText,
        const  char  *      vSeps,
        const  int          nMaxSep,
        TokenArray          &vTokens)
{
    const  size_t  lenText  = strText.length();
    std::vector<char>   chBuf(lenText + 1);
    char  *     ptrBuf  = &(chBuf[0]);

    ::memcpy( ptrBuf, strText.c_str(), lenText );
    chBuf[lenText]  = '\0';

    char  *     ptrTkn  = (nullptr);
    ////char  *     ptrSave = (nullptr);

    ////ptrTkn  = strtok_r(ptrBuf,  vSeps,  &ptrSave);
    ptrTkn  = strtok(ptrBuf,  vSeps);
    if ( ptrTkn == (nullptr) ) {
        return ( 0 );
    }
    vTokens.push_back(ptrTkn);

    for ( int i = 1; i < nMaxSep; ++ i ) {
        ////ptrTkn  = strtok_r(nullptr,  vSeps,  &ptrSave);
        ptrTkn  = strtok(nullptr,  vSeps);
        if ( ptrTkn == (nullptr) ) {
            break;
        }
        vTokens.push_back(ptrTkn);
    }

    ////ptrTkn  = strtok_r(nullptr,  "\n",  &ptrSave);
    ptrTkn  = strtok(nullptr,  "\n");
    if ( ptrTkn != (nullptr) ) {
        vTokens.push_back(ptrTkn);
    }

    return ( vTokens.size() );
}

}   //  End of namespace  Interface
FAIRYSHOGI_NAMESPACE_END
