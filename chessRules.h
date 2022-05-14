#ifndef CHESSRULES_H

#define CHESSRULES_H

#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>

#define BOARD_SIZE 5

typedef struct _treeNodeListCell treeNodeListCell;

typedef char chessPos[2];

typedef struct _chessPosArray
{
	unsigned int size;
	chessPos* positions;
} chessPosArray;

typedef struct _chessPosCell chessPosCell;

typedef struct _chessPosList chessPosList;

typedef struct _treeNode
{
	chessPos position;
	treeNodeListCell* next_possible_positions;
}treeNode;

typedef struct _treeNodeListCell
{
	treeNode* node;
	struct _treeNodeListCell* next;
}treeNodeListCell;

typedef struct _pathTree
{
	treeNode* root;
}pathTree;

chessPosArray*** validKnightMoves(); /*creates a matrix of pointer to arrays of possible knight moves*/
chessPos* KnightOptions(char letter, char number, int size); /*gets a letter and a number, representing a position, and the number of the next possible moves, and builds the array of the next possible moves*/
int numberOfKnightOptions(int i, int j); /*gets a coordinate (i,j) and calculates the number of possible knight moves*/

void makeFalseBoolArr(bool*** isAppear);  /*sets all cells in the matrix to false*/

pathTree findAllPossibleKnightPaths(chessPos* startingPosition); /*gets a starting position and creats a tree that contains all the possible valid paths for a knight*/
treeNode* findAllPossibleKnightPathsHelper(chessPos* startingPosition, chessPosArray*** validMovesArr, bool*** isAppear); /*gets a starting position and creats a tree node that contains the position, and a list of all of its next moves' paths*/
chessPosList* findKnightPathCoveringAllBoard(pathTree* path_tree); /*return a path that covers all of the board, in a list, and 'NULL' if no path as such*/
chessPosList* findKnightPathCoveringAllBoardHelper(treeNode* root, int* listSize); /*returns the longest list from a root, and its length*/

int checkAndDisplayPathFromFile(char* file_name); /*gets an file name, checks if the list in the file is valid and displays the path from that list*/
bool isInArr(chessPos toFind, chessPosArray* arrOfPositions); /*checks if a positions is in an array*/
int checkAndInsertToChessPosList(chessPos currentChessPos, chessPosList* lst, chessPosArray*** validMovesArr); /*checks if a position is a valid knight move*/


void freePathTree(pathTree* path); /*free the path tree*/
void freePathTreeHelper(treeNode* root); /*free the path tree */
void freeBoolArr(bool** arr); /*free the bool array*/
void freeChessPosArr(chessPosArray*** board);/*free chessPos array*/

#endif