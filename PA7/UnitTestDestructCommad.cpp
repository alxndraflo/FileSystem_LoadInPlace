//----------------------------------------------------------------------------
// Copyright 2019, Ed Keenan, all rights reserved.
//----------------------------------------------------------------------------

#include "Framework.h"

#include "UnitTestDestructCommand.h"
#include "OList.h"

UnitTestDestructCommand::UnitTestDestructCommand(OList *pInList)
{
	assert(pInList != nullptr);
	this->pList = pInList;
}

// This function is called in the destructor
// Use this as a reference when you create your own functor
void UnitTestDestructCommand::Command()
{
	// LOAD from RAM: used in unit tests 0-5
	assert(this->pList != nullptr);

	Node *pTmp = this->pList->GetHead();
	Node *pNode = nullptr;
	while (pTmp != nullptr)
	{
		pNode = pTmp;
		pTmp = pTmp->getNext();

		// Make sure the data is scrambled before delete
		pNode->BlowUp();
		delete pNode;
	}

	this->pList->SetHead(nullptr);
}

// End of File
