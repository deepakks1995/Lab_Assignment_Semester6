/*
* @file botTemplate.cpp
* @author Arun Tejasvi Chaganty <arunchaganty@gmail.com>
* @date 2010-02-04
* Template for users to create their own bots
*/

#include "Othello.h"
#include "OthelloBoard.h"
#include "OthelloPlayer.h"
#include <cstdlib>
using namespace std;
using namespace Desdemona;

class MyBot: public OthelloPlayer
{
    public:
        /**
         * Initialisation routines here
         * This could do anything from open up a cache of "best moves" to
         * spawning a background processing thread. 
         */
        MyBot( Turn turn );

        /**
         * Play something 
         */
        virtual Move play( const OthelloBoard& board );
    private:
};

MyBot::MyBot( Turn turn )
    : OthelloPlayer( turn )
{
}
Turn global;
int evaluation(OthelloBoard & board){
    list<Move> moves = board.getValidMoves(global);
    int right = moves.size();
    list<Move> moves = board.getValidMoves(other(global));
    return right-moves.size();
}
int minimax(const OthelloBoard & board, int depth,bool isMaximizingPlayer, int alpha, int beta){
    if(depth == 1){
        return evaluation(board);
    }
    if(isMaximizingPlayer){
        int bestval = -1000;
        list<Move> moves = board.getValidMoves(global);
        list<Move>::iterator it;
        for(it = moves.begin(); it!=moves.end();++it){
            OthelloBoard temp_board = board;
            temp_board.makeMove(global, *it);
            int value = minimax(temp_board, depth+1, false, alpha,beta);
            bestval = max(bestval, value);
            apha = max(alpha, bestval);
            if(beta<=alpha) break;
        }
        return bestval;
    }
    else{
        int bestval = 1000;
        list<Move> moves = board.getValidMoves(other(global));
        list<Move>::iterator it;
        for(it = moves.begin(); it!=moves.end();++it){
            OthelloBoard temp_board = board;
            temp_board.makeMove(other(global), *it);
            int value = minimax(temp_board, depth+1, true, alpha,beta);
            bestval = min(bestval,value);
            beta = min(beta, bestval);
            if(beta <= alpha) break;
        }
        return bestval;
    }
}
Move MyBot::play( const OthelloBoard& board )
{
    global = turn;

    list<Move> moves = board.getValidMoves( turn );
    //int randNo = rand() % moves.size();
    list<Move>::iterator it;
    int alpha = -1000, beta = 1000, bestval = -1000;
    Move optimal = *(moves.begin());
    for(it = moves.begin();it!=moves.end();++it){
        OthelloBoard temp_board = board;
        temp_board.makeMove(turn, *it);
        int value = minimax(temp_board, 1, false,alpha , beta);
        if(value > bestval){
            bestval = value;
            optimal = *it;
        }
        apha = max(alpha, bestval);
        if(beta<=alpha) break;
    }
    return optimal;
}

// The following lines are _very_ important to create a bot module for Desdemona

extern "C" {
    OthelloPlayer* createBot( Turn turn )
    {
        return new MyBot( turn );
    }

    void destroyBot( OthelloPlayer* bot )
    {
        delete bot;
    }
}

