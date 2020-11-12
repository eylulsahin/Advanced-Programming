#include <string>
#include "board.h"

using namespace std;

class Player
{
private:

	char player;
	int direction;
	int row;
	int col;
	Board& board;

public:

	Player:: Player(Board& myBoard, char id, int directionp);	 //constructor

	void move(int);
	void claimOwnership();
	bool wins();
	int getRow();
	int getCol();
};