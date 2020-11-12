#include <iostream>
#include "board.h"

using namespace std;


// constructor
Board::Board()
{
	for (int i = 0; i<2; i++)
	{
		for (int j = 0; j <6 ; j++)
		{
			theBoard[i][j]='-';
		}
	}
}

void Board::displayBoard()	//prints board
{
	for (int i = 0; i< 2; i++)
	{
		for (int j = 0; j <6 ; j++)
		{
			cout << theBoard[i][j] << " ";
		}
		cout << endl;
	}
}

char Board::getOwner(int row, int col)	//returns owner cell
{
	return theBoard[row][col];
}

void Board::setOwner(int row, int col, char owner)
{
	theBoard[row][col]=owner;
}

bool Board::isFull()
{
	for (int i = 0; i< 2; i++)
	{
		for (int j = 0; j <6 ; j++)
		{
			if(theBoard[i][j]=='-')
				return false;
		}
	}
	return true;		//returns true if board is full
}

int Board::countOwnedCell(char owner)	//returns amount of owner char in board
{
	int count=0;

	for (int i = 0; i< 2; i++)
	{
		for (int j = 0; j <6 ; j++)
		{
			if(theBoard[i][j]==owner)
				count++;
		}
	}
	
	return count;
	
}

