#include <iostream>
#include "stack.h"
using namespace std;


DynIntStack::DynIntStack()
{
	top = NULL; 
}

//Begin : code taken from DynIntStack.cpp and UPDATED
// Member function push pushes the argument onto the stack.                                    *
void DynIntStack::push(int row, int column)
{
	StackNode *newNode;

	// Allocate a new node & store Num
	newNode = new StackNode;
	newNode->row = row;
	newNode->column = column;


	// If there are no nodes in the list
	// make newNode the first node
	if (isEmpty())
	{
		top = newNode;
		newNode->next = NULL;
	}
	else	// Otherwise, insert NewNode before top
	{
		newNode->next = top;
		top = newNode;
	}
}
//End : code taken from DynIntStack.cpp 

//Begin : code taken from DynIntStack.cpp and UPDATED
// Member function pop pops the value at the top of the stack off, and copies it into the variable passed as an argument.
void DynIntStack::pop(int &startrow, int &startcol)
{
	StackNode *temp;

	if (!isEmpty())
	{
		startrow = top->row;
		startcol = top->column;
		temp = top->next;
		delete top;
		top = temp;
	}
}
//End : code taken from DynIntStack.cpp 

//Begin : code taken from DynIntStack.cpp
// Member funciton isEmpty returns true if the stack is empty, or false otherwise.
bool DynIntStack::isEmpty(void)
{
	bool status;

	if (top == NULL)
		status = true;
	else
		status = false;

	return status;
}
//End : code taken from DynIntStack.cpp