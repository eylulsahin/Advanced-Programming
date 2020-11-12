/* The aim of this program is to find an enclosed area in a 2D matrix that contains the characters ‘x’s and ‘o’s.
This program is written by Ulku Eylul Sahin on 15.02.2020 */

#include <iostream>
#include <fstream>              // for ifstream
#include <sstream> 
#include <vector>
#include <string>
#include <iomanip>

using namespace std;

void printmatrix(vector<vector<char>> matrix) //This function takes the matrix as a parameter and prints the elements of the matrix
{
	cout << "Input Matrix:" << endl;
	for (int i = 0; i < matrix.size(); i++)
	{
		for (int x = 0; x < matrix[i].size() ; x++)
		{
			cout << matrix[i][x] << " " ;
		}
		cout << endl;
	}
}

bool isvisited(vector<int>&visited, int x, int y)		/*This function checks if the coordinates (integer parameters) are visited 
														 by checking if they are an element of the visited vector*/

{
	for (int i = 0; i < visited.size(); i=i+2)
	{
		if( visited[i]==x && visited[i+1] == y)
			return true;
	}
	return false;
}

void search_enclosedarea(vector<vector<char>> &matrix, int x, int y)	/*This function searches for an enclosed area by character 'x' for the matrix
																		taken as parameter, by starting from the coordinates which are the integer parameters.
																		Then the function prints the path by stating if there is an enclosed path or not. */
{
	char start = matrix[x][y];
	vector<int> visited;  //empty vector to store visited coordinates
	visited.push_back(x);	//add starting point to visited coordinates
	visited.push_back(y);

	int rowcount = matrix.size()-1;
	int colcount = matrix[0].size()-1;
	int startx=x,starty=y;

	if(start == 'o')
	{
		cout << "This cell is not occupied!" << endl;
	}
	else if( start == 'x')
	{
		bool flag = true;

		do
		{
			flag = false;

			if((x <= rowcount) && (y+1 <= colcount) && (x >= 0) && (y+1 >= 0) && (matrix[x][y+1] == start) && !(isvisited(visited, x, y+1)))	//for moving right
			{
				y++;
				visited.push_back(x);
				visited.push_back(y);
				flag = true;
			}
			else if  ( (x+1 <= rowcount) && (y <= colcount) && (x+1 >= 0) && (y >= 0) && (matrix[x+1][y] == start)  && !(isvisited(visited, x+1, y)))	//for moving down
			{
				x++;
				visited.push_back(x);
				visited.push_back(y);
				flag = true;
			}
			else if( (x <= rowcount) && (y-1 <= colcount) && (x >= 0) && (y-1 >= 0) && (matrix[x][y-1] == start) && !(isvisited(visited, x, y-1)))	//for moving left
			{
				y--;
				visited.push_back(x);
				visited.push_back(y);
				flag = true;
			}
			else if ( (x-1 <= rowcount) && (y <= colcount) && (x-1 >= 0) && (y >= 0) && (matrix[x-1][y] == start) &&  !(isvisited(visited, x-1, y)))	//for moving up
			{
				x--;
				visited.push_back(x);
				visited.push_back(y);
				flag = true;
			} 
		}while( !(startx == x && starty == y) && flag);
		
		if (  ((startx == x) && (starty == y)) || ((startx == x+1) && (starty == y)  ||  ((startx == x-1) && (starty == y))  ||  ((startx == x) && (starty == y+1)  ||   ((startx == x) && (starty == y-1))))  )
		{
		flag = true;
		}


		if (flag == true && visited.size()>4 )											/* flag is true means that the coordinates reached back to the starting point,
																									besides that since there are more than 4 coordinates in the visited vector
																									the coordinates forms an enclosed are*/
		{
			cout << "Found an enclosed area. The coordinates of the followed path:" << endl;
			for (int i = 0; i < (visited.size()); i= i+2)
			{
				cout << visited[i] << setw(4) << visited[i+1] << endl;
			}
		}
		else   //flag is false means there aren't any more x's in right up left or downwards.
		{
			cout << "Cannot found an enclosed area starting with given coordinate. The coordinates of the followed path:" << endl;
			for (int i = 0; i < (visited.size()); i= i+2)
			{
				cout << visited[i] << setw(4) << visited[i+1] << endl;
			}
		}
	}

}

bool charcheck(vector<vector<char>> matrix)	//checks if the matrices elements are only consistent of x and o characters
{

	for ( int  x = 0 ; x < matrix.size() ; x++)
	{
		for ( int y = 0 ; y < matrix[x].size() ; y++)
		{
			if (matrix[x][y] != 'o' && matrix[x][y] != 'x')
				return false;
		}
	}
	return true;
}

bool linecheck(vector<vector<char>> matrix)	//checks if the matrices has same amount of characters for each row
{

	int temp = matrix[0].size();
	for (int i = 0; i < matrix.size() ; i++)
	{
		if(temp != matrix[i].size())
			return false;
	}
	return true;
}

int main()
{
	vector<vector<char>> mymatrix;

	ifstream input;
	string filename, element, line;
	char str;

	cout << "Please enter file name: " ;
	cin >> filename;
	input.open(filename.c_str());   // open the file

	while (input.fail())
	{
		cout << "Cannot find a file named " << filename << endl;

		cout << "Please enter file name: " ;
		cin >> filename;
		input.open(filename.c_str());
	}

	int count = 0;

	while ( getline(input, line))
	{
		istringstream iss(line);
		mymatrix.push_back(vector<char>());	
		while (iss >> str)
		{
			mymatrix[count].push_back(str);
		}
		count++;
	}
	if(charcheck(mymatrix) == false)	//check for invalid characters
	{
		cout << filename << "includes invalid char(s)" << endl;
	}
	else if (charcheck(mymatrix) == true)
	{
		if(linecheck(mymatrix) == false)	//checks if every row has same amount of character
		{
			cout << filename << "is invalid matrix, does not contain same amount of char each row!" <<endl;
		}
		else if (linecheck(mymatrix) == true)
		{
			printmatrix(mymatrix);

			int corx =0, cory =0;
			int rowcount = mymatrix.size()-1;
			int colcount = mymatrix[0].size()-1;

			while(!( corx == -1 && cory == -1))	//stop the program when -1 -1 is entered for coordinates
			{
				cout << endl << "Please enter starting coordinates, first row X then column Y:" ; //takes input for coordinates
				cin >> corx >> cory;

				if (cin.fail())	//if an invalid input is given
				{
					cout << "Invalid Coordinates" << endl;
					cin.clear();
					cin.ignore(10000, '\n');
				}
				else if((corx <= rowcount) && (cory <= colcount) && (corx > -1) && (cory > -1))
				{
					search_enclosedarea(mymatrix, corx, cory);
				}
				else if ( (corx != -1) && (cory != -1))
					cout << "Invalid Coordinates" << endl;
			}
		}
		cout << "Terminating...";
	}
	return 0;
}