//----------------------------------------------------------------------------
// Copyright 2019, Ed Keenan, all rights reserved.
//----------------------------------------------------------------------------

#include "Framework.h"
#include "_UnitTestConfiguration.h"

#include "OList.h"
#include "Node.h"
#include "UnitTestDestructCommand.h"
#include "CustomDestructCommand.h"

static OList *pOList_5 = nullptr;
static OList *pNewOList = nullptr;
static DestructCommand *pDestCommand_5 = nullptr;
static DestructCommand *pDestCommand_Custom = nullptr;

#if ReadFromFile_Test_Enable
TEST_WITH_TEARDOWN(ReadFromFile, FileSystem, ReadFromFile_Test_Enable)
{
	//-----------------------------------------------------------------------------
	// 0) Create objects
	//-----------------------------------------------------------------------------

	Timer t1;
	Timer t2;

	//-----------------------------------------------------------------------------
	// 1) Create the original Link List timing
	//-----------------------------------------------------------------------------

	// Do not modify or data this function, you need to leave this routine alone.
	pOList_5 = new OList(25000);

	// Setup the destructor
	pDestCommand_5 = new UnitTestDestructCommand(pOList_5);
	pOList_5->SetDestructCommand(pDestCommand_5);

	// find a specific key
	Node foundNode;

	bool foundFlag = pOList_5->FindKey(0x7f9e1b10, foundNode);

	CHECK(foundNode.key == 0x7F9E1B10);
	CHECK(foundNode.x == 657018931);
	CHECK(foundNode.y == 1315507706);
	CHECK(foundNode.z == 1847085303);
	CHECK(foundFlag == true);

	//-----------------------------------------------------------------------------
	// 2) Read data from File to OList
	//-----------------------------------------------------------------------------

	t1.Tic();

		// ------------------------------------------------------------------------
		// Rules:
		//
		// Read the Binary file and reconstruct the OList from the File
		//
		//		File needs to be in Binary
		//	    Use: fopen,fread,fwrite,etc... 
		//		     Needs to use these functions for consistent timing across class
		//		No Streams/boost/STL/modern C++ - allowed
		//
		//		Add additional private methods or data as you see fit to the OList class
		//
		// ------------------------------------------------------------------------
		// Using your file system, 
		//				  Read YOUR FILE and reconstruct a new OList into pNewOlist
		//                Make sure you close the file after you the creation 
		//
		// GRAD Students:
		//     This file needs to be "LOAD in PLACE" flie
		//	   Recreation of List should not be more than 2 or 3 new() calls in total
		//     Make sure you flip the LOAD_IN_PLACE to TRUE;
		//     Watch lecture, read the notes
		//
		// UNDERGRADS students:
		//     You aren't required to do LOAD in PLACE file
		//     It might be fun to try....
		//
		// ------------------------------------------------------------------------

		pNewOList = new OList("Data.bin", 25000);

		// Setup the destructor
		pDestCommand_Custom = new CustomDestructCommand(pNewOList);
		pNewOList->SetDestructCommand(pDestCommand_Custom);

	t1.Toc();


	//-----------------------------------------------------------------------------
	// 3) Verify data
	//-----------------------------------------------------------------------------

	t2.Tic();
		bool VerifyResult = OList::Verify(pNewOList, pOList_5);
	t2.Toc();

	CHECK(VerifyResult == true);

	Trace::out("  Time to recreate list: %f ms  \n", t1.TimeInSeconds() * 1000.0f);
	Trace::out("\n  Verify Time: %f ms  Result: %d\n", t2.TimeInSeconds() * 1000.0f, VerifyResult);

} TEST_END

TEST_TEARDOWN(ReadFromFile, FileSystem)
{
	delete pOList_5;
	delete pDestCommand_5;
	delete pNewOList;
	delete pDestCommand_Custom;
}

#endif

// ---  End of File ---------------
