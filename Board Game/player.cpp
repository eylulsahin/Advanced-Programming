#include <iostream>
#include "player.h"

using namespace std;

Player:: Player(Board& Board, char id, int directionp)
	:board(Board), player(id), direction(directionp)
{
	row = 0;
	col = 0;
}

void Player::move(int amount)
{
	int count =0;
	while(count!=amount)
	{
		if(direction==0)	//counterclockwise
		{
			if(col==5)
			{
				if(row==0) 
					col--;
				else if(row==1)
					row--;
			}

			else if(col==0)
			{
				if(row==0)
					row++;
				else if(row==1)
					col++;
			}
			else
			{
				if(row==0)
					col--;
				else if(row==1)
					col++;
			}
			count++;
		}
		else if(direction==1)	//clockwise
		{
			if(col==5)
			{
				if(row==0)
					row++;
				else if(row==1)
					col--;
			}

			else if(col==0)
			{
				if(row==0)
					col++;
				else if(row==1)
					row--;
			}
			else
			{
				if(row==0)
					col++;
				else if(row==1)
					col--;
			}
			count++;
		}
	}
}

void Player::claimOwnership()
{
	if(board.getOwner(row, col)=='-')
		board.setOwner(row, col , player);
}

bool Player::wins()
{
	if(board.countOwnedCell(player) == 7)	//wins when occupies 7 cells
		return true;
	else
		return false;
}

int Player::getRow()
{
	return row;
}

int Player::getCol()
{
	return col;
}
