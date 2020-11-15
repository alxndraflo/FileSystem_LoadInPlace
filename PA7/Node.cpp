//----------------------------------------------------------------------------
// Copyright 2019, Ed Keenan, all rights reserved.
//----------------------------------------------------------------------------

#include <stdlib.h>

#include "Node.h"

void Node::BlowUp()
{
	memset(this, 0xAB, sizeof(Node));
}

Node::Node()
{
	this->pNext = nullptr;
	this->pPrev = nullptr;
	this->getRandUInt(x);
	this->getRandUInt(y);
	this->getRandUInt(z);
	this->getRandUInt(key);
}

bool Node::operator ==(const Node &n)
{
	return (n.x == this->x && n.y == this->y && n.z == this->z && n.key == this->key);
}

void Node::setNext(Node * p)
{
	this->pNext = p;
}

void Node::setPrev(Node * p)
{
	this->pPrev = p;
}

Node * Node::getNext()
{
	return this->pNext;
}

Node * Node::getPrev()
{
	return this->pPrev;
}

void Node::getRandUInt(unsigned int & var)
{
	int high = rand();
	int low = rand();
	var = (unsigned int)(high << 16 | low);
}

// ---  End of File ---------------
