#include "ChessRules.h"
#include "chessPosList.h"
#include "menu.h"



chessPosArray*** validKnightMoves() /*creates a matrix of pointer to arrays of possible knight moves*/
{
	int i, j;
	char letter, number;

	chessPosArray*** board = (chessPosArray***)malloc(BOARD_SIZE * sizeof(chessPosArray**));
	checkMemoryAllocation(board);

	for (i = 0; i < BOARD_SIZE; i++)
	{
		board[i] = (chessPosArray**)malloc(BOARD_SIZE * sizeof(chessPosArray*));
		checkMemoryAllocation(board[i]);

		for (j = 0; j < BOARD_SIZE; j++)
		{
			board[i][j] = (chessPosArray*)malloc(sizeof(chessPosArray));
			checkMemoryAllocation(board[i][j]);

			board[i][j]->size = numberOfKnightOptions(i + 1, j + 1);


			letter = (i - 1) + 'A'; /*converts the 'i' to the matching letter of a position*/
			number = j + '0'; /*coverts the 'j' to the matching number of a position*/

			board[i][j]->positions = KnightOptions(letter + 1, number + 1, board[i][j]->size); /*finds the array of possible positions from a spcific position*/

		}
	}

	return board;

}



chessPos* KnightOptions(char letter, char number, int size) /*gets a letter and a number, representing a position, and the number of the next possible moves, and builds the array of the next possible moves*/
{
	int count = 0;
	chessPos* positions = (chessPos*)malloc(size * sizeof(chessPos));
	checkMemoryAllocation(positions);

	/*checking all the cases possible, depending on the location of the position given*/
	if (letter - 2 >= 'A') /*the position is below rows 1 and 2*/
	{
		if (number + 1 <= ('0' + BOARD_SIZE)) /*the position is to the left of the most right column*/
		{

			positions[count][0] = letter - 2;
			positions[count][1] = number + 1;
			count++;
		}
		if (number - 1 >= '1') /*the position is to the right of colunm 1*/
		{
			positions[count][0] = letter - 2;
			positions[count][1] = number - 1;
			count++;
		}

	}

	if (letter - 1 >= 'A') /*the position is below row 1*/
	{
		if (number + 2 <= ('0' + BOARD_SIZE)) /*the position is to the left of the two most right column*/
		{

			positions[count][0] = letter - 1;
			positions[count][1] = number + 2;
			count++;
		}

		if (number - 2 >= '1')  /*the position is to the right of colunms 1 and 2*/
		{
			positions[count][0] = letter - 1;
			positions[count][1] = number - 2;
			count++;
		}
	}

	if (letter + 1 <= ('A' + BOARD_SIZE - 1))  /*the position is above the last row*/
	{
		if (number + 2 <= ('0' + BOARD_SIZE)) /*the position is to the left of the two most right column*/
		{

			positions[count][0] = letter + 1;
			positions[count][1] = number + 2;
			count++;
		}

		if (number - 2 >= '1')  /*the position is to the right of colunms 1 and 2*/
		{
			positions[count][0] = letter + 1;
			positions[count][1] = number - 2;
			count++;
		}
	}

	if (letter + 2 <= ('A' + BOARD_SIZE - 1))  /*the position is above the last two rows*/
	{
		if (number + 1 <= ('0' + BOARD_SIZE)) /*the position is to the left of the most right column*/
		{

			positions[count][0] = letter + 2;
			positions[count][1] = number + 1;
			count++;
		}
		if (number - 1 >= '1')  /*the position is to the right of colunm 1*/
		{
			positions[count][0] = letter + 2;
			positions[count][1] = number - 1;
			count++;
		}

	}

	return positions;

}



int numberOfKnightOptions(int i, int j) /*gets a coordinate (i,j) and calculates the number of possible knight moves*/
{
	if (i == 1 || i == BOARD_SIZE) /*first or last row*/
	{
		if (j == 1 || j == BOARD_SIZE) /*first or last columns, therefore in the corners*/
		{
			return 2;
		}
		else if (j == 2 || j == BOARD_SIZE - 1) /*second column or one before the last column*/
		{
			return 3;
		}
		else /*column 3 up to the third before the last column*/
		{
			return 4;
		}
	}

	else if (i == 2 || i == BOARD_SIZE - 1) /*second row or one before the last row*/
	{
		if (j == 1 || j == BOARD_SIZE) /*first or last columns*/
		{
			return 3;
		}
		else if (j == 2 || j == BOARD_SIZE - 1) /*second column or one before the last column*/
		{
			return 4;
		}
		else /*column 3 up to the third before the last column*/
		{
			return 6;
		}
	}
	else /*row 3 up to the third before the last row*/
	{
		if (j == 1 || j == BOARD_SIZE)  /*first or last columns*/
		{
			return 4;
		}
		else if (j == 2 || j == BOARD_SIZE - 1)  /*second column or one before the last column*/
		{
			return 6;
		}
		else /*column 3 up to the third before the last column*/
		{
			return 8;
		}
	}


}



void makeFalseBoolArr(bool*** isAppear) /*sets all cells in the matrix to false*/
{
	int i, j;

	for (i = 0; i < BOARD_SIZE; i++)
	{
		(*isAppear)[i] = (bool*)malloc(BOARD_SIZE * sizeof(bool));
		checkMemoryAllocation((*isAppear)[i]);

		for (j = 0; j < BOARD_SIZE; j++)
		{
			(*isAppear)[i][j] = false;
		}
	}
}


pathTree findAllPossibleKnightPaths(chessPos* startingPosition) /*gets a starting position and creats a tree that contains all the possible valid paths for a knight*/
{
	pathTree res;
	chessPosArray*** validMovesArr = validKnightMoves();
	bool** isAppear = (bool**)malloc(BOARD_SIZE * sizeof(bool*));
	checkMemoryAllocation(isAppear);

	makeFalseBoolArr(&isAppear);

	res.root = findAllPossibleKnightPathsHelper(startingPosition, validMovesArr, &isAppear);

	freeBoolArr(isAppear);

	freeChessPosArr(validMovesArr);

	return res;
}



treeNode* findAllPossibleKnightPathsHelper(chessPos* startingPosition, chessPosArray*** validMovesArr, bool*** isAppear) /*gets a starting position and creats a tree node that contains the position, and a list of all of its next moves' paths*/
{
	int i;
	treeNode* newRoot = (treeNode*)(malloc(sizeof(treeNode)));
	checkMemoryAllocation(newRoot);

	chessPosArray* pNextMoves;
	chessPos* nextMoves;
	treeNodeListCell* saver = NULL;
	treeNodeListCell* newListNode;


	newRoot->position[0] = (*startingPosition)[0]; /*sets the newRoot to the starting position*/
	newRoot->position[1] = (*startingPosition)[1];
	newRoot->next_possible_positions = NULL;

	pNextMoves = validMovesArr[(*startingPosition)[0] - 'A'][(*startingPosition)[1] - '1']; /*gets the list of next possible moves from the starting position*/
	nextMoves = pNextMoves->positions;

	(*isAppear)[(*startingPosition)[0] - 'A'][(*startingPosition)[1] - '1'] = true;


	for (i = 0; i < pNextMoves->size; i++)
	{

		if (!(*isAppear)[(nextMoves[i])[0] - 'A'][(nextMoves[i])[1] - '1']) /*if the position has not appeared yet*/
		{

			(*isAppear)[(nextMoves[i])[0] - 'A'][(nextMoves[i])[1] - '1'] = true;

			newListNode = (treeNodeListCell*)malloc(sizeof(treeNodeListCell));
			checkMemoryAllocation(newListNode);

			newListNode->next = NULL;


			newListNode->node = findAllPossibleKnightPathsHelper(nextMoves[i], validMovesArr, isAppear);

			if (newRoot->next_possible_positions == NULL)
			{
				newRoot->next_possible_positions = newListNode;
			}
			else /*inserts to end list*/
			{
				saver = newRoot->next_possible_positions;
				newRoot->next_possible_positions = newListNode;
				newRoot->next_possible_positions->next = saver;
			}

		}


	}

	(*isAppear)[newRoot->position[0] - 'A'][newRoot->position[1] - '1'] = false; /*after returning, the starting position appearance needs to be set as false, in order to check other paths*/

	return newRoot;
}



chessPosList* findKnightPathCoveringAllBoard(pathTree* path_tree) /*return a path that covers all of the board, in a list, and 'NULL' if no path as such*/
{
	int ListSize = 0;
	chessPosList* res;

	res = findKnightPathCoveringAllBoardHelper(path_tree->root, &ListSize);

	if (ListSize == BOARD_SIZE * BOARD_SIZE) /*if covers all board*/
	{
		return res;
	}
	else /*if does not cover all board*/
	{
		return NULL;
	}
}



chessPosList* findKnightPathCoveringAllBoardHelper(treeNode* root, int* listSize) /*returns the longest list from a root, and its length*/
{
	treeNodeListCell* curr;
	chessPosList* maxList = (chessPosList*)malloc(sizeof(chessPosList));
	checkMemoryAllocation(maxList);

	chessPosList* currentList = NULL;
	int maxSize = 0;
	int currentSize = 0;

	makeEmptyChessPosList(maxList);

	if (root == NULL)
	{
		*listSize = 0;
		currentList = (chessPosList*)malloc(sizeof(chessPosList));
		checkMemoryAllocation(currentList);

		makeEmptyChessPosList(currentList);
		return currentList;
	}

	curr = root->next_possible_positions;

	while (curr != NULL)
	{
		currentList = findKnightPathCoveringAllBoardHelper(curr->node, &currentSize);

		if (currentSize > maxSize)
		{
			freeChessPosList(maxList);
			maxSize = currentSize;
			maxList = currentList;
		}
		else /*maxList is bigger*/
		{
			freeChessPosList(currentList);
		}


		curr = curr->next;

	}

	insertDataToStartChessPosList(maxList, root->position);
	maxSize++;

	*listSize = maxSize;

	return maxList;
}





int checkAndDisplayPathFromFile(char* file_name) /*gets an file name, checks if the list in the file is valid and displays the path from that list*/
{
	int listLen;
	int validMove;
	int count = 0;
	int stage = 1;
	short size;
	BYTE currentLetter;
	BYTE currentNumber;
	BYTE mask = 0x07; /*0000 0111*/
	BYTE currentRead[3];
	chessPos currentChessPos;
	chessPosList* lst = (chessPosList*)(malloc(sizeof(chessPosList)));
	checkMemoryAllocation(lst);

	chessPosArray*** validMovesArr;

	FILE* fp = fopen(file_name, "rb");

	makeEmptyChessPosList(lst);

	if (fp == NULL) /*file doesn't exist*/
	{
		free(lst);
		return -1;
	}
	else /*file does exist*/
	{
		validMovesArr = validKnightMoves();

		fread(&size, sizeof(short), 1, fp);

		fread(currentRead, sizeof(BYTE), 3, fp);

		/*goes through the file' data. reads 3 BYTEs which represents 4 positions. each one of the 4 positions, is handled differently.
		  the way to handle, is marked in the varible 'stage'*/
		while (count < size)
		{
			switch (stage)
			{
			case 1:
				currentLetter = currentRead[0];
				currentLetter = currentLetter >> 5;
				currentLetter = currentLetter + 'A';

				currentNumber = currentRead[0];
				currentNumber = currentNumber >> 2;
				currentNumber = currentNumber & mask;
				currentNumber = currentNumber + '1';

				break;
			case 2:
				currentLetter = currentRead[0];
				currentLetter = currentLetter << 1;
				currentLetter = currentLetter | (currentRead[1] >> 7);
				currentLetter = currentLetter & mask;
				currentLetter = currentLetter + 'A';

				currentNumber = currentRead[1];
				currentNumber = currentNumber >> 4;
				currentNumber = currentNumber & mask;
				currentNumber = currentNumber + '1';

				break;
			case 3:
				currentLetter = currentRead[1];
				currentLetter = currentLetter >> 1;
				currentLetter = currentLetter & mask;
				currentLetter = currentLetter + 'A';

				currentNumber = currentRead[1];
				currentNumber = currentNumber << 2;
				currentNumber = currentNumber | (currentRead[2] >> 6);
				currentNumber = currentNumber & mask;
				currentNumber = currentNumber + '1';

				break;
			case 4:
				currentLetter = currentRead[2];
				currentLetter = currentLetter >> 3;
				currentLetter = currentLetter & mask;
				currentLetter = currentLetter + 'A';

				currentNumber = currentRead[2];
				currentNumber = currentNumber & mask;
				currentNumber = currentNumber + '1';

				break;
			}

			currentChessPos[0] = currentLetter;
			currentChessPos[1] = currentNumber;

			validMove = checkAndInsertToChessPosList(currentChessPos, lst, validMovesArr);

			if (validMove == 1) /*not a vaild knight path*/
			{
				freeChessPosList(lst);
				freeChessPosArr(validMovesArr);
				fclose(fp);
				return 1;
			}

			count++;

			stage++;

			if (stage == 5) /*after stage 4, returns to stage 1*/
			{
				stage = 1;
				fread(currentRead, sizeof(BYTE), 3, fp);
			}


		}

		freeChessPosArr(validMovesArr);

		display(lst);

		listLen = chessPosListLen(lst);

		freeChessPosList(lst);

		fclose(fp);

		if (listLen == BOARD_SIZE * BOARD_SIZE) /*positions in list are covering all board*/
		{
			return 2;
		}

	}



	return 3;
}



bool isInArr(chessPos toFind, chessPosArray* arrOfPositions) /*checks if a position is a valid knight move*/
{
	int i;

	for (i = 0; i < arrOfPositions->size; i++)
	{
		if ((arrOfPositions->positions[i])[0] == toFind[0] && (arrOfPositions->positions[i])[1] == toFind[1])
		{
			return true;
		}
	}

	return false;
}



int checkAndInsertToChessPosList(chessPos currentChessPos, chessPosList* lst, chessPosArray*** validMovesArr) /*checks if a position is a valid knight move*/
{
	if (lst->tail == NULL)
	{
		insertDataToStartChessPosList(lst, currentChessPos);
		return 0;
	}
	else
	{
		if (isInArr(currentChessPos, validMovesArr[lst->tail->position[0] - 'A'][lst->tail->position[1] - '1']))
		{
			insertDataToEndChessPosList(lst, currentChessPos);
			return 0;
		}
		else
		{
			return 1;
		}

	}
}

void freePathTree(pathTree* path) /*free the path tree*/
{
	freePathTreeHelper(path->root);
	path->root = NULL;
}

void freePathTreeHelper(treeNode* root) /*free the path tree */
{
	treeNodeListCell* curr;
	treeNodeListCell* next;

	if (root == NULL)
	{
		return;
	}

	curr = root->next_possible_positions;

	while (curr != NULL)
	{
		freePathTreeHelper(curr->node);
		next = curr->next;
		free(curr);
		curr = next;
	}

	free(root);
}

void freeBoolArr(bool** arr) /*free the bool array*/
{
	int i;

	for (i = 0; i < BOARD_SIZE; i++)
	{
		free(arr[i]);
	}

	free(arr);
}

void freeChessPosArr(chessPosArray*** board) /*free chessPos array*/
{
	int i, j;

	for (i = 0; i < BOARD_SIZE; i++)
	{
		for (j = 0; j < BOARD_SIZE; j++)
		{
			free(board[i][j]->positions);
		}

		free(board[i]);
	}

	free(board);
}
