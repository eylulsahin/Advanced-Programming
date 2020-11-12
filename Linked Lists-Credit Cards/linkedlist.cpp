#include "linkedlist.h"
#include <iostream>
#include <iomanip>

cardlist::cardlist()
{
	head = NULL;
	tail = NULL;
}

/* Begin: code taken from ptrfunc.cpp */ //and UPDATED for doubly linkedlist
void cardlist::AddInOrder(int month, int year, string cardno)
{
	expirationnode *  ptr = head;   // loop variable

	expirationnode *dummy=searchlist(month, year);
	if( dummy == NULL)	//if node with given expiration date doesnt exist
	{
		// if new node should be first, handle this case and return  
		// in this case, we return the address of new node since it is new head  
		if ((head == NULL) || (year < head->year) || (year == head->year && month < head->month))        //MODIFIED 
		{   
			expirationnode * temp = new expirationnode;  //node to be inserted 
			temp->year = year;
			temp->month = month;

			temp->cHead = NULL;
			addinorderoneway(temp, cardno);	//add the cards numbers to inner singly linked list
			temp->next = head; //connect the rest

			if(head==NULL)
				tail = temp;
			head = temp;
			temp->prev = NULL;
			if(head->next != NULL)
				temp->next->prev = temp;


			cout << cardno << " " << month << " " << year << ": added to a new expiration date node" << endl;
			return;

		}

		// check node one ahead so we don't pass!
		while (ptr->next != NULL && ((ptr->next->year < year) || (ptr->next->month < month && ptr->next->year == year)))
		{   
			ptr = ptr->next;
		} // postcondition: new node to be inserted just after the node that ptr points

		//now insert node with month and year after where ptr points to
		expirationnode * temp = new expirationnode;  //node to be inserted 
		temp->month = month;
		temp->year = year;
		temp->cHead = NULL;
		addinorderoneway(temp, cardno);
		temp->next = ptr->next; //connect the rest
		ptr->next = temp;
		temp->prev = ptr;
		if(temp->next != NULL)
			temp->next->prev = temp;
		else
			tail = tail->next;

		cout << cardno << " " << month << " " << year << " :added to a new expiration date node" << endl;
	}
	else 
	{
		if(SearchListCard(cardno)==false)	
		{
			addinorderoneway(dummy, cardno);
			cout <<cardno << " " << month << " " << year << " inserted to an existing expiration date node" << endl;
		}
		else //if node with given cardnumber already exists
			cout << cardno <<  " " << month << " " << year << " this card was already inserted" << endl;
	}
}
/* End: code taken from ptrfunc.cpp */

/* Begin: code taken from ptrfunc.cpp */ //and UPDATED
void cardlist::displaylistchronological ()
{
	;
	expirationnode * ptr = head;
	if(ptr == NULL)
		cout <<"List is empty!" <<endl;
	while (ptr != NULL) 
	{
		cout <<"Expiration Date: "<< ptr ->month << " " << ptr->year <<endl;
		creditcardnode* cardnodes=ptr->cHead;
		int count = 1;
		while(cardnodes!=NULL)
		{
			cout << count << ")" << cardnodes->creditcardno << endl;
			cardnodes=cardnodes->next;
			count++;
		}
		ptr = ptr->next;
		cout << "-------------------" <<endl;
	}

}
/* End: code taken from ptrfunc.cpp */

/* Begin: code taken from ptrfunc.cpp */ //and UPDATED for reverse printing
void cardlist::displaylistreversechronological ()
{
	expirationnode * ptr = tail;	//difference is start from tail instead of head this time
	if(ptr == NULL)
		cout <<"List is empty!" <<endl;
	while (ptr != NULL) 
	{
		cout <<"Expiration Date: "<< ptr ->month << " " << ptr->year <<endl;
		creditcardnode* cardnodes=ptr->cHead;
		while(cardnodes!=NULL)
		{
			cout <<"cardno is" << cardnodes->creditcardno << endl;
			cardnodes=cardnodes->next;
		}
		ptr = ptr->prev;
		cout << "-------------------" <<endl;
	}
}


/* Begin: code taken from ptrfunc.cpp */  //and UPDATED
expirationnode* cardlist::searchlist(int month, int year)	//Searches the list for a value and returns true or false
{
	expirationnode *temp = head;
	while (temp != NULL)
	{
		if((temp->year == year) && (temp->month == month)) //If the node with the given ID is found
			return temp;			
		temp = temp->next;
	}
	//If the code proceeds from here, it means that the whole list is traversed 
	//and a node with ID == searchValue could not be found. 
	return NULL;
}
/* End: code taken from ptrfunc.cpp */

///* Begin: code taken from ptrfunc.cpp */ //and UPDATED
expirationnode* cardlist::SearchListCard(string cardnumber)		//searches the list by card number and return the node with the wanted card number.
{
	expirationnode *temp;
	temp= head;
	while (temp != NULL)
	{

		creditcardnode *ptr;
		ptr= temp->cHead;

		while(ptr!= NULL)
		{
			if(ptr->creditcardno == cardnumber)
				return temp;	//returns the node with given cardnumber
			ptr = ptr->next;
		}

		temp = temp->next;
	}
	return NULL;
}

///* End: code taken from ptrfunc.cpp */

///* Begin: code taken from ptrfunc.cpp */ //and UPDATED
void cardlist::cardsearch(string cardnumber)		//searches the list by card number and return the node with the wanted card number.
{
	expirationnode *temp;
	temp= head;
	while (temp != NULL)
	{

		creditcardnode *ptr;
		ptr= temp->cHead;

		while(ptr!= NULL)
		{
			if(ptr->creditcardno == cardnumber)
			{
				cout << "There exists a credit card given number " << cardnumber;
				cout <<" with expiration date: " << temp->month << " " << temp->year << endl << endl;
			}
			ptr = ptr->next;
		}
		temp = temp->next;
	}
}

///* End: code taken from ptrfunc.cpp */

/* Begin: code taken from ptrfunc.cpp */ //and UPDATED for deleting all nodes exp date smaller than the given exp date
void cardlist::bulkDelete (int month, int year)
{

	expirationnode* ptr = head;

	while ((ptr != NULL) && (ptr->year < year || (ptr->month < month && ptr->year == year)))
	{
		creditcardnode*p = ptr->cHead;

		cout << "Node with expiration date " << ptr->month << " " << ptr->year << " and the following credit cards have been deleted!" << endl;
		int counter=1;
		while(p!=NULL)
		{
			creditcardnode *dummy = p;

			cout << counter << ")" << p->creditcardno << endl;
			counter++;
			if(p->next != NULL) //bidaha bak
			{
				dummy= p->next;			
				delete p;
				p = dummy;
			}
			else
			{
				delete p;
				p= NULL;
			}
		}
		DeleteOneNode(ptr->month, ptr->year);
		ptr = head;
	}
}
/* End: code taken from ptrfunc.cpp */
/* Begin: code taken from ptrfunc.cpp */ //and UPDATED
void cardlist::DeleteOneNode (int month, int year)
	/* pre: toBeDeleted points to the node to be deleted from the list
	post: deletes the node pointed by toBeDeleted, updates head if changes */
{
	expirationnode *toBeDeleted = searchlist(month, year);
	expirationnode * ptr;


	if(toBeDeleted==tail)
	{
		delete toBeDeleted;
		head= NULL;
		tail = NULL;
	}
	else if (toBeDeleted == head)  //if the node to be deleted is the first node
	{
		if(head->next != NULL) 
			head = head->next;
		delete toBeDeleted;
		head->prev = NULL;
	}
	else  //if the node to be deleted is in the middle or at the end
	{
		ptr = head;
		while (ptr->next != toBeDeleted)
			ptr = ptr->next;
		if(toBeDeleted == tail)
			tail = tail->prev;

		//connect the previous node to the next node and delete
		ptr->next = toBeDeleted->next;
		delete toBeDeleted;
	}
}
/* End: code taken from ptrfunc.cpp */
/* Begin: code taken from ptrfunc.cpp */ //and UPDATED for adding cardsnumbers to single linkedlist
void cardlist::addinorderoneway(expirationnode * noddy, string cardno)

{
	creditcardnode*  ptr = noddy->cHead;   // loop variable

	// if new node should be first, handle this case and return  
	// in this case, we return the address of new node since it is new head  
	if ((noddy->cHead == NULL) || (cardno < noddy->cHead->creditcardno))        //MODIFIED 
	{   
		creditcardnode * temp = new creditcardnode;  //node to be inserted 
		temp->creditcardno = cardno;
		temp->next = noddy->cHead;
		noddy->cHead = temp; //connect the rest

		return ;	//return new node

	}

	// check node one ahead so we don't pass!
	while (ptr->next != NULL && (ptr->next->creditcardno < cardno))
	{   
		ptr = ptr->next;
	} // postcondition: new node to be inserted just after the node that ptr points

	//now insert node with month and year after where ptr points to
	creditcardnode * temp = new creditcardnode;  //node to be inserted 
	temp->creditcardno = cardno;

	temp->next = ptr->next;
	ptr->next = temp; //connect the rest
}
/* End: code taken from ptrfunc.cpp */
/* Begin: code taken from ptrfunc.cpp */ //and UPDATED
void cardlist::clearlists()
{
	expirationnode * bigger; //delete linked list in order to prevent memmory leak
	creditcardnode *inner = NULL;

	bigger = head;
	while(bigger != NULL)
	{
		inner = head->cHead;
		while(inner != NULL)
		{
			inner = head->cHead->next;
			delete bigger->cHead;
			bigger->cHead = inner;
		}
		bigger= head->next;
		delete head;
		head = bigger;
	}
	head = NULL;
	tail=NULL;
}
/* End: code taken from ptrfunc.cpp */