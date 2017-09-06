/*
 * @file botTemplate.cpp
 * @author Arun Tejasvi Chaganty <arunchaganty@gmail.com>
 * @date 2010-02-04
 * @modified-by Sabarinath, Abhiram
 * @modified-date 2012-11-10
 * Template for users to create their own bots
 */

#include "Othello.h"
#include "OthelloBoard.h"
#include "OthelloPlayer.h"
#include <cstdlib>
#include <algorithm>
#include <vector>
#include <list>
#include <cstring>
#include <climits>
#include <map>
#include <pthread.h>
using namespace std;
using namespace Desdemona;

#define ll long long
#define ull unsigned long long

#define ff first
#define ss second
#define PB push_back
#define PF push_front
#define MP make_pair

/*Simulate for different values and choose the best*/
#define STABILITY_WEIGHT 70

#define PIECE_WEIGHT 3
#define DISC_WEIGHT 20
#define MOBILIITY_WEIGHT 40
#define FRONTIER_WEIGHT 10

#define MAX_NUM LONG_MAX
#define MIN_NUM LONG_MIN

/*Global Variables*/

/*Always keep the depth to be an even number ( preferably) */
int PLY_DEPTH = 6;

typedef pair<double, double> pdd;

map<ll, pdd > store;

static int gameMovesDone = 5;

/* The best that can be made by our bot*/
Move FinalMove(-1, -1);

/* Coin Color of our Move*/
static Turn ourTurn;

/* The Board copy after making the FinalMove*/
static OthelloBoard PrevBoard;

/* Move made by the opponent*/
Move PrevMove(-1, -1);

/* Flag to check whether the first move is done*/
static bool strtGame = true;

/*Number of immediate Successors Explored*/
static int threadDone;

/*Number of level 2 successors explored completely*/
static int threadDone2;

/*Flag for level 2 Successors Explored*/
static bool thread2Done[32];

/*List of Immediate Moves*/
static list<Move> immediateSucc;

/*List of lists : of all level 1 Successors */
static list<Move> moveLst1[32];

/*List of lists : of all level 2 Successors */
static list<Move> moveLst2[32][32];

/* The thread that RGs the opponent */
static pthread_t RGThread;
static int RGThreadStatus;

/*Check for Thread completeness*/
bool threadSuccessfull;

/*Position of the Move Made by the opponent*/
int pos;

/*Move is made by opponent or also not passed by me*/
bool OpponentMoveDone;

/*Flag to indicate whether a thread has done the shallow depth*/
bool shallowDepthDone;


int scoreok[10][10] = {
            {0,  0,  0,  0,  0,  0,  0,  0,  0,  0},
            {0, 65, -3,  6,  4,  4,  6, -3, 65,  0},
            {0, -3, -29, 3,  1,  1,  3, -29,-3,  0},
            {0,  6,  3,  5,  3,  3,  5,  3,  6,  0},
            {0,  4,  1,  3,  1,  1,  3,  1,  4,  0},
            {0,  4,  1,  3,  1,  1,  3,  1,  4,  0},
            {0,  6,  3,  5,  3,  3,  5,  3,  6,  0},
            {0, -3, -29, 3,  1,  1,  3, -29,-3,  0},
            {0, 65, -3,  6,  4,  4,  6, -3, 65,  0},
            {0,  0,  0,  0,  0,  0,  0,  0,  0,  0}
    };

int scorebetter[10][10] = {
    {0,  0,  0,  0,  0,  0,  0,  0,  0,  0},
    {0, 30, -10,  21,  8,  8,  21, -10, 30,  0},
    {0, -10, -17, -4,  1,  1,  -4, -17, -10,  0},
    {0,  21,  -4,  2,  2,  2,  2,  -4,  21,  0},
    {0,  8,  1,  2,  1,  1,  2,  1,  8,  0},
    {0,  8,  1,  2,  1,  1,  2,  1,  8,  0},
    {0,  21,  -4,  2,  2,  2,  2,  -4,  21,  0},
    {0, -10, -17, -4,  1,  1,  -4, -17, -10,  0},
    {0, 30, -10,  21,  8,  8,  21, -10, 30,  0},
    {0,  0,  0,  0,  0,  0,  0,  0,  0,  0}
};

int score[10][10] = {
    {0,  0,  0,  0,  0,  0,  0,  0,  0,  0},
    {0, 20, -3,  11,  8,  8,  11, -3, 20,  0},
    {0, -3, -7, -4,  1,  1,  -4, -7, -3,  0},
    {0,  11,  -4,  2,  2,  2,  2,  -4,  11,  0},
    {0,  8,  1,  2,  -3,  -3,  2,  1,  8,  0},
    {0,  8,  1,  2,  -3,  -3,  2,  1,  8,  0},
    {0,  11,  -4,  2,  2,  2,  2,  -4,  11,  0},
    {0, -3, -7, -4,  1,  1,  -4, -7, -3,  0},
    {0, 20, -3,  11,  8,  8,  11, -3, 20,  0},
    {0,  0,  0,  0,  0,  0,  0,  0,  0,  0}
};

/**
 *  Each Node of the MinMax Tree is represented by the 'Node' Class
 */
class Node {
public:
	OthelloBoard nodeBoard;
	Turn nodeType;

	Node(OthelloBoard board, Turn type);
	~Node();
};

Node::Node(OthelloBoard board, Turn type) {
	this->nodeBoard = board;
	this->nodeType = type;
}

bool isDiagonalsFilled(int i, int j, OthelloBoard& curBoard )
{
	int k = i, l = j;
	while(0 <= k && k < 8 && 0 <= l && l < 8){
		if(curBoard.get(k,l) == EMPTY)
			return false;
		k++, l++;
	}
	k = i, l = j;
	while(0 <= k && k < 8 && 0 <= l && l < 8){
		if(curBoard.get(k,l) == EMPTY)
			return false;
		k++, l--;
	}
	k = i, l = j;
	while(0 <= k && k < 8 && 0 <= l && l < 8){
		if(curBoard.get(k,l) == EMPTY)
			return false;
		k--, l++;
	}
	k = i, l = j;
	while(0 <= k && k < 8 && 0 <= l && l < 8){
		if(curBoard.get(k,l) == EMPTY)
			return false;
		k--, l--;
	}
	return true;
}

/* Currently implementing stability as a separate function. Later integrate into evaluation to save time */
int stabilityFactor(Node* curNode)
{
	OthelloBoard& curBoard = curNode->nodeBoard;
	Turn myTurn = curNode->nodeType;
	Turn otherTurn = other(myTurn);

	bool filledRows[8];
	bool filledCols[8];

	bool check ;
	for (int i = 0; i < 8; i++){
		check = true;
		for (int j = 0; j < 8; j++){
			if (curBoard.get(i, j) == EMPTY)
				check = false;
		}
		if (check)
			filledRows[i] = true;
	}
	for (int j = 0; j < 8; j++){
		check = true;
		for (int i = 0; i < 8; i++){
			if (curBoard.get(i, j) == EMPTY)
				check = false;
		}
		if (check)
			filledCols[j] = true;
	}
	int stability = 0;
	for( int i = 0; i < 8; i ++){
		for(int j = 0; j < 8; j ++){
			if(filledRows[i] && filledCols[j] && isDiagonalsFilled(i,j,curBoard) && myTurn == curBoard.get(i, j))
				stability++;
			if(filledRows[i] && filledCols[j] && isDiagonalsFilled(i,j,curBoard) && otherTurn == curBoard.get(i, j))
				stability--;
		}
	}
	if( filledRows[0] && myTurn == curBoard.get(0, 0)) stability += 8;
	if( filledRows[7] && myTurn == curBoard.get(7, 0)) stability += 8;
	if( filledCols[0] && myTurn == curBoard.get(0, 7)) stability += 8;
	if( filledCols[7] && myTurn == curBoard.get(7, 7)) stability += 8;
	if( filledRows[0] && otherTurn == curBoard.get(0, 0)) stability -= 8;
	if( filledRows[7] && otherTurn == curBoard.get(7, 0)) stability -= 8;
	if( filledCols[0] && otherTurn == curBoard.get(0, 7)) stability -= 8;
	if( filledCols[7] && otherTurn == curBoard.get(7, 7)) stability -= 8;

	return stability;
}

inline bool checkBound(int x, int y){
	return (x >= 0 && y < 8 && y >= 0 && x < 8);
}

double evaluationFunc(Node* curNode) {
	//TODO: Return a value for the given Node based on different strategies.
	Turn myTurn = curNode->nodeType;
	Turn otherTurn = other(myTurn);

	double finalVal = 0.0;

	/*Coin position weight*/
	int discEvalVal = 0;
	int frontierVal = 0;
	int i, j, a, b;

	a = (curNode->nodeBoard).getRedCount();
	b = (curNode->nodeBoard).getBlackCount();
	if(gameMovesDone > 54)
		return (( myTurn == RED ? (a-b) : (b-a))*PIECE_WEIGHT);

	for (i = 0; i < 8; ++i) {
		for (j = 0; j < 8; ++j){
			if ((curNode->nodeBoard).get(i, j) == myTurn){
				discEvalVal += score[i + 1][j + 1];
				if(checkBound(i-1, j) && (curNode->nodeBoard).get(i-1,j) == EMPTY)
					frontierVal++;
				else if(checkBound(i, j-1) && (curNode->nodeBoard).get(i,j-1) == EMPTY)
					frontierVal++;
				else if(checkBound(i+1, j) && (curNode->nodeBoard).get(i+1,j) == EMPTY)
					frontierVal++;
				else if(checkBound(i, j+1) && (curNode->nodeBoard).get(i,j+1) == EMPTY)
					frontierVal++;
			}
			else if ((curNode->nodeBoard).get(i, j) == otherTurn){
				discEvalVal -= score[i + 1][j + 1];
				if(checkBound(i-1, j) && (curNode->nodeBoard).get(i-1,j) == EMPTY)
					frontierVal--;
				else if(checkBound(i, j-1) && (curNode->nodeBoard).get(i,j-1) == EMPTY)
					frontierVal--;
				else if(checkBound(i+1, j) && (curNode->nodeBoard).get(i+1,j) == EMPTY)
					frontierVal--;
				else if(checkBound(i, j+1) && (curNode->nodeBoard).get(i,j+1) == EMPTY)
					frontierVal--;
			}
		}
	}

	finalVal += DISC_WEIGHT*discEvalVal;
	finalVal -= FRONTIER_WEIGHT*frontierVal;

	/*Add weights to the mobility count*/
	a = (curNode->nodeBoard).getValidMoves(myTurn).size();
	b = (curNode->nodeBoard).getValidMoves(otherTurn).size();
	finalVal += MOBILIITY_WEIGHT*(a-b);

	/*Add weights to the Piecewise count of Coins*/
	finalVal += PIECE_WEIGHT*( myTurn == RED ? (a-b) : (b-a) );

	/*Add weights to frontier cells*/
	return finalVal + (stabilityFactor(curNode) * STABILITY_WEIGHT);
}

double evaluationFunc1(Node* root, Turn myTurn){

	Turn otherTurn = other(myTurn);

	int a = (root->nodeBoard).getRedCount();
	int b = (root->nodeBoard).getBlackCount();
	if(gameMovesDone > 54)
		return (( myTurn == RED ? (a-b) : (b-a))*PIECE_WEIGHT);
	double finalVal = 0.0;
	int i, j;
	for(i = 0; i < 8; ++i){
		for( j = 0; j < 8; ++j){
			if((root->nodeBoard).get(i,j) == myTurn)
				finalVal += score[i+1][j+1];
			else if((root->nodeBoard).get(i,j) == otherTurn)
				finalVal -= score[i+1][j+1];
		}
	}
	return finalVal;
}

/**
 * Recursive procedure implementing MinMax Tree Construction, with alpha - beta pruning
 * Pruning is done while constructing with the help of Evaluation function
 * List of all the children of a current Node can be obtained from the .getValidMoves method of OthelloBoard object
 */

double alphabetaMiniMax(Node* root, int depth, double alpha, double beta, int ind) {
//	int hashCode = getHash(root->nodeBoard);
//	if(store[hashCode]){
//
//	}
	if (depth == PLY_DEPTH)
		return evaluationFunc(root);

	list<Move> successors = (depth == 0 ? moveLst1[pos] : (depth == 1  ? moveLst2[pos][ind] :  (root->nodeBoard).getValidMoves(root->nodeType)));
	/*Mobility Rule for inner nodes*/
	if (successors.empty())
		return evaluationFunc(root);

	Node* tmp = NULL;
	double newValue = 0.0;
	int i = 0;
	Turn otherTurn = other(root->nodeType);

	for (list<Move>::iterator it = successors.begin(); it != successors.end(); ++it, ++i) {
		tmp = new Node(root->nodeBoard, otherTurn);
		(tmp->nodeBoard).makeMove(root->nodeType, *it);
		newValue = -1 * alphabetaMiniMax(tmp, depth + 1, -1 * beta, -1 * alpha, i);
		if (newValue > alpha) {
			alpha = newValue;
			if (depth == 0)
				FinalMove.x = it->x, FinalMove.y = it->y;
		}
		if (alpha >= beta)
			return alpha;
	}
	return alpha;
}

typedef pair<double, Move> pim;

bool compareTo(const pim& a, const pim& b){
	return a.first > b.first;
}

bool compareTo1(const pim& a, const pim& b){
	return b.first > a.first;
}

/*Shallow Depth MiniMax;  2 depth lookup; Ordering using sort function*/
void shallowDepth(Node* root){

	if(!threadSuccessfull)
		moveLst1[pos] = (root->nodeBoard).getValidMoves(ourTurn);

	list<pim> compareLst;
	list<pim> compareLst1[32];
	int size = 0;
	OthelloBoard saveBoard = root->nodeBoard;
	Turn otherTurn = other(ourTurn);

	for(list<Move>::iterator it = moveLst1[pos].begin(); it != moveLst1[pos].end(); ++it){
		(root->nodeBoard).makeMove(ourTurn, *it);
		compareLst.push_back(MP(evaluationFunc1(root, otherTurn), *it));
		root->nodeBoard = saveBoard;
	}
	compareLst.sort(compareTo);

	for(list<pim>::iterator it = compareLst.begin(); it != compareLst.end(); ++it, ++size){
		(root->nodeBoard).makeMove(ourTurn, it->second);
		//if(!(thread2Done[size] && threadSuccessfull))
			moveLst2[pos][size] = (root->nodeBoard).getValidMoves(otherTurn);
		OthelloBoard saveBoard1 = root->nodeBoard;
		for( list<Move>::iterator kj = moveLst2[pos][size].begin(); kj != moveLst2[pos][size].end(); ++kj){
			(root->nodeBoard).makeMove(otherTurn, *kj);
			compareLst1[size].push_back(MP(evaluationFunc1(root, ourTurn), *kj));
			root->nodeBoard = saveBoard1;
		}
		root->nodeBoard = saveBoard;
	}

	for(int i = 0; i < size; ++i)
		compareLst1[i].sort(compareTo1);

	moveLst1[pos].clear();
	for(list<pim>::iterator it = compareLst.begin(); it != compareLst.end(); ++it)
		moveLst1[pos].push_back(it->second);

	for(int i = 0; i < size; ++i){
		moveLst2[pos][i].clear();
		for(list<pim>::iterator it = compareLst1[i].begin(); it != compareLst1[i].end(); ++it)
			moveLst2[pos][i].push_back(it->second);
	}

}

/*Function to calculate 2 levels of Moves*/
void* threadFunc(void* ptr){
	int i, j;
	shallowDepthDone = false;
	threadDone = threadDone2 = -1;
	memset(thread2Done,false, sizeof(thread2Done));
	Turn otherTurn = other(ourTurn);
	immediateSucc = PrevBoard.getValidMoves(otherTurn);
	list<Move>::iterator it, kj;
	OthelloBoard saveBoard = PrevBoard;

	for(i = 0, it = immediateSucc.begin(); it != immediateSucc.end(); ++it, ++i){
		PrevBoard.makeMove(otherTurn, *it);
		moveLst1[i] = PrevBoard.getValidMoves(ourTurn);
		PrevBoard = saveBoard;
		++threadDone;
	}

	for(i = 0, kj = immediateSucc.begin() ; kj != immediateSucc.end(); ++kj, ++i ){
		PrevBoard.makeMove(otherTurn, *kj);
		OthelloBoard saveBoard1 = PrevBoard;
		for( j = 0, it = moveLst1[i].begin(); it != moveLst1[i].end(); ++it, ++j){
			PrevBoard.makeMove(ourTurn, *it);
			moveLst2[i][j] = PrevBoard.getValidMoves(otherTurn);
			PrevBoard = saveBoard1;
		}
		thread2Done[i] = true;
		++threadDone2;
		PrevBoard = saveBoard;
	}
	return NULL;
}

int getIndex(){
	list<Move> moveLst = PrevBoard.getValidMoves(other(ourTurn));
	int i = 0;
	for(list<Move>::iterator it = moveLst.begin(); it != moveLst.end(); ++it, ++i){
		if(it->x == PrevMove.x && it->y == PrevMove.y)
			return i;
	}
	return -1;
}

void getPrevMove(const OthelloBoard& board) {
	int i, j;
	OpponentMoveDone = true;
	int numberOfMoves = 0;
	for (i = 0; i < 8; ++i) {
		for (j = 0; j < 8; ++j) {
			if (PrevBoard.get(i, j) == EMPTY && board.get(i, j) != PrevBoard.get(i, j)) {
				PrevMove.x = i, PrevMove.y = j;
				++numberOfMoves;
				if(numberOfMoves > 1)
					OpponentMoveDone = false;
			}
		}
	}
	gameMovesDone += numberOfMoves;
	if(numberOfMoves == 0)
		OpponentMoveDone = false;
}

void setPlyDepth(){
	if(gameMovesDone < 6 || gameMovesDone > 54)
		PLY_DEPTH = 10;
	else if(gameMovesDone < 7 || gameMovesDone > 50)
		PLY_DEPTH = 8;
	else if(gameMovesDone < 9 || gameMovesDone > 45)
		PLY_DEPTH = 7;
	else if(gameMovesDone < 16 || gameMovesDone > 38)
		PLY_DEPTH = 6;
	else
		PLY_DEPTH = 5;
}

class MyBot: public OthelloPlayer {
public:
	/**
	 * Initialization routines here
	 * This could do anything from open up a cache of "best moves" to
	 * spawning a background processing thread.
	 */
	MyBot(Turn turn);

	/**
	 * Play something
	 */
	virtual Move play(const OthelloBoard& board);
private:
};

MyBot::MyBot(Turn turn) : OthelloPlayer(turn) {

}

Move MyBot::play(const OthelloBoard& board) {
	ourTurn = turn;
	store.clear();
	threadSuccessfull = false;
	if (!strtGame) {
		pthread_join(RGThread, NULL);
		getPrevMove(board);
		setPlyDepth();
		if(OpponentMoveDone){
			pos = getIndex();
			if(pos <= threadDone && pos != -1)
				threadSuccessfull = true;
		}
	}
	else if (ourTurn == BLACK) {
		strtGame = false;
		--gameMovesDone;
		setPlyDepth();
		PrevBoard = OthelloBoard(board);
		list<Move> moveLst = PrevBoard.getValidMoves(ourTurn);
		list<Move>::iterator it = moveLst.begin();
		int randNo = (rand() % 4);
		for (int i = 0; i < randNo - 1; ++it, ++i);

		FinalMove.x = it->x, FinalMove.y = it->y;
		PrevBoard.makeMove(ourTurn, FinalMove);
		++gameMovesDone;
		/* Initializing the thread to RG opponenet before returning the move */
		RGThreadStatus = pthread_create(&RGThread, NULL, threadFunc, (void*)NULL);

		return FinalMove;
	}
	strtGame = false;
	PrevBoard = OthelloBoard(board);
	Node* root = new Node(PrevBoard, ourTurn);
	if(!shallowDepthDone)
		shallowDepth(root);
	alphabetaMiniMax(root, 0, MIN_NUM, MAX_NUM, 0);
	PrevBoard.makeMove(ourTurn, FinalMove);
	++gameMovesDone;
	/* Initializing the thread to RG opponenet before returning the move */
	RGThreadStatus = pthread_create(&RGThread, NULL, threadFunc, (void*)NULL);

	return FinalMove;
}

// The following lines are _very_ important to create a bot module for Desdemona

extern "C" {
OthelloPlayer* createBot(Turn turn) {
	return new MyBot(turn);
}

void destroyBot(OthelloPlayer* bot) {
	delete bot;
}
}