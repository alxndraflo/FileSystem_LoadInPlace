//----------------------------------------------------------------------------
// Copyright 2019, Ed Keenan, all rights reserved.
//----------------------------------------------------------------------------

#ifndef NODE_H
#define NODE_H

class Node
{
public:
	Node();
	Node(const Node &) = default;
	Node & operator = (const Node &) = default;
	~Node() = default;

	bool operator ==(const Node &);

	void setNext(Node *p);
	void setPrev(Node *p);
	Node * getNext();
	Node * getPrev();

	void BlowUp();

private:
	void getRandUInt(unsigned int & var);

public:
	Node	*pNext;
	Node	*pPrev;
	unsigned int x;
	unsigned int y;
	unsigned int z;
	unsigned int key;
};

#endif 

// ---  End of File ---------------
