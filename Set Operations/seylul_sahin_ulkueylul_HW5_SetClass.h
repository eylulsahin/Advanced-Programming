#ifndef INTEGERSET_H
#define INTEGERSET_H
#include <string> 

using namespace std;

class IntegerSet
{
public:
	IntegerSet();	 // empty constructor
	IntegerSet(int);	// constructor with set size
	IntegerSet(const IntegerSet &); // copy constructor
	~IntegerSet();	//destructor

	const IntegerSet& operator = (const IntegerSet& rhs); 
	const IntegerSet& operator +=(const IntegerSet & rhs);
	IntegerSet operator + (const IntegerSet & rhs)const;	
	IntegerSet operator + ( const int & rhs);							
	IntegerSet operator *   (const IntegerSet& rhs);					
	bool operator <=  (const IntegerSet& rhs);						

	int *GetArray()const;
	int GetSize()const;
	bool ExistanceCheck(IntegerSet, int);								

private:
	int size;           //number of elements  
	int *intarray;      //array

};

// free functions
ostream&  operator << (ostream & os, const IntegerSet & ct);
bool operator <=  (const int& lhs, const IntegerSet& rhs);	
bool operator !=  (const IntegerSet& lhs, const IntegerSet& rhs);						


#endif