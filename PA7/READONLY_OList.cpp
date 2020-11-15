//----------------------------------------------------------------------------
// Copyright 2019, Ed Keenan, all rights reserved.
//----------------------------------------------------------------------------

#include <stdio.h>
#include <stdlib.h>
#include <assert.h>

#include "OList.h"
#include "Node.h"
#include "Trace.h"

#define UNUSED_VAR(x) (void *)x


void OList::privCreateLinkedList(int numNodes)
{
	this->SetCutoffLength();

	// initialize it NULL
	this->pHead = nullptr;
	this->NumNodes = numNodes;
	this->mCutoffLength = this->GetCutoffLength();
	this->privFunctor = nullptr;

	// Reset the seed
	// NO-ONE should ever call this function
	// it is here to insure that everyone's seed is the same.
	// Do not change or recall srand anywhere
	srand(2017);

	// create the nodes
	Node *pCurr = new Node();
	pCurr->setPrev(nullptr);
	this->pHead = pCurr;
	Node *pPrev = pCurr;

	// initialize the all nodes
	for (int i = 0; i < this->NumNodes - 1; ++i)
	{
		pCurr = new Node();

		// Update links
		pCurr->setPrev(pPrev);

		if (pPrev != nullptr)
		{
			pPrev->setNext(pCurr);
		}

		pPrev = pCurr;
	}

	// last node
	pCurr->setNext(nullptr);

}

int OList::GetCutoffLength()
{
	return this->mCutoffLength;
}

bool OList::VerifySortOrder(const OList * const pList)
{
	bool Result = false;

	// Don't crash 
	if (pList == nullptr )
	{
		return false;
	}

	Node *pTmp = pList->pHead;
	Node *pTmpPrev = nullptr;
	unsigned int prevKey = 0;
	int count = 0;

	// Loop forward through the list
	while (pTmp != nullptr )
	{
		//Trace::out("%i) %x\n", count, pTmp->key);
		count++;
		pTmpPrev = pTmp;

		// is this the node?
		if (pTmp->key > prevKey)
		{
			// Good keep going
			Result = true;
		}
		else
		{
			// yes error, then break
			Result = false;
			break;
		}

		// go to next
		pTmp = pTmp->pNext;
	
		// Quick test
		if (pTmp != nullptr )
		{
			// Check back pointers
			if (pTmpPrev != pTmp->pPrev)
			{
				// yes error, then break
				Result = false;
				break;
			}
		}
	}

	// Better be at the end
	if (count != pList->NumNodes)
	{
		return false;
	}
	
	// Now move backwards through the list
	pTmp = pTmpPrev;

	pTmpPrev = nullptr;
	prevKey = pTmp->key + 1;
	count = 0;

	// Loop forward through the list
	while (pTmp != nullptr)
	{
		//Trace::out("%i) %x\n", count, pTmp->key);
		count++;
		pTmpPrev = pTmp;

		// is this the node?
		if (pTmp->key < prevKey)
		{
			// Good keep going
			Result = true;
		}
		else
		{
			// yes error, then break
			Result = false;
			break;
		}

		// go to prev
		pTmp = pTmp->pPrev;

		// Quick test
		if (pTmp != nullptr)
		{
			// Check back pointers
			if (pTmpPrev != pTmp->pNext)
			{
				// yes error, then break
				Result = false;
				break;
			}
		}
	}

	// Better be at the beginning
	if (count != pList->NumNodes)
	{
		return false;
	}

	return Result;
}

bool OList::Verify(const OList *pNew, const OList * const pOld)
{
	bool Result = false;

	// Don't crash 
	if (pNew == nullptr || pOld == nullptr)
	{
		return false;
	}

	Node *pTmp = pOld->pHead;
	Node *pTmp2 = pNew->pHead;

	Node *pTmpOld = nullptr;
	Node *pTmp2Old = nullptr;

	unsigned int count = 0;

	// Loop until you find a node
	while (pTmp != nullptr && pTmp2 != nullptr)
	{
		count++;

		// keep old
		pTmpOld = pTmp;
		pTmp2Old = pTmp2;

		// is this the node?
		if (*pTmp == *pTmp2)
		{
			// Good keep going
			Result = true;
		}
		else
		{
			// yes error, then break
			Result = false;
			break;
		}

		// go to next
		pTmp = pTmp->pNext;
		pTmp2 = pTmp2->pNext;

		// Quick test
		if (pTmp != nullptr && pTmp2 != nullptr)
		{
			// Check back pointers
			if (pTmpOld != pTmp->pPrev)
			{
				// yes error, then break
				Result = false;
				break;
			}

			if (pTmp2Old != pTmp2->pPrev)
			{
				// yes error, then break
				Result = false;
				break;
			}
		}
	}

	pTmp = pTmpOld;
	pTmp2 = pTmp2Old;

	// Loop until you find a node from End to beginning
	while (pTmp != nullptr && pTmp2 != nullptr)
	{
		count++;

		// keep old
		pTmpOld = pTmp;
		pTmp2Old = pTmp2;

		// is this the node?
		if (*pTmp == *pTmp2)
		{
			// Good keep going
			Result = true;
		}
		else
		{
			// yes error, then break
			Result = false;
			break;
		}

		// go to next
		pTmp = pTmp->pPrev;
		pTmp2 = pTmp2->pPrev;

		// Quick test
		if (pTmp != nullptr && pTmp2 != nullptr)
		{
			// Check back pointers
			if (pTmpOld != pTmp->pNext)
			{
				// yes error, then break
				Result = false;
				break;
			}

			if (pTmp2Old != pTmp2->pNext)
			{
				// yes error, then break
				Result = false;
				break;
			}
		}
	}

	//total count
	if (count != 50000)
	{
		Result = false;
	}

	return Result;
}

Node *OList::privGetListHead()
{
	return pHead;
}

bool OList::FindKey(unsigned int key, Node &foundNode)
{
	bool foundFlag(false);

	Node *p = OList::privGetListHead();
	
	// Loop until you find a node
	while( p != nullptr )
	{
		// is this the node?
		if( p->key == key)
		{
			// yes, then break
			foundFlag = true;
			break;
		}

		// go to next
		p = p->pNext;
	}

	// return the node reference that contains the key
	if (foundFlag)
	{
		foundNode = *p;
	}

	// flag
	return foundFlag;
}

OList::OList(int numNodes)
{
	this->privCreateLinkedList(numNodes);
}

OList::~OList()
{
	assert(privFunctor != nullptr);
	// Call the Function
	this->privFunctor->Command();
}

void OList::SetDestructCommand(DestructCommand *pFunctor)
{
	assert(pFunctor != nullptr);
	this->privFunctor = pFunctor;
}

Node *OList::GetHead()
{
	assert(this->pHead != nullptr);
	return this->pHead;
}

void OList::SetHead(Node *pNode)
{
	this->pHead = pNode;
}

// ---  End of File ---------------
