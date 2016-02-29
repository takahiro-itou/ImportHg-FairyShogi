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

#include    "FairyShogi/Common/FairyShogiTypes.h"
#include    "FairyShogi/Common/ActionView.h"
#include    "FairyShogi/Common/ViewBuffer.h"
#include    "FairyShogi/Interface/ConsoleInterface.h"

#include    <iostream>
#include    <limits>
#include    <cstdlib>
#include    <cstring>
#include    <time.h>
#include    <vector>

using   namespace   FAIRYSHOGI_NAMESPACE;

typedef     Interface::ConsoleInterface     GameController;

typedef     GameController::ActionViewList  ActionList;
typedef     ActionList::const_iterator      ActIter;

typedef     GameController::ActionView      ActionView;
typedef     GameController::ActionData      ActionData;

GameController      g_gcGameCtrl;

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

CONSTEXPR_VAR   const   int
g_tblPromotion[]    = {
    Game::BoardState::FIELD_EMPTY_SQUARE,

    Game::BoardState::FIELD_BLACK_PR_PAWN,
    Game::BoardState::FIELD_BLACK_PR_SILVER,
    Game::BoardState::FIELD_BLACK_GOLD,
    Game::BoardState::FIELD_BLACK_HORSE,
    Game::BoardState::FIELD_BLACK_DRAGON,
    Game::BoardState::FIELD_BLACK_KING,
    Game::BoardState::FIELD_BLACK_PR_PAWN,
    Game::BoardState::FIELD_BLACK_PR_SILVER,
    Game::BoardState::FIELD_BLACK_HORSE,
    Game::BoardState::FIELD_BLACK_DRAGON,

    Game::BoardState::FIELD_WHITE_PR_PAWN,
    Game::BoardState::FIELD_WHITE_PR_SILVER,
    Game::BoardState::FIELD_WHITE_GOLD,
    Game::BoardState::FIELD_WHITE_HORSE,
    Game::BoardState::FIELD_WHITE_DRAGON,
    Game::BoardState::FIELD_WHITE_KING,
    Game::BoardState::FIELD_WHITE_PR_PAWN,
    Game::BoardState::FIELD_WHITE_PR_SILVER,
    Game::BoardState::FIELD_WHITE_HORSE,
    Game::BoardState::FIELD_WHITE_DRAGON,
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
    if ( actView.putHand == Game::BoardState::HAND_EMPTY_PIECE ) {
        outStr  <<  (actView.xOldCol)   <<  (actView.yOldRow)
                <<  (actView.xNewCol)   <<  (actView.yNewRow);
        if ( flgName ) {
            outStr  <<  (g_tblPieceName2[actView.fpMoved]);
        }
        if ( (actView.fpAfter) != (actView.fpMoved) ) {
            outStr  <<  '+';
        } else {
            outStr  <<  ' ';
        }
    } else {
        outStr  <<  (g_tblHandName[actView.putHand])
                <<  '*'
                <<  (actView.xNewCol)   <<  (actView.yNewRow)
                <<  ' ';
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
executeForwardCommand(
        const  std::string  &strArgs,
        GameController      &objGame)
{
    ActionView  actView;

    if ( objGame.parseActionText(strArgs, &actView) != ERR_SUCCESS )
    {
        std::cerr   <<  "Invalid Arguments."    <<  std::endl;
        return ( ERR_SUCCESS );
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
    }

    std::cerr   <<  "Invalid Command."  << std::endl;
    return ( ERR_SUCCESS );
}

int  main(int argc, char * argv[])
{
    std::cerr   <<  "Fairy Shogi Version 0.0"
                <<  std::endl;

    std::string     strBuf;
    std::istream   & inStr  = (std::cin);

    g_gcGameCtrl.resetGame();

    for ( ;; ) {
        if ( ! inStr ) {
            break;
        }
        std::cerr   <<  ">";
        std::getline(inStr, strBuf);
        if ( strBuf.empty() ) {
            continue;
        }

        if ( strBuf == "quit" ) {
            break;
        }

        const  int  retVal  = parseConsoleInput(strBuf, g_gcGameCtrl);
        if ( retVal != ERR_SUCCESS ) {
            std::cerr   <<  "\nCommand Failed"  <<  std::endl;
        }
    }

    return ( 0 );
}
