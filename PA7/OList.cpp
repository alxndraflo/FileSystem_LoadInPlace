//----------------------------------------------------------------------------
// Copyright 2019, Ed Keenan, all rights reserved.
//----------------------------------------------------------------------------

#include <stdio.h>
#include <stdlib.h>
#include <assert.h>

#include "OList.h"
#include "Node.h"
#include "Trace.h"
#include "CustomDestructCommand.h"

#define UNUSED_VAR(x) (void *)x

// ----------------------------------
// -----> MODIFY This FILE <---------
// ----------------------------------

void OList::SetCutoffLength()
{
	// Yes HARD code your cutoff
	// CHANGE this number, by running experiments to find best value
	this->mCutoffLength = 16;
}

void OList::MergeSort()
{
	//Call to private merge sort method
	pMergeSort(&this->pHead);
}

void OList::pMergeSort(Node** origHead)
{
	Node* head = *origHead;
	Node* left = nullptr;
	Node* right = nullptr;

	//Base case
	if ((head == nullptr) || (head->pNext == nullptr))
	{
		return;
	}

	//Split list into left and right side sublists
	pSplitList(head, &left, &right);

	//Recursively sort left and right side sublists
	pMergeSort(&left);
	pMergeSort(&right);

	//Set original head to new sorted list AFTER merge
	*origHead = pMergeLists(left, right);
}

void OList::pSplitList(Node* origHead, Node** left, Node** right)
{
	Node* slow = origHead;
	Node* fast = origHead->pNext;

	//Advance fast(right) side by 2 nodes, and slow(left) side by 1 node
	while (fast != nullptr)
	{
		fast = fast->pNext;

		if (fast != nullptr)
		{
			slow = slow->pNext;
			fast = fast->pNext;
		}
	}

	//Slow is left side, so split after at midpoint
	*left = origHead;
	*right = slow->pNext;
	slow->pNext = nullptr;
}

Node* OList::pMergeLists(Node* left, Node* right)
{
	Node* mergedList = nullptr;

	//Base case 1
	if (left == nullptr)
	{
		return right;
	}
	//Base case 2
	if (right == nullptr)
	{
		return left;
	}

	//Choose left or right side, and recurse
	if (left->key <= right->key)
	{
		mergedList = left;
		mergedList->pNext = pMergeLists(left->pNext, right);
		mergedList->pNext->pPrev = left;
		mergedList->pPrev = nullptr;
	}
	else
	{
		mergedList = right;
		mergedList->pNext = pMergeLists(left, right->pNext);
		mergedList->pNext->pPrev = right;
		mergedList->pPrev = nullptr;
	}

	return mergedList;
}

void OList::InsertionSort()
{
	//Call to private insertion sort method
	pInsertionSort(&this->pHead);
}

void OList::pInsertionSort(Node** head)
{
	Node* sortedList = nullptr;
	Node* current = *head;

	//Walk list and insert into sortedList
	while (current != nullptr) 
	{
		//Save next ptr for next iteration
		Node* next = current->pNext;

		//Remove ptr links
		current->pPrev = current->pNext = nullptr;

		//Insert in sorted order to new sorted list
		pSortedInsert(&sortedList, current);

		//Advance current to next node in list
		current = next;
	}

	//Point the list head to the new sorted list
	*head = sortedList;
}

void OList::pSortedInsert(Node** head, Node* newNode)
{
	Node* current = nullptr;

	// if list is empty 
	if (*head == nullptr)
	{
		*head = newNode;
	}
	else if ((*head)->key >= newNode->key) //if at front of list
	{
		newNode->pNext = *head;
		newNode->pNext->pPrev = newNode;
		*head = newNode;
	}
	else 
	{
		current = *head;

		//find node AFTER one where need to insert
		while (current->pNext != nullptr &&	current->pNext->key < newNode->key)
		{
			current = current->pNext;
		}

		//Fix pointers
		newNode->pNext = current->pNext;

		//If not at end, insert node
		if (current->pNext != nullptr)
		{
			newNode->pNext->pPrev = newNode;
		}

		current->pNext = newNode;
		newNode->pPrev = current;
	}
}

void OList::MergeComboSort(int CutoffLength)
{
	UNUSED_VAR(CutoffLength);

	pComboMergeSort(&this->pHead, this->NumNodes);
}

void OList::pComboMergeSort(Node** origHead, int upperBound)
{
	Node* head = *origHead;
	Node* left = nullptr;
	Node* right = nullptr;

	//Base case
	if ((head == nullptr) || (head->pNext == nullptr))
	{
		return;
	}

	//If list size less than or equal to cutoff length
	if (upperBound <= this->GetCutoffLength())
	{
		//Call insertion sort
		pInsertionSort(&head);
		*origHead = head;
	}
	else
	{
		//Split list into left and right side sublists
		pSplitList(head, &left, &right);

		//Recursively sort left and right side sublists
		pComboMergeSort(&left, upperBound / 2);
		pComboMergeSort(&right, upperBound / 2);
		*origHead = pMergeLists(left, right);
	}

	//Set original head to new sorted list AFTER merge
}


void OList::WriteToFile(const char * const pFileName)
{
	//Create buffer and convert list to contiguous memory
	char* listBuffer = ConvertToContiguous();

	size_t bufferSize = NumNodes * sizeof(Node);

	//Verify filename is not null & open file
	assert(pFileName);
	FILE* pFileHandle = fopen(pFileName, "wb");

	//Write buffer to file
	fwrite(listBuffer, bufferSize, 1, pFileHandle);

	//Close file
	fclose(pFileHandle);

	//Delete buffer
	delete[] listBuffer;
}

OList::OList(const char * const pFileName, int numNodes)
{
	// Leave the next 5 lines...
	this->SetCutoffLength();
	this->pHead = nullptr;
	this->mCutoffLength = this->GetCutoffLength();
	this->NumNodes = numNodes;
	this->privFunctor = nullptr;
	//----------------------------------------------//

	//Create contiguous block of memory
	size_t bufferSize = NumNodes * sizeof(Node);
	char* listBuffer = new char[bufferSize];

	// Verify filename not null & open file
	assert(pFileName);
	FILE* pFileHandle = fopen(pFileName, "rb");

	//Read data from file to buffer
	fread(listBuffer, bufferSize, 1, pFileHandle);

	//Close file
	fclose(pFileHandle);

	//Method to reconstruct linked list
	ReconstructList(listBuffer);
}

char* OList::ConvertToContiguous()
{
	//Create contiguous block of memory
	size_t bufferSize = NumNodes * sizeof(Node);
	char* listBufferContiguous = new char[bufferSize];

	//Set pointers to walk buffer and list
	char* bufferPtr = listBufferContiguous;
	Node* originalList = this->pHead;

	//Cast buffer ptr to Node ptr - to walk list
	Node* current = (Node*)bufferPtr;

	//FIRST NODE
	//Set prev/next ptrs
	current->pPrev = originalList->pPrev;
	current->pNext = (Node*)(bufferPtr - listBufferContiguous + sizeof(Node));

	//Copy data from original list to buffer
	current->x = originalList->x;
	current->y = originalList->y;
	current->z = originalList->z;
	current->key = originalList->key;

	//Advance to next node in list
	originalList = originalList->pNext;

	//Advance buffer pointer to next node address
	bufferPtr += sizeof Node;

	//Copy data from list into buffer (after head)
	while (originalList != nullptr)
	{
		current = (Node*)bufferPtr;

		// Fix pointers relative to buffer
		current->pNext = (Node*)(bufferPtr - listBufferContiguous + sizeof(Node));
		current->pPrev = (Node*)(bufferPtr - listBufferContiguous - sizeof(Node));

		//Copy node data to buffer
		current->x = originalList->x;
		current->y = originalList->y;
		current->z = originalList->z;
		current->key = originalList->key;

		//Advance to next node in list
		originalList = originalList->pNext;

		//Advance buffer pointer to next node address
		bufferPtr += sizeof(Node);
	}

	//Fix next ptr for last node
	current->pNext = nullptr;

	return listBufferContiguous;
}

void OList::ReconstructList(char* buffer)
{
	//Place pHead to first address of buffer
	this->pHead = (Node*)buffer;
	Node* current = this->pHead;

	//Update pointers in new linked list
	while (current->pNext != nullptr)
	{
		current->pNext = (Node*)(buffer + (size_t)current->pNext);
		current->pPrev = (Node*)(buffer + (size_t)current->pPrev);

		//Advance to next node in list
		current = current->pNext;
	}

	//Fix head's prev pointer
	this->pHead->pPrev = nullptr;

	//Fix pointers for last node in list
	current->pPrev = (Node*)(buffer + (size_t)current->pPrev);
	current->pNext = nullptr;
}


// ---  End of File ---------------
