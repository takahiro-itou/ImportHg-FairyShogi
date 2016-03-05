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
**      アプリケーション本体。
**
**      @file       Bin/FairyShogi.cpp
**/

#include    "CommandInterpreter.h"

#include    "FairyShogi/Common/FairyShogiTypes.h"
#include    "FairyShogi/Common/ActionView.h"
#include    "FairyShogi/Common/ViewBuffer.h"
#include    "FairyShogi/Interface/ConsoleInterface.h"

#include    <iostream>
#include    <limits>
#include    <cstdlib>
#include    <cstring>
#include    <fstream>
#include    <time.h>
#include    <vector>

using   namespace   FAIRYSHOGI_NAMESPACE;

Interface::CommandInterpreter   g_ciGameCtrl;

typedef     Interface::ConsoleInterface     GameController;

typedef     GameController::ActionViewList  ActionList;
typedef     ActionList::const_iterator      ActIter;

typedef     GameController::ActionView      ActionView;
typedef     GameController::ActionData      ActionData;

GameController      g_gcGameCtrl;

std::ofstream       g_outStrKifu;

CONSTEXPR_VAR   const   char  *
g_tblPieceName[]    = {
    "  ",
    " P",  " S",  " G",  " B",  " R",  " K",
    "+P",  "+S",  "+B",  "+R",
    " p",  " s",  " g",  " b",  " r",  " k",
    "+p",  "+s",  "+b",  "+r"
};

CONSTEXPR_VAR   const   char  *
g_tblPieceName2[]   = {
    "W",
    "P",  "S",  "G",  "B",  "R",  "K",
    "+P", "+S", "+B", "+R",
    "p",  "s",  "g",  "b",  "r",  "k",
    "+p", "+s", "+b", "+r"
};

CONSTEXPR_VAR   const   char  *
g_tblSfenName[]     = {
    "1",
    "P",   "S",   "G",   "B",   "R",   "K",
    "+P",  "+S",  "+B",  "+R",
    "p",   "s",   "g",   "b",   "r",   "k",
    "+p",  "+s",  "+b",  "+r"
};

CONSTEXPR_VAR   const   char  *
g_tblHandName[]     = {
    "WALL",
    "P", "S", "G", "B", "R", "K",
    "p", "s", "g", "b", "r", "k"
};

size_t
parseText(
        const   std::string         &strText,
        const   char  *             vSeps,
        const   int                 nMaxSep,
        std::vector< std::string >  &vTokens)
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

ErrCode
setPosition(
        const  std::string  &strData,
        GameController      &objGame)
{
    std::vector<std::string>    vTokens;

    vTokens.clear();
    vTokens.reserve(4);

    parseText(
            strData, " \t", 3, // std::numeric_limits<int>::max(),
            vTokens);
    if ( vTokens[0] == "startpos" ) {
        objGame.resetGame();
        return ( ERR_SUCCESS );
    }

    std::cerr   <<  "Invalid Position Format["  <<  strData  <<  "]"
                <<  std::endl;
    return ( ERR_SUCCESS );
}

ErrCode
displaySfen(
        const  GameController  &objGame,
        std::ostream           &outStr)
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
            const  int          pi  = (y * 5) + x;
            const  PieceIndex   dp  = vb.piBoard[pi];
            outStr  <<  g_tblSfenName[dp];
        }

    }

    /**     @todo   暫定処理。後で直す。    **/
    outStr  <<  " b ";

    //  持ち駒を表示する。  //
    int     flg = 0;
    for ( int c = 1; c < 12; ++ c ) {
        const  THandCount   numHand = vb.nHands[c];
        if ( numHand <= 0 ) { continue; }
        flg = 1;
        if ( numHand > 1 ) {
            outStr  <<  (numHand);
        }
        outStr  <<  g_tblHandName[c];
    }
    if ( flg == 0 ) {
        outStr  <<  "-";
    }

    outStr  <<  " 1\n";

    return ( ERR_SUCCESS );
}

ErrCode
displayBoard(
        const  GameController  &objGame,
        std::ostream           &outStr)
{
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
            const  int          pi  = (y * 5) + x;
            const  PieceIndex   dp  = vb.piBoard[pi];
            outStr  <<  "|"  <<  g_tblPieceName[dp];
        }
        if ( (flgShow) & GameController::SCF_ROTATE_BOARD ) {
            outStr  <<  "|"  <<  (5-y)  <<  "\n";
        } else {
            outStr  <<  "|"  <<  (y+1)  <<  "\n";
        }
        outStr  <<  "----------------\n";
    }

    //  持ち駒を表示する。  //
    for ( int c = 1; c < 12; ++ c ) {
        if ( c == 1 ) {
            outStr  <<  "\nBLACK:";
        } else if ( c == 7 ) {
            outStr  <<  "\nWHITE:";
        }

        const  THandCount   numHand = vb.nHands[c];
        if ( numHand <= 0 ) { continue; }
        outStr  <<  g_tblHandName[c]
                <<  numHand
                <<  ", ";
    }

    outStr  <<  std::endl;

    return ( ERR_SUCCESS );
}

std::ostream  &
displayActionData(
        const  ActionData   &actData,
        const  int          flgName,
        std::ostream        &outStr)
{
    if ( actData.putHand == Game::BoardState::HAND_EMPTY_PIECE ) {
        outStr  <<  (actData.xOldCol + 1)   <<  (actData.yOldRow + 1)
                <<  (actData.xNewCol + 1)   <<  (actData.yNewRow + 1);
        if ( flgName ) {
            outStr  <<  (g_tblPieceName2[actData.fpMoved]);
        }
        if ( (actData.fpAfter) != (actData.fpMoved) ) {
            outStr  <<  '+';
        } else {
            outStr  <<  ' ';
        }
    } else {
        outStr  <<  (g_tblHandName[actData.putHand])
                <<  '*'
                <<  (actData.xNewCol + 1)   <<  (actData.yNewRow + 1)
                <<  ' ';
    }

    return ( outStr );
}

std::ostream  &
displayActionView(
        const  ActionView   &actView,
        const  int          flgName,
        std::ostream        &outStr)
{
    if ( actView.hpiDrop == Game::BoardState::HAND_EMPTY_PIECE ) {
        outStr  <<  (actView.xDispOldCol)   <<  (actView.yDispOldRow)
                <<  (actView.xDispNewCol)   <<  (actView.yDispNewRow);
        if ( (actView.fpAfter) != (actView.fpMoved) ) {
            outStr  <<  '+';
        } else {
            outStr  <<  ' ';
        }
    } else {
        outStr  <<  (g_tblHandName[actView.hpiDrop])
                <<  '*'
                <<  (actView.xDispNewCol)   <<  (actView.yDispNewRow)
                <<  "  ";
    }
    if ( flgName ) {
        outStr  <<  (g_tblPieceName[actView.fpMoved])  <<  ' ';
    }

    return ( outStr );
}

ErrCode
executePlayerCommand(
        const  std::string  &strArgs,
        GameController      &objGame)
{
    CONSTEXPR_VAR   char    chName[2] = { 'b', 'w' };

    if ( strArgs == "next" ) {
        const  PlayerIndex  pi  =  objGame.getCurrentPlayer();
        objGame.setCurrentPlayer(pi ^ 1);
        std::cerr   <<  chName[objGame.getCurrentPlayer()]  <<  std::endl;
        return ( ERR_SUCCESS );
    }
    if ( strArgs == "get" ) {
        std::cout   <<  chName[objGame.getCurrentPlayer()]  <<  std::endl;
        return ( ERR_SUCCESS );
    }

    if ( (strArgs[0] == '0') || (strArgs[0] == 'b') ) {
        objGame.setCurrentPlayer(0);
        return ( ERR_SUCCESS );
    }
    if ( (strArgs[0] == '1') || (strArgs[0] == 'w') ) {
        objGame.setCurrentPlayer(1);
        return ( ERR_SUCCESS );
    }

    std::cerr   <<  "Invalid Arguments."    <<  std::endl;
    return ( ERR_SUCCESS );
}

ErrCode
executeBackwardCommand(
        const  std::string  &strArgs,
        GameController      &objGame)
{
    return ( objGame.playBackward() );
}

ErrCode
executeForwardCommand(
        const  std::string  &strArgs,
        GameController      &objGame)
{
    ActionView  actView;

    if ( objGame.parseActionText(strArgs, &actView) != ERR_SUCCESS )
    {
        std::cerr   <<  "Invalid Arguments."    <<  std::endl;
        return ( ERR_INVALID_COMMAND );
    }

    displayActionView(actView, 1, std::cerr)    <<  std::endl;

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

    g_outStrKifu    <<  "dice "
                    <<  objGame.getConstraint()
                    <<  "\nfwd ";
    displayActionView(actView,  1,  g_outStrKifu);
    if ( flgLeg != Common::ALF_LEGAL_ACTION ) {
        g_outStrKifu    <<  '!';
    }
    g_outStrKifu    <<  std::endl;

    objGame.playForward(actView);

    executePlayerCommand("next", objGame);
    objGame.setConstraint(6);

    return ( ERR_SUCCESS );
}

ErrCode
executeDiceCommand(
        const  std::string  &strArgs,
        GameController      &objGame)
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
        std::cerr   <<  "Invalid Arguments."    <<  std::endl;
        return ( ERR_SUCCESS );
    }
    objGame.setConstraint(dr);

    return ( ERR_SUCCESS );
}

ErrCode
executeListCommand(
        const  std::string     &strArgs,
        const  GameController  &objGame,
        std::ostream           &outStr)
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
        displayActionView( (* itr), 1, outStr );
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

ErrCode
executeGoCommand(
        GameController  &objGame)
{
    ActionView  actData;

    if ( objGame.startThinking(actData) != ERR_SUCCESS ) {
        std::cerr   <<  "No Legal Actions"  <<  std::endl;
        return ( ERR_SUCCESS );
    }

    std::cout   <<  "bestmove ";
    displayActionView(actData,  0,  std::cout)  <<  std::endl;
    std::cerr   <<  "#  COM : ";
    displayActionView(actData,  1,  std::cerr)  <<  std::endl;
    return ( ERR_SUCCESS );
}

ErrCode
executeFlipCommand(
        const  std::string  &strArgs,
        GameController      &objGame)

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

ErrCode
executeRecordCommand(
        const  std::string      &strArgs,
        const  GameController   &objGame)
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
        displayActionView( * itr, 1,  * pOutStr )   <<  std::endl;
    }

    return ( ERR_SUCCESS );
}

ErrCode
executeRotateCommand(
        const  std::string  &strArgs,
        GameController      &objGame)

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

ErrCode
parseConsoleInput(
        const  std::string  &strLine,
        GameController      &objGame)
{
    std::vector<std::string>    vTokens;

    vTokens.clear();
    vTokens.reserve(2);

    parseText(
            strLine,  " \t",  1,  vTokens);
    if ( vTokens.empty() ) {
        return ( ERR_INVALID_COMMAND );
    }

    if ( vTokens[0] == "go" ) {
        return ( executeGoCommand(objGame) );
    } else if ( vTokens[0] == "dice" ) {
        vTokens.push_back("get");
        return ( executeDiceCommand(vTokens[1], objGame) );
    } else if ( vTokens[0] == "position" ) {
        if ( vTokens.size() == 1 ) {
            std::cerr   <<  "Require Arguments."    <<  std::endl;
            return ( ERR_SUCCESS );
        }
        return  ( setPosition(vTokens[1], objGame) );
    } else if ( vTokens[0] == "fwd" ) {
        vTokens.push_back("");
        return ( executeForwardCommand(vTokens[1], objGame) );

    } else if ( vTokens[0] == "sfen" ) {
        return ( displaySfen(objGame, std::cout) );
    } else if ( vTokens[0] == "show" ) {
        return ( displayBoard(objGame, std::cout) );
    } else if ( vTokens[0] == "list" ) {
        vTokens.push_back("cur");
        return ( executeListCommand(vTokens[1], objGame, std::cout) );
    } else if ( vTokens[0] == "player") {
        vTokens.push_back("next");
        return ( executePlayerCommand(vTokens[1], objGame) );
    } else if ( vTokens[0] == "flip" ) {
        vTokens.push_back("change");
        return ( executeFlipCommand(vTokens[1], objGame) );
    } else if ( vTokens[0] == "srand" ) {
        std::srand( ::time(NULL) );
    } else if ( (vTokens[0] == "bwd") || (vTokens[0] == "back") ) {
        vTokens.push_back("");
        return ( executeBackwardCommand(vTokens[1], objGame) );
    } else if ( (vTokens[0] == "record") )  {
        vTokens.push_back("");
        return ( executeRecordCommand(vTokens[1], objGame) );
    }

    std::cerr   <<  "Invalid Command."  << std::endl;
    return ( ERR_SUCCESS );
}

int  main(int argc, char * argv[])
{
    std::cerr   <<  "Fairy Shogi Version 0.0"
                <<  std::endl;

    std::string     strBuf;
    ErrCode         retErr;

    std::istream   & inStr  = (std::cin);

    // g_gcGameCtrl.resetGame();

    // g_outStrKifu.open(".backup.kifu.swp");
    // displaySfen(g_gcGameCtrl,  g_outStrKifu);

    for ( ;; ) {
        if ( ! inStr ) {
            break;
        }
        std::cerr   <<  ">";
        std::getline(inStr, strBuf);

        if ( strBuf.empty() ) {
            continue;
        }
        if ( strBuf[0] == '#' ) {
            //  コメント行は無視する。  //
            continue;
        }
        if ( strBuf == "quit" ) {
            //  終了コマンドを処理。    //
            break;
        }

        retErr  =  g_ciGameCtrl.interpretConsoleInput(strBuf,  std::cout);
        if ( retErr != ERR_SUCCESS ) {
            std::cerr   <<  "\nCommand Failed"  <<  std::endl;
        }
        // GameStateFlags  fgStat  =  g_gcGameCtrl.testGameStateResult();
        // std::cerr   <<  "# DEBUG : Game Status = "  <<  fgStat
        //         <<  std::endl;
        // if ( fgStat == Common::GAME_IS_OVER ) {
        //     std::cerr   <<  "# DEBUG : Game Result = "
        //                 <<  g_gcGameCtrl.getGameResult()
        //                 <<  std::endl;
        // }

    }

//    g_outStrKifu.close();

    return ( 0 );
}
