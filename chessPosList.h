#ifndef CHESSPOSLIST_H

#define CHESSPOSLIST_H

typedef struct _chessPosCell
{
	chessPos position;
	struct _chessPosCell* next;
}chessPosCell;

typedef struct _chessPosList
{
	chessPosCell* head;
	chessPosCell* tail;
}chessPosList;

void display(chessPosList* lst); /*gets a chessPosList, removes repeating positions and prints a board and the path of the knight*/
void checkAndRemoveRepeatingPositions(bool*** isAppear, chessPosList* lst); /*removes all repeating positions from the list*/
void printMovesInOrder(chessPosList* lst); /*prints a board and the knight path from the list*/
void makeEmptyChessPosList(chessPosList* lst); /*makes an empty list*/
void insertDataToStartChessPosList(chessPosList* lst, chessPos toInsert); /*inserts some data, to the start of a chessPosList*/
chessPosCell* creatNewChessPosCell(chessPos data, chessPosCell* next); /*creates a new chessPosCell*/
void insertNodeToStartChessPosList(chessPosList* lst, chessPosCell* toInsert); /*inserts a node to the start of chessPosList*/
void insertDataToEndChessPosList(chessPosList* lst, chessPos toInsert); /*inserts some data to the end of chessPosList*/
void insertNodeToEndChessPosList(chessPosList* lst, chessPosCell* toInsert); /*inserts a node to the end of chessPosList*/
bool isEmptyChessPosList(chessPosList* lst); /*check if the list is empty*/
void removeNodeFromList(chessPosList* lst, chessPosCell* toRemove); /*removes a node from chessPosList*/
short chessPosListLen(chessPosList* lst); /*calculates the lenth of a list*/
void saveListToBinFile(char* file_name, chessPosList* pos_list); /*gets a file name and writes a list of positions into a file in a proper format*/
void freeChessPosList(chessPosList* lst); /*free the chessPos list*/

#endif