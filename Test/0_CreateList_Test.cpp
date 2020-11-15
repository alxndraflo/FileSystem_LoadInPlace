//----------------------------------------------------------------------------
// Copyright 2019, Ed Keenan, all rights reserved.
//----------------------------------------------------------------------------

#include "Framework.h"
#include "_UnitTestConfiguration.h"

#include "OList.h"
#include "Node.h"
#include "UnitTestDestructCommand.h"

// For Teardown
static OList *pOList_0 = nullptr;
static DestructCommand *pDestCommand_0 = nullptr;

#if CreateList_Test_Enable
TEST_WITH_TEARDOWN(CreateList, FileSystem, CreateList_Test_Enable)
{
	//-----------------------------------------------------------------------------
	// 0) Create a timer objects
	//-----------------------------------------------------------------------------
	Timer t1;
	Timer t2;

	//-----------------------------------------------------------------------------
	// 1) Create the original Link List timing
	//-----------------------------------------------------------------------------

	// start timer
	t1.Tic();

		// Do not modify or data this function, you need to leave this routine alone.
		pOList_0 = new OList(25000);

		// Setup the destructor
		pDestCommand_0 = new UnitTestDestructCommand(pOList_0);
		pOList_0->SetDestructCommand(pDestCommand_0);

	t1.Toc();

	// find a specific key
	Node foundNode;

	t2.Tic();

		// search the list for timing
		bool foundFlag = pOList_0->FindKey(0x7f9e1b10, foundNode);

	t2.Toc();

	// log the time conversion and proof
	Trace::out("\n");
	Trace::out("Creation of original List: %f ms\n", t1.TimeInSeconds() * 1000.0f);
	Trace::out("\n");
	Trace::out("Original linked list---------------------------\n");
	Trace::out("   Finding Key: %f ms\n", t2.TimeInSeconds()*1000.0f);
	Trace::out(" (Proof)   key: 0x%X  x:%d y:%d z:%d flag:%d\n", foundNode.key, foundNode.x, foundNode.y, foundNode.z, foundFlag);
	Trace::out("\n");

	CHECK(foundNode.key == 0x7F9E1B10);
	CHECK(foundNode.x == 657018931);
	CHECK(foundNode.y == 1315507706);
	CHECK(foundNode.z == 1847085303);
	CHECK(foundFlag == true);

    // This test doesn't count in grading
	_UnitStats.testCount--;
	_UnitStats.testPass--;

} TEST_END


TEST_TEARDOWN(CreateList, FileSystem)
{
	delete pOList_0;
	delete pDestCommand_0;
}
#endif

// ---  End of File ---------------
