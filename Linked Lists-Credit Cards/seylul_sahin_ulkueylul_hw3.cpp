//This program stores blacklisted credit cards organized according to their expiration dates and 
//gives the user 6 options such as chronological display, bulk deleting or finding one by their expiration date or card number.

//This program is written by Ulku Eylul Sahin on Mrch 2020.

#include <iostream>
#include <fstream>              // for ifstream
#include <sstream> 
#include <vector>
#include <string>
#include <iomanip>
#include "linkedlist.h"

using namespace std;

bool inputcheck(string cardnumber)	//This function takes the card number as parameter and returns true if it is in right format.
{
	if(cardnumber.length() == 16 )
	{
		for (int i = 0; i < cardnumber.length() ; i++)
		{
			char isdigit = cardnumber.at(i);
			if(isdigit < 48 || isdigit > 57)
				return false;
		}
		return true;
	}
	else
		return false;
}


bool inputcheckDate(int month, int year)	// this function checks if the month user inputs is between 1 and 12.
{
	if(month>0 && month < 13)
		return true;
	else
		return false;
}


int main()
{

	string filename, line, str, cardnumber;
	int month, year;

	cardlist list;

	int option = 0;

	while(option != 6) //terminates when option is 6
	{
		cout << endl << "1) Upload Card(s) from a File" << endl << "2) Display List Chronological" << endl;
		cout <<"3) Display List Reverse Chronological" << endl << "4) Card Search"<< endl;
		cout <<"5) Bulk Delete" << endl << "6) Exit" << endl << "Please choose option from the menu: ";
		cin >> option ;

		if (option == 1)	//opens file and adds the cards to linked lists.
		{
			ifstream input;
			cout << "Please enter file name: " ;
			cin >> filename;
			input.open(filename.c_str());   // open the file

			if (input.fail())	//if cant open file
			{
				cout << "Could not find a file named " << filename << endl;
			}

			else{
				while ( getline(input, line))
				{
					istringstream iss(line);
					iss >> cardnumber >> month >> year;

					list.AddInOrder(month, year, cardnumber);
				}
			}}
		else if (option==2)	//displays list chronological
		{
			list.displaylistchronological();
		}

		else if (option==3)	//displays list reverse chronological
		{
			list.displaylistreversechronological();
		}

		else if(option==4)	//searches by card number
		{

			expirationnode *temp;
			string inputcard;
			cout << "Please enter the credit card number: " ;	//takes credit card number input
			cin >> inputcard;

			if(inputcheck(inputcard) == false)	//input check
			{
				cout << "Invalid format!" << endl;

			}

			else{
				if(list.SearchListCard(inputcard)== NULL)	//searches for the node that card number is in / if card is not found
				{
					cout << "There is no credit card with given credit card number: " << inputcard << endl;
				}
				if (list.SearchListCard(inputcard) != NULL) //if card is found in the linkedlist
				{
					list.cardsearch(inputcard);
				}
			}}

		else if(option==5)	//deletes the nodes with smaller expiration dates than the input expiration date
		{

			int inputmonth, inputyear;
			cout << "Please enter month and year: " ;
			cin >> inputmonth >> inputyear;	//takes expiration date as input

			if(inputcheckDate(inputmonth, inputyear) == false || cin.fail()) //inputcheck
			{
				if(cin.fail())
				{
					cin.clear();
					cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
				}
				cout << "Invalid format!" << endl;

			}

			else{
				list.bulkDelete(inputmonth, inputyear);	//deletes nodes before expiration date
			}
		}
		else if(option == 6)
		{
			list.clearlists(); //in order to prevent memmory leak
			cout << "Terminating!!!"<<endl;
			cout<<"All the nodes have been deleted!" <<endl;

		}
		else if(cin.fail())
		{
			cin.clear();
			cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
			cout << "Invalid format!" << endl;
		}

		else //if not 1,2,3,4,5 or 6
		{
			cout << "Invalid operation!" << endl;

		}
	}
	cin.get();
	cin.get();
	return 0;
}