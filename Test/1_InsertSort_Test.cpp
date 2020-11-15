//----------------------------------------------------------------------------
// Copyright 2019, Ed Keenan, all rights reserved.
//----------------------------------------------------------------------------

#include "Framework.h"
#include "_UnitTestConfiguration.h"

#include "OList.h"
#include "Node.h"
#include "UnitTestDestructCommand.h"

// Used for Teardown
static OList *pOList_1 = nullptr;
static DestructCommand *pDestCommand_1 = nullptr;

#if Insert_Test_Enable
TEST_WITH_TEARDOWN(Insert, FileSystem, Insert_Test_Enable)
{
	//-----------------------------------------------------------------------------
	// 0) Create objects
	//-----------------------------------------------------------------------------

	Timer t1;

	//-----------------------------------------------------------------------------
	// 1) Create the original Link List timing
	//-----------------------------------------------------------------------------

	// Do not modify or data this function, you need to leave this routine alone.
	pOList_1 = new OList(25000);
	assert(pOList_1);

	// find a specific key
	Node foundNode;

	bool foundFlag = pOList_1->FindKey(0x7f9e1b10, foundNode);

	CHECK(foundNode.key == 0x7F9E1B10);
	CHECK(foundNode.x == 657018931);
	CHECK(foundNode.y == 1315507706);
	CHECK(foundNode.z == 1847085303);
	CHECK(foundFlag == true);

	//-----------------------------------------------------------------------------
	// 2) Insertion Sort Timing
	//-----------------------------------------------------------------------------

	t1.Tic();
		
		// ---------------------------------------------------------
		// ---->  Create this function, use insertion sort  <-------
		// ---------------------------------------------------------
		pOList_1->InsertionSort();

		// Setup the destructor
		pDestCommand_1 = new UnitTestDestructCommand(pOList_1);
		pOList_1->SetDestructCommand(pDestCommand_1);

	t1.Toc();

	// Make sure new list is proper
	bool result = OList::VerifySortOrder(pOList_1);
	CHECK(result == true);

	Trace::out("     Insertion Time: %f ms\n", t1.TimeInSeconds() * 1000.0f);

} TEST_END

TEST_TEARDOWN(Insert, FileSystem)
{
	delete pOList_1;
	delete pDestCommand_1;
}

#endif

// ---  End of File ---------------
