//This program is written by Ulku Eylul Sahin on March 2020.

#include <iostream>
#include <fstream>             
#include <sstream> 
#include <string>
#include <iomanip>
#include "stack.h"
#include <stdlib.h>  

using namespace std;

//input check for row and column
bool inputcheck(string value)	
{
	for (int i = 0; i < value.length() ; i++)
	{
		char isdigit = value.at(i);
		if(isdigit < 48 || isdigit > 57)
			return false;
	}
	if(value.length() == 1 && value.at(0)<51)
		return false;
	else
		return true;
}

//checks if the starting point input is a number or a string
bool isnumber(string sprow, string spcol)
{
	for (int i = 0; i < sprow.length(); i++)
	{
		char isdigit = sprow.at(i);
		if(isdigit < 48 || isdigit > 57)
			return false;
	}

	for (int i = 0; i < spcol.length(); i++)
	{
		char isdigit = spcol.at(i);
		if(isdigit < 48 || isdigit > 57)
			return false;
	}

	return true;
}

//input check for starting point
bool StartPointInputCheck( int row, int column, int startrow, int startcol)
{

	if(startrow>=row || startcol>=column)
		return false;
	else
		return true;
}

//input check for filling character
bool charcheck(char character)
{
	if(character=='x' || character=='X')
		return false;
	else
		return true;
}

//This function traverses the matrix starting from starting point. Replaces spaces in that enclosed area with filling characters.
// traverses by putting the visited cells coordinates in the stack
void iterate (char** matrix,DynIntStack stack, int startrow, int startcol, char fillingchar)
{
	bool flag = true;

	int isstartrow=startrow;
	int isstartcol=startcol;

	while(flag)	
	{
		if(matrix[startrow][startcol]== ' ')				//fills starting point and adds it to stack
		{
			stack.push(startrow, startcol);
			matrix[startrow][startcol]= fillingchar;
		}

		else if(matrix[startrow+1][startcol]== ' ')			//checks the below neighbor cell
		{
			stack.push(startrow+1, startcol);				//add the cell to stack
			matrix[startrow+1][startcol]= fillingchar;		//replace space with filling character
			startrow++;										//update starting row
		}

		else if(matrix[startrow][startcol+1]== ' ')			//checks the right neighbor cell
		{
			stack.push(startrow, startcol+1);
			matrix[startrow][startcol+1]= fillingchar;
			startcol++;
		}

		else if(matrix[startrow-1][startcol]== ' ')			//checks the above neighbor cell
		{
			stack.push(startrow-1, startcol);
			matrix[startrow-1][startcol]= fillingchar;
			startrow--;
		}

		else if(matrix[startrow][startcol-1]== ' ')			//checks the left neighbor cell
		{
			stack.push(startrow, startcol-1);
			matrix[startrow][startcol-1]= fillingchar;
			startcol--;
		}
		

		else if(!stack.isEmpty())	//if doesnt have anywhere else to go and stack is not empty yet
		{
			stack.pop(startrow, startcol);	
		}

		else //when stack is empty
			flag= false;
	}
}

void PrintMatrix(char** matrix, int row, int column)
{
	for (int i = 0; i < row; i++)
	{
		for (int j = 0; j < column; j++)
		{
			cout << matrix[i][j];
		}
		cout << endl;
	}
}

int main()
{
	string row, column;
	string startingpoint, filename;
	ifstream input;

	//Take row input
	cout << "Enter the number of rows: " ;
	cin >> row;
	while(!inputcheck(row))
	{
		cout << row << " is not valid!" << endl;
		cout << "Enter the number of rows: " ;
		cin >> row;
	}

	//Take column input
	cout << "Enter the number of columns: " ;
	cin >> column;
	while(!inputcheck(column))
	{
		cout << column << " is not valid!" << endl;
		cout << "Enter the number of columns: " ;
		cin >> column;
	}

	string line;
	char** matrix ;
	int rows = stoi(row);
	int columns = stoi(column);

	//form matrix 
	matrix = new char* [rows];
	for (int j = 0; j<rows; j++)
	{
		matrix[j] = new char [columns]; 
	}

	//Open file
	cout << "Please enter file name: " ;
	cin >> filename;
	input.open(filename.c_str());   // open the file

	while (input.fail())	//if cant open file
	{
		cout << "Cannot open a file named " << filename << endl;
		cout << "Please enter file name: " ;
		cin >> filename;
		input.open(filename.c_str());   // open the file
	}

	
	for(int i=0; i<rows; i++)
	{
		getline(input, line);
		//put values from the file in the matrix
		string iss(line);
		for(int j=0 ; j<columns; j++)
		{
			matrix[i][j]=iss[j]; 
		}
	}
	string sprow, spcol;
	//take starting point input
	cout << "Enter the starting point: ";
	cin >> sprow >> spcol;

	int startrow=0;
	int startcol=0;

	if(isnumber(sprow, spcol))	//if starting points are numbers
	{
		startrow = stoi(sprow);		//turn strings into integers
		startcol = stoi(spcol);
	}

	while(StartPointInputCheck(rows, columns, startrow, startcol)==false || isnumber(sprow,spcol)==false)
	{
		cout << "Invalid coordinate!" << endl;
		cout << "Enter the starting point: ";
		cin >> sprow >> spcol;

		if(isnumber(sprow, spcol))
		{
			startrow = stoi(sprow);
			startcol = stoi(spcol);
		}
	}

	if(matrix[startrow][startcol]=='x' || matrix[startrow][startcol]=='X')	//if already occupied
	{
		cout << "Starting point is already occupied." << endl << "Terminating...";
	}

	else
	{
		char fillingchar;
		//take filling character input
		cout << "Enter the filling char: ";
		cin >> fillingchar;

		while(!charcheck(fillingchar))
		{
			cout << "Filling char is not valid!"<<endl;
			cout << "Enter the filling char: ";
			cin >> fillingchar;
		}

		DynIntStack stack; 
		//start traversing matrix
		iterate(matrix, stack, startrow, startcol, fillingchar);
		PrintMatrix(matrix, rows, columns);

	}
	return 0;
}
