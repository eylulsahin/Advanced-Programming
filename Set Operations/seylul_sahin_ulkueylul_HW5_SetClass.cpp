#include <iostream>
#include <iomanip>
#include <sstream>
using namespace std;

#include "seylul_sahin_ulkueylul_HW5_SetClass.h"


//constructor
IntegerSet::IntegerSet()
{
	size=0;
	intarray = NULL;
}

// constructor with set size
IntegerSet::IntegerSet(int ssize)
{
	intarray = new int[ssize];
	size = ssize;

	for(int i=0; i<size; i++)
	{
		intarray[i] =i;
	}
}

//// destructor
IntegerSet::~IntegerSet()
{
	size = 0;
	delete[] intarray;
}

// copy constructor
IntegerSet::IntegerSet(const IntegerSet & copy)
{
	size = copy.size;
	intarray = new int[size]; // deep copy

	for(int i = 0; i < size; i++)
	{
		intarray[i] = copy.intarray[i];
	}
}

//checks if an element exists in a set
bool IntegerSet::ExistanceCheck(IntegerSet myarray, int element)
{
	for (int i=0 ; i< myarray.size; i++)
	{
		if(myarray.intarray[i]==element)
			return true;
	}
	return false;
}

//returns size from member func
int IntegerSet::GetSize()const
{
	int x = this->size;
	return x;
}

//returns intarray
int* IntegerSet::GetArray()const
{
	return this->intarray;
}

// assignment operator
const IntegerSet& IntegerSet::operator=(const IntegerSet & rhs)
{
	if (this != &rhs) // if they are not already equal
	{
		// first delete left hand side
		size = 0;
		delete[] intarray;

		// create new array for left hand side
		size = rhs.size;
		intarray = new int[size];

		for(int i = 0; i < size; i++)
		{
			int x =rhs.intarray[i];
			intarray[i] = x; // assign content
		}
	}
	return *this;
}

//+= operator
const IntegerSet& IntegerSet::operator +=(const IntegerSet & rhs)
{
	*this = *this + rhs;
	return *this;
}

// + operator
IntegerSet IntegerSet::operator + (const int & rhs)
{
	if(!ExistanceCheck(*this, rhs))
	{
		IntegerSet tempset (size+1);	

		if(this->size==0)
			tempset.intarray[0]= rhs;
		else{
			for(int y=0 ; y< this->size ; y++)
			{
				tempset.intarray[y] = this->intarray[y];

			}
			tempset.intarray[size]=rhs;
		}
		return tempset;
	}
	else
		return *this;
}

//!= operator
bool operator !=  (const IntegerSet& lhs, const IntegerSet& rhs)
{
	int lhssize = lhs.GetSize();
	int rhssize = rhs.GetSize();

	int* lhsarray = lhs.GetArray();
	int* rhsarray = rhs.GetArray();

	bool flag=false;

	if(lhssize != rhssize)	//they are not equal
		return true;

	else{
		for(int i=0 ; i< lhssize ; i++)
		{
			for(int x=0 ; i< rhssize ; i++)	//if all the elemnts are same
			{
				if(lhsarray[i] == rhsarray[x]) 
					flag=true;
			}
			flag=false;
		}
		if(flag == true)	//size and all elements are same, so they are equal
			return true;
	}

	return false;
}

// << operator
ostream&  operator << (ostream & os, const IntegerSet & ct)
{
	int tempsize = ct.GetSize();
	int* temparray = ct.GetArray();

	os << "{";
	for(int x=0 ; x< tempsize ; x++)
	{
		if(x != (tempsize-1))
			os << temparray[x] << ", ";
		else
			os << temparray[x];
	}
	os << "}";
	return os;
}

// * operator
IntegerSet IntegerSet::operator * (const IntegerSet& rhs)
{

	IntegerSet temparray;

	for(int i=0 ; i< this->size ; i++)
	{
		for(int x=0 ; x< rhs.size ; x++)
		{
			if(this->intarray[i] == rhs.intarray[x])
				temparray = temparray + this->intarray[i];
		}
	}
	return temparray;
}

// <= operator
bool operator <= (const int& lhs, const IntegerSet& rhs)
{
	int size1 = rhs.GetSize();
	int* rhsarray = rhs.GetArray();

	for(int i=0 ; i< size1 ; i++)
	{
		if(lhs == rhsarray[i])
			return true;
	}

	return false;
}

// <= operator
bool IntegerSet::operator <=  (const IntegerSet& rhs)
{
	bool flag=false;
	for (int i = 0; i < this->size; i++) 
	{ 
		for (int j = 0; j < rhs.size; j++) 
		{ 
			if(rhs.intarray[i] == this->intarray[j]) 
				flag=true ;
		} 

		// If flag is still false then rhs is not present in lhs 
		if ((this->size == rhs.size) && flag==false) 
			return false; 
	} 
	// If we reach here then all elements of rhs are present in lhs
	return true; 
}

// + operator (union)
IntegerSet IntegerSet::operator + (const IntegerSet & rhs) const
{

	IntegerSet returnset = *this;

	bool flag=false;

	for(int x=0; x< rhs.size ; x++)
	{
		for(int i= 0; i<this->size ; i++)
		{
			if(rhs.intarray[x] == this->intarray[i])
				flag=true;
		}
		if(flag==false)
		{
			returnset= returnset+ rhs.intarray[x];
		}
		flag=false;
	}
	return returnset;
}

