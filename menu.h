#ifndef MENU_H

#define MENU_H

typedef unsigned char BYTE;

void printMenu(); /*prints the menu to the user*/
void getChoice(int* choice); /*gets the user's choice*/
void getStartingPosition(chessPos* chosenPosition); /*gets the starting position from the user*/
void createAllPossibleKnightPaths(chessPos* chosenPosition, pathTree* path); /*creates the path tree from the user's chosen position*/
void findAKnightPathCoversAllBoard(chessPos* chosenPosition, pathTree* path, chessPosList** knightPathList, bool* is3Activated); /*find a knight path that covers all board from the chosen position*/
void savePathToFile(chessPos* chosenPosition, pathTree* path, chessPosList** knightPathList, bool* is3Activated);/*saves the path from case 4 to a binary file*/
void loadAndDisplayPath(); /*load a file and chack if the path there is valid, and display the valid path from the file.*/
char* getFileName();/*gets the name of the file from the user*/

void printBoard(); /*prints a board*/
void printLine(); /*prints the template of the board lines, depanding on the board size*/
void gotoxy(int x, int y); /*sets the cursor, to the coordinate (x,y) on the screen*/

void checkMemoryAllocation(void* ptr); /*check if the memory allocated successfully*/
void checkFileOpening(FILE* fp); /*check if the file opens successfully*/

#endif