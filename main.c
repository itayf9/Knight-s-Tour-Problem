#include "ChessRules.h"
#include "chessPosList.h"
#include "menu.h"



void main()
{
	int choice = 0;
	bool is3Activated = false;
	chessPos* chosenPosition = NULL;
	pathTree path;
	chessPosList* knightPathList = NULL;

	path.root = NULL;

	getChoice(&choice);

	while (choice != 6) /*handle the option selection operation*/
	{
		switch (choice)
		{
		case 1: /*option 1 was chosen*/
			if (chosenPosition != NULL)
			{
				free(chosenPosition);
			}

			chosenPosition = (chessPos*)(malloc(sizeof(chessPos)));
			checkMemoryAllocation(chosenPosition);

			getStartingPosition(chosenPosition);
			is3Activated = false;

			if (path.root != NULL)
			{
				freePathTree(&path);
				path.root = NULL;
			}

			if (knightPathList != NULL)
			{
				freeChessPosList(knightPathList);
				knightPathList = NULL;
			}

			break;
		case 2: /*option 2 was chosen*/
			createAllPossibleKnightPaths(chosenPosition, &path);

			break;
		case 3: /*option 3 was chosen*/
			findAKnightPathCoversAllBoard(chosenPosition, &path, &knightPathList, &is3Activated);

			break;
		case 4: /*option 4 was chosen*/
			savePathToFile(chosenPosition, &path, &knightPathList, &is3Activated);

			break;
		case 5: /*option 5 was chosen*/
			loadAndDisplayPath();

		default:
			break;
		}

		getChoice(&choice);

	}

	/*option 6 was chosen, therefore exiting the program*/

	free(chosenPosition);
	freePathTree(&path);
	freeChessPosList(knightPathList);

}


