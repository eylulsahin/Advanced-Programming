#ifndef BOARD
#define BOARD
#include <string>

using namespace std;

class Board
{
private:
	char theBoard[2][6];
public:
	Board();
	void displayBoard();
	char getOwner(int,int);
	void setOwner(int,int,char);
	bool isFull();
	int countOwnedCell(char);
};
#endif