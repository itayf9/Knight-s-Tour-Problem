#include "ChessRules.h"
#include "chessPosList.h"
#include "menu.h"



void printMenu() /*prints the menu to the user*/
{
	printf("\n");

	printf("Please enter your choice:\n");
	printf("1. Enter a knight's starting position\n2. Create all possible knight paths\n3. Find a knight path covering all board\n4. Save knight path covering all board to file\n5. Load and display path from file\n6. Exit\n");

	
}



void getChoice(int* choice) /*gets the user's choice*/
{
	int valid;

	printMenu();

	valid = scanf("%d", choice);

	while (valid == 0 || (*choice) < 1 || (*choice) > 6)
	{
		system("cls");
		printf("Error. Please enter a valid option (1-6) \n");
		printMenu();
		while (getchar() != '\n') /*gets rid of the characters up to '\n'*/
		{
		}
		valid = scanf("%d", choice);
	}

	system("cls"); /*clear screen*/
}



void getStartingPosition(chessPos* chosenPosition) /*gets the starting position from the user*/
{
	chessPos temp;

	printf("Please enter the position you wish to work with: \n");

	scanf(" %c %c", &(temp[0]), &(temp[1]));
	(*chosenPosition)[0] = temp[0];
	(*chosenPosition)[1] = temp[1];


	while ((*chosenPosition)[0] < 'A' || (*chosenPosition)[0] > ('A' + BOARD_SIZE - 1) || (*chosenPosition)[1] < '1' || (*chosenPosition)[1] > ('1' + BOARD_SIZE - 1))
	{
		printf("Not a valid position!! Please enter a position (A - %c) and (1 - %d) : \n", BOARD_SIZE + 'A' - 1, BOARD_SIZE);
		scanf(" %c %c", &(temp[0]), &(temp[1]));
		(*chosenPosition)[0] = temp[0];
		(*chosenPosition)[1] = temp[1];
	}
}



void createAllPossibleKnightPaths(chessPos* chosenPosition, pathTree* path) /*creates the path tree from the user's chosen position*/
{
	if (chosenPosition == NULL)
	{
		printf("Please Enter a starting position first (option 1). \n");
	}
	else
	{
		if (path->root != NULL)
		{
			freePathTree(path);
			path->root = NULL;
		}

		*path = findAllPossibleKnightPaths(chosenPosition);
	}
}



void findAKnightPathCoversAllBoard(chessPos* chosenPosition, pathTree* path, chessPosList** knightPathList, bool* is3Activated) /*find a knight path that covers all board from the chosen position*/
{
	if (chosenPosition == NULL) /*the user didn't chose a position*/
	{
		printf("Please Enter a starting position first (option 1). \n");
		return;
	}
	else if (path->root == NULL) /*the user didn't activated case 2*/
	{
		createAllPossibleKnightPaths(chosenPosition, path);
	}

	*knightPathList = findKnightPathCoveringAllBoard(path);

	if (*knightPathList == NULL) /*no path that covers all board*/
	{
		printf("There is no path that is covering all board.\n");
	}

	*is3Activated = true;
}



void savePathToFile(chessPos* chosenPosition, pathTree* path, chessPosList** knightPathList, bool* is3Activated) /*saves the path from case 4 to a binary file*/
{
	char* fileName;

	if (chosenPosition == NULL) /*the user didn't chose a position*/
	{
		printf("Please Enter a starting position first (option 1). \n");
		return;
	}
	else if (!(*is3Activated)) /*the user didn't activated case 3*/
	{
		findAKnightPathCoversAllBoard(chosenPosition, path, knightPathList, is3Activated);

		if (*knightPathList == NULL) /*there is no path that is covering all board*/
		{
			return;
		}
	}

	fileName = getFileName();

	if (*knightPathList == NULL) /*there is no path that covering all board*/
	{
		printf("There is no path that is covering all board.\n");
	}
	else /*there is a path thats covering all board*/
	{
		saveListToBinFile(fileName, *knightPathList); 
	}
}



void loadAndDisplayPath() /*load a file and chack if the path there is valid, and display the valid path from the file.*/
{
	int res;
	char* fileName;

	fileName = getFileName();

	res = checkAndDisplayPathFromFile(fileName);

	switch (res)
	{
	case -1:
		printf("The file does not exist.\n");

		break;
	case 1:
		printf("The knight path is not valid.\n");

		break;
	case 2:
		printf("The knight path is covering all board.\n");

		break;
	case 3:
		printf("The knight path is not covering all board.\n");

		break;
	}
}



char* getFileName() /*gets the name of the file from the user*/
{
	int count = 0;
	int strLen = 1;
	char ch;

	char* str = (char*)malloc(sizeof(char) * strLen);
	checkMemoryAllocation(str);

	if (str == NULL)
	{
		printf("memmory allocation failed");
		exit(1);
	}

	getchar(); /*get rid of '\n'*/

	printf("Please enter file name: \n");

	while (1)
	{
		ch = getchar();

		if (ch == '\n')
		{
			break;
		}

		count++;
		if (count >= strLen)
		{
			strLen++;

			str = (char*)realloc(str, sizeof(char) * (strLen));
			checkMemoryAllocation(str);
		}
		str[count - 1] = ch;
	}

	str[count] = '\0';


	return str;



}



void printBoard() /*prints a board*/
{
	int i, j;

	printLine();

	for (i = 0; i <= BOARD_SIZE; i++)
	{
		if (i == 0)
		{
			printf("|");

			for (j = 0; j <= BOARD_SIZE; j++)
			{
				if (j == 0)
				{
					printf("    |");
				}
				else
				{
					printf("  %d |", j);
				}
			}
		}
		else
		{
			printf("|");

			for (j = 0; j <= BOARD_SIZE; j++)
			{
				if (j == 0)
				{
					printf("  %c |", i - 1 + 'A');
				}
				else
				{
					printf("    |");
				}
			}
		}
		printf("\n");
		printLine();
	}
}



void printLine() /*prints the template of the board lines, depanding on the board size*/
{
	int i;

	printf("+----+");
	for (i = 0; i < BOARD_SIZE; i++)
	{
		printf("----+");
	}
	printf("\n");


}



void gotoxy(int x, int y) /*sets the cursor, to the coordinate (x,y) on the screen*/
{
	printf("\x1b[%d;%df", x + 1, y + 1);
}



void checkMemoryAllocation(void* ptr) /* check if the memory allocated successfully*/
{
	if (ptr == NULL)
	{
		printf("A memory allocation error has been detected");
		exit(1);
	}
}



void checkFileOpening(FILE* fp) /*check if the file opens successfully */
{
	if (fp == NULL)
	{
		printf("couldn't open this file");
		exit(1);
	}
}
