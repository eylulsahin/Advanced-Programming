struct StackNode
{
	int row;
	int column;
	StackNode *next;
};

class DynIntStack
{
private:
	StackNode *top;

public:
	DynIntStack(void);
	void push(int, int);
	void pop(int &, int &);
	bool isEmpty(void);
};