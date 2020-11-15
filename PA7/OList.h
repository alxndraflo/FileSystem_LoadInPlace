//----------------------------------------------------------------------------
// Copyright 2019, Ed Keenan, all rights reserved.
//----------------------------------------------------------------------------

#ifndef OLIST_H
#define OLIST_H

#include "Node.h"
#include "DestructCommand.h"


class OList
{
public:
	// specialization
	OList(int numNodes);

	// Big four
	OList() = delete;
	~OList();
	OList(const OList &) = delete;
	OList & operator = (const OList &) = delete;

	// Destructors
	void SetDestructCommand( DestructCommand *pFunctor );

	// Accessors
	Node *GetHead();
	void SetHead(Node *pNode);

	// Class methods
	int GetCutoffLength();
	bool FindKey(unsigned int key, Node &foundNode);

	// Static Methods

	static bool Verify(const OList *const pNew, const OList * const pOld);
	static bool VerifySortOrder(const OList *const pList);

	//---------------------------------------------------------------------------------------
	// Please implement(rework) these methods (add additional methods to help if you want)
	//---------------------------------------------------------------------------------------
		
		void SetCutoffLength();
		OList(const char * const pFileName, int numNodes);
		void WriteToFile(const char * const pFileName);

		void InsertionSort();
		void MergeSort();
		void MergeComboSort(int CutoffLength);

private: 

	// methods
	void privCreateLinkedList(int numNodes);
	Node *privGetListHead();

	//load in place methods
	char* ConvertToContiguous();
	void ReconstructList(char* buffer);

	//sort methods
	void pInsertionSort(Node** head);
	void pSortedInsert(Node** head, Node* newNode);

	void pMergeSort(Node** head);
	void pSplitList(Node* head, Node** left, Node** right);
	Node* pMergeLists(Node* left, Node* right);

	void pComboMergeSort(Node** origHead, int upperBound);
	//int pComboSplitList(Node* origHead, Node** left, Node** right);


	//TODO: Merge sort***

	// -----------------------------------
	// data
	// -----------------------------------

	Node			*pHead;
	DestructCommand *privFunctor;	
	int  NumNodes;
	int  mCutoffLength;

};

#endif 

// ---  End of File ---------------
