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
#include    "FairyShogi/Interface/GameController.h"

#include    <iostream>
#include    <limits>
#include    <cstdlib>
#include    <cstring>
#include    <time.h>
#include    <vector>

using   namespace   FAIRYSHOGI_NAMESPACE;

typedef     Interface::GameController       GameController;

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
    0,
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

const
int
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

int
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
        return ( 0 );
    }

    std::cerr   <<  "Invalid Position Format["  <<  strData  <<  "]"
                <<  std::endl;
    return ( 0 );
}

int
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
    return ( 0 );

}

int
displayBoard(
        const  GameController  &objGame,
        std::ostream           &outStr)
{
    Common::ViewBuffer  vb;
    ::memset( &vb, 0, sizeof(vb) );
    objGame.writeToViewBuffer(vb);

    //  盤面を表示する。    //
    outStr  <<  "| 5| 4| 3| 2| 1|\n";
    outStr  <<  "----------------\n";
    for ( int y = 0; y < 5; ++ y ) {
        for ( int x = 0; x < 5; ++ x ) {
            const  int          pi  = (y * 5) + x;
            const  PieceIndex   dp  = vb.piBoard[pi];
            outStr  <<  "|"  <<  g_tblPieceName[dp];
        }
        outStr  <<  "|"  <<  (y+1)  <<  "\n";
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
    return ( 0 );
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

int
executePlayerCommand(
        const  std::string  &strArgs,
        GameController      &objGame)
{
    CONSTEXPR_VAR   char    chName[2] = { 'b', 'w' };

    if ( strArgs == "next" ) {
        const  PlayerIndex  pi  =  objGame.getCurrentPlayer();
        objGame.setCurrentPlayer(pi ^ 1);
        std::cerr   <<  chName[objGame.getCurrentPlayer()]  <<  std::endl;
        return ( 0 );
    }
    if ( strArgs == "get" ) {
        std::cout   <<  chName[objGame.getCurrentPlayer()]  <<  std::endl;
        return ( 0 );
    }

    if ( (strArgs[0] == '0') || (strArgs[0] == 'b') ) {
        objGame.setCurrentPlayer(0);
        return ( 0 );
    }
    if ( (strArgs[0] == '1') || (strArgs[0] == 'w') ) {
        objGame.setCurrentPlayer(1);
        return ( 0 );
    }

    std::cerr   <<  "Invalid Arguments."    <<  std::endl;
    return ( 0 );
}

int
playForward(
        const  std::string  &strPlay,
        GameController      &objGame)
{
    ActionView  actView;

    if ( objGame.parseActionText(strPlay, &actView) != ERR_SUCCESS )
    {
        std::cerr   <<  "Invalid Arguments."
                    <<  std::endl;
        return ( 0 );
    }

    displayActionView(actView, 1, std::cerr)    <<  std::endl;

#if 0
    int     nx, ny, ox, oy;
    int     pr  = 0;

    nx  =  strPlay[2] - '0';
    ny  =  strPlay[3] - '0';

    if ( (nx < 1) || (5 < nx) || (ny < 1) || (5 < ny) ) {
        std::cerr   <<  "Out of Range (Target)"
                    <<  std::endl;
        return ( 0 );
    }
    nx  = 5 - nx;
    --  ny;
#endif

    ActionList      actList;
    objGame.makeLegalActionList(0, -1, actList);
    const  ActIter  itrEnd  = actList.end();

    ActionFlag      flgLeg  =  Common::ALF_LEGAL_ACTION;
    for ( ActIter itr = actList.begin(); itr != itrEnd; ++ itr ) {
        if ( GameController::isEquals(* itr, actView) ) {
            flgLeg  = (itr->fLegals);
            break;
        }
    }

    if ( flgLeg != Common::ALF_LEGAL_ACTION ) {
        std::cerr   <<  "Not Legal Move."   <<  std::endl;
        if ( strPlay[strPlay.length() - 1] != '!' ) {
            return ( 0 );
        }
    }
    objGame.playForward(actView);

#if 0
    if ( strPlay[1] == '*' ) {
        //  持ち駒を打つ。  //
        int  h  = -1;
        for ( int ht = 0; ht < 13; ++ ht ) {
            if ( g_tblHandName[ht][0] == strPlay[0] ) {
                h   = ht;
                break;
            }
        }
        if ( h == -1 ) {
            std::cerr   <<  "Invalid Piece Name"    <<  strPlay
                        <<  std::endl;
            return ( 0 );
        }

        for ( ActIter itr = actList.begin(); itr != itrEnd; ++ itr ) {
            if ( (itr->putHand) != h )  { continue; }
            if ( (itr->xNewCol) != 4 - nx ) { continue; }
            if ( (itr->yNewRow) != ny ) { continue; }
            flgLeg  = 1;
        }
        if ( (flgLeg == 0) ) {
            std::cerr   <<  "Not Legal Put."    <<  std::endl;
            if ( strPlay[4] != '!' ) {
                return ( 0 );
            }
        }

        objGame.playPutAction(nx, ny, h);

    } else {
        ox  =  strPlay[0] - '0';
        oy  =  strPlay[1] - '0';
        if ( (ox < 1) || (5 < ox) || (oy < 1) || (5 < oy) ) {
            std::cerr   <<  "Out of Range (Source)"
                        <<  std::endl;
            return ( 0 );
        }
        ox  =  5 - ox;
        --  oy;
        const  int  trg = objGame.getBoardState().getFieldPiece(ox, oy);
        if ( (strPlay.length() >= 5) && (strPlay[4] == '+') ) {
            pr  = g_tblPromotion[trg];
        } else {
            pr  = trg;
        }

        for ( ActIter itr = actList.begin(); itr != itrEnd; ++ itr ) {
            if ( (itr->xNewCol) != 4 - nx ) { continue; }
            if ( (itr->yNewRow) != ny ) { continue; }
            if ( (itr->xOldCol) != 4 - ox ) { continue; }
            if ( (itr->yOldRow) != oy ) { continue; }
//            if ( (itr->fpAfter) != pr ) { continue; }
            flgLeg  = 1;
        }
        if ( (flgLeg == 0) ) {
            std::cerr   <<  "Not Legal Move."   <<  std::endl;
            if ( strPlay[strPlay.length() - 1] != '!' ) {
                return ( 0 );
            }
        }

        objGame.playMoveAction(ox, oy, nx, ny, pr);
    }
#endif

    executePlayerCommand("next", objGame);
    objGame.setConstraint(6);

    return ( 0 );
}

int
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
        return ( 0 );
    } else if ( numChk >= 2 ) {
        std::cerr   <<  "** DOUBLE CHECK!"  <<  std::endl;
        objGame.setConstraint(6);
        return ( 0 );
    }

    if ( strArgs[0] == 'g' ) {
        std::cout   <<  "Current Constraint. Dice = "
                    <<  objGame.getConstraint()
                    <<  std::endl;
        return ( 0 );
    }

    if ( strArgs[0] == 'r' ) {
        const  int  rn  =  ((std::rand() >> 8) % 6) + 1;
        std::cout   <<  rn  <<  std::endl;
        objGame.setConstraint(rn);
        return ( 0 );
    }

    const  int  dr  =  strArgs[0] - '0';
    if ( (dr < 0) || (6 < dr) ) {
        std::cerr   <<  "Invalid Arguments."    <<  std::endl;
        return ( 0 );
    }
    objGame.setConstraint(dr);

    return ( 0 );
}

int
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
    return ( 0 );
}

int
executeGoCommand(
        GameController  &objGame)
{
    ActionView  actData;

    if ( objGame.startThinking(actData) != ERR_SUCCESS ) {
        std::cerr   <<  "No Legal Actions"  <<  std::endl;
        return ( 0 );
    }

    std::cout   <<  "bestmove ";
    displayActionView(actData,  0,  std::cout)  <<  std::endl;
    std::cerr   <<  "#  COM : ";
    displayActionView(actData,  1,  std::cerr)  <<  std::endl;
    return ( 0 );
}

int
parseConsoleInput(
        const  std::string  &strLine)
{
    std::vector<std::string>    vTokens;

    vTokens.clear();
    vTokens.reserve(2);

    parseText(
            strLine,  " \t",  1,  vTokens);

    if ( vTokens[0] == "go" ) {
        return ( executeGoCommand(g_gcGameCtrl) );
    } else if ( vTokens[0] == "dice" ) {
        if ( vTokens.size() == 1 ) {
            std::cerr   <<  "Require Arguments."    <<  std::endl;
            return ( 0 );
        }
        return ( executeDiceCommand(vTokens[1], g_gcGameCtrl) );
    } else if ( vTokens[0] == "position" ) {
        if ( vTokens.size() == 1 ) {
            std::cerr   <<  "Require Arguments."    <<  std::endl;
            return ( 0 );
        }
        return  ( setPosition(vTokens[1], g_gcGameCtrl) );

    } else if ( vTokens[0] == "fwd" ) {
        return ( playForward(vTokens[1], g_gcGameCtrl) );
    } else if ( vTokens[0] == "sfen" ) {
        return ( displaySfen(g_gcGameCtrl, std::cout) );
    } else if ( vTokens[0] == "show" ) {
        return ( displayBoard(g_gcGameCtrl, std::cout) );
    } else if ( vTokens[0] == "list" ) {
        vTokens.push_back("cur");
        return ( executeListCommand(vTokens[1], g_gcGameCtrl, std::cout) );
    } else if ( vTokens[0] == "player") {
        vTokens.push_back("next");
        return ( executePlayerCommand(vTokens[1], g_gcGameCtrl) );
    }

    std::cerr   <<  "Invalid Command."  << std::endl;
    return ( 0 );
}

int  main(int argc, char * argv[])
{
    std::cerr   <<  "Fairy Shogi Version 0.0"
                <<  std::endl;

    std::srand( ::time(NULL) );

    std::string     strBuf;
    std::istream   & inStr  = (std::cin);

    g_gcGameCtrl.resetGame();

    for ( ;; ) {
        if ( ! inStr ) {
            break;
        }
        std::cerr   <<  ">";
        std::getline(inStr, strBuf);
        if ( strBuf == "quit" ) {
            break;
        }

        const  int  retVal  = parseConsoleInput(strBuf);
        if ( retVal != 0 ) {
            std::cerr   <<  "Command Failed."   <<  std::endl;
            //exit ( retVal );
        }
    }

    return ( 0 );
}
