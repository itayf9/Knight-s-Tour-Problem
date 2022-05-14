#include "ChessRules.h"
#include "chessPosList.h"
#include "menu.h"



void display(chessPosList* lst) /*gets a chessPosList, removes repeating positions and prints a board and the path of the knight*/
{
	bool** isAppear = (bool**)malloc(BOARD_SIZE * sizeof(bool*));
	checkMemoryAllocation(isAppear);

	chessPosCell* valueSaver;
	int count;

	system("cls"); /*clears the screen*/

	makeFalseBoolArr(&isAppear);

	if (lst->head == NULL && lst->tail == NULL) /*if the list is empty*/
	{
		printBoard(); /*print an empty board*/
		return;
	}

	checkAndRemoveRepeatingPositions(&isAppear, lst);

	printMovesInOrder(lst);

	freeBoolArr(isAppear);
}



void checkAndRemoveRepeatingPositions(bool*** isAppear, chessPosList* lst) /*removes all repeating positions from the list*/
{
	chessPosCell* current;
	chessPosCell* nextSaver;

	current = lst->head;

	while (current != NULL)
	{

		if ((*isAppear)[current->position[0] - 'A'][current->position[1] - '1']) /*if already exists in the list*/
		{
			nextSaver = current->next;
			removeNodeFromList(lst, current);
			current = nextSaver;

		}
		else /*still was not found in the list*/
		{
			(*isAppear)[current->position[0] - 'A'][current->position[1] - '1'] = true;
			current = current->next;
		}
	}
}



void printMovesInOrder(chessPosList* lst) /*prints a board and the knight path from the list*/
{
	chessPosCell* current;
	int count;

	printBoard();

	current = lst->head;
	count = 1;

	while (current != NULL)
	{
		gotoxy((current->position[0] - 'A' + 1) * 2 + 1, (current->position[1] - '0') * 5 + 3); /*sets the cursor to the matching cell on screen*/

		printf("%d", count);
		count++;
		current = current->next;
	}

	gotoxy(4 + 2 * BOARD_SIZE, 0); /*sets the cursor below the board*/
}



void makeEmptyChessPosList(chessPosList* lst) /*makes an empty list*/
{
	lst->head = NULL;
	lst->tail = NULL;
}



void insertDataToStartChessPosList(chessPosList* lst, chessPos toInsert) /*inserts some data, to the start of a chessPosList*/
{
	chessPosCell* newHead;
	newHead = creatNewChessPosCell(toInsert, NULL);
	insertNodeToStartChessPosList(lst, newHead);
}



chessPosCell* creatNewChessPosCell(chessPos data, chessPosCell* next) /*creates a new chessPosCell*/
{
	chessPosCell* res;
	res = (chessPosCell*)malloc(sizeof(chessPosCell));
	checkMemoryAllocation(res);

	(res->position)[0] = data[0];
	(res->position)[1] = data[1];
	res->next = next;

	return res;
}



void insertNodeToStartChessPosList(chessPosList* lst, chessPosCell* toInsert) /*inserts a node to the start of chessPosList*/
{
	if (isEmptyChessPosList(lst))
	{
		toInsert->next = NULL;
		lst->head = toInsert;
		lst->tail = toInsert;
	}
	else
	{
		toInsert->next = lst->head;
		lst->head = toInsert;
	}

}



void insertDataToEndChessPosList(chessPosList* lst, chessPos toInsert) /*inserts some data to the end of chessPosList*/
{
	chessPosCell* newTail;
	newTail = creatNewChessPosCell(toInsert, NULL);
	insertNodeToEndChessPosList(lst, newTail);
}



void insertNodeToEndChessPosList(chessPosList* lst, chessPosCell* toInsert) /*inserts a node to the end of chessPosList*/
{
	if (isEmptyChessPosList(lst))
	{
		toInsert->next = NULL;
		lst->head = toInsert;
		lst->tail = toInsert;
	}
	else
	{
		lst->tail->next = toInsert;
		lst->tail = toInsert;
	}
}



bool isEmptyChessPosList(chessPosList* lst) /*check if the list is empty*/
{
	if (lst->head == NULL)
	{
		return true;
	}
	else
	{
		return false;
	}
}


void removeNodeFromList(chessPosList* lst, chessPosCell* toRemove) /*removes a node from chessPosList*/
{
	chessPosCell* curr;
	chessPosCell* saver;
	chessPosCell* after;

	if (lst->head == toRemove && lst->tail == toRemove) /*if the node to remove is the only one in the list*/
	{
		lst->head = NULL;
		lst->tail = NULL;

		free(toRemove);
	}

	else if (lst->head == toRemove) /*if the node is the head*/
	{
		lst->head = toRemove->next;
		free(toRemove);
	}

	else if (lst->tail == toRemove) /*if the node is the tail*/
	{
		curr = lst->head;
		after = NULL;

		while (curr != toRemove)
		{
			after = curr;

			curr = curr->next;
		}

		lst->tail = after;
		after->next = NULL;
		free(toRemove);
	}
	else /*the node is not the head and not the tail*/
	{
		curr = lst->head;
		after = NULL;

		while (curr != toRemove)
		{
			after = curr;

			curr = curr->next;
		}

		saver = curr->next;
		after->next = saver;
		free(toRemove);
	}
}



short chessPosListLen(chessPosList* lst) /*calculates the lenth of a list*/
{
	short count = 0;
	chessPosCell* curr = lst->head;

	while (curr != NULL)
	{
		count++;

		curr = curr->next;
	}

	return count;
}



void saveListToBinFile(char* file_name, chessPosList* pos_list) /*gets a file name and writes a list of positions into a file in a proper format*/
{
	int stage = 1;
	int count = 0;
	short listLen = 0;
	BYTE currentLetter;
	BYTE currentNumber;
	BYTE currentRes[3] = { 0, 0, 0 };
	chessPosCell* currentCell;

	FILE* fpChessPosList = fopen(file_name, "wb");
	checkFileOpening(fpChessPosList);

	fwrite(&listLen, sizeof(short), 1, fpChessPosList);

	currentCell = pos_list->head;

	/*goes through the position list. out of every 4 positions in the list each one is handled differently.
	  the way to handle, is marked in the varible 'stage'*/
	while (currentCell != NULL)
	{
		switch (stage)
		{
		case 1:
			currentLetter = currentCell->position[0] - 'A';
			currentNumber = currentCell->position[1] - '1';
			currentLetter = currentLetter << 3;
			currentRes[0] = currentLetter | currentNumber;
			currentRes[0] = currentRes[0] << 2;

			break;
		case 2:
			currentLetter = currentCell->position[0] - 'A';
			currentLetter = currentLetter >> 1;
			currentRes[0] = currentRes[0] | currentLetter;

			currentLetter = currentCell->position[0] - 'A';
			currentNumber = currentCell->position[1] - '1';
			currentLetter = currentLetter << 7;
			currentNumber = currentNumber << 4;
			currentRes[1] = currentLetter | currentNumber;

			break;
		case 3:
			currentLetter = currentCell->position[0] - 'A';
			currentNumber = currentCell->position[1] - '1';
			currentLetter = currentLetter << 1;
			currentRes[1] = currentRes[1] | currentLetter;

			currentNumber = currentNumber >> 2;
			currentRes[1] = currentRes[1] | currentNumber;

			currentNumber = currentCell->position[1] - '1';
			currentNumber = currentNumber << 6;
			currentRes[2] = currentNumber;

			break;
		case 4:
			currentLetter = currentCell->position[0] - 'A';
			currentNumber = currentCell->position[1] - '1';

			currentLetter = currentLetter << 3;
			currentRes[2] = currentRes[2] | currentLetter;
			currentRes[2] = currentRes[2] | currentNumber;

			fwrite(currentRes, sizeof(BYTE), 3, fpChessPosList);
			currentRes[0] = 0;
			currentRes[1] = 0;
			currentRes[2] = 0;

			break;
		}

		stage++;

		if (stage == 5) /*after stage 4, returns to stage 1*/
		{
			stage = 1;
		}

		count++;

		currentCell = currentCell->next;

	}

	stage--; /*in order to add the extra bytes*/
	if (stage == 1)
	{
		fwrite(currentRes, sizeof(BYTE), 1, fpChessPosList);
	}
	else if (stage == 2)
	{
		fwrite(currentRes, sizeof(BYTE), 2, fpChessPosList);
	}
	else /*stage = 3*/
	{
		fwrite(currentRes, sizeof(BYTE), 3, fpChessPosList);
	}

	fseek(fpChessPosList, 0, SEEK_SET);
	fwrite(&count, sizeof(short), 1, fpChessPosList);

	fclose(fpChessPosList);
}

void freeChessPosList(chessPosList* lst) /*free the chessPos list*/
{
	chessPosCell* curr;
	chessPosCell* next;

	if (lst == NULL)
	{
		return;
	}

	curr = lst->head;

	while (curr != NULL)
	{
		next = curr->next;

		free(curr);

		curr = next;
	}

	free(lst);

}