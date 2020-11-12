#ifndef _DOUBLYLINKEDLIST_H
#define _DOUBLYLINKEDLIST_H
#include <string>
using namespace std;

struct creditcardnode
{
    string creditcardno;
    creditcardnode * next ;
};


struct expirationnode {
    int month, year ;
    creditcardnode * cHead ;
	expirationnode * next;
    expirationnode * prev ;
} ;

class cardlist
{
private:
    expirationnode *head;        //Head node, start of LinkedList
    expirationnode *tail;        //Tail node, end of LinkedList

public:
    cardlist();            //Constructor
    
    void AddInOrder(int month, int year, string creditcardno  );
    void displaylistchronological();
    void displaylistreversechronological();
    void cardsearch(string creditcardno);
    void bulkDelete (int month, int year);
    void deleteall() ;
	expirationnode* searchlist(int month, int year);
	expirationnode* SearchListCard(string cardnumber);
	void addinorderoneway(expirationnode* noddy, string cardno);
	void DeleteOneNode(int month, int year);
	void clearlists();
};


#endif