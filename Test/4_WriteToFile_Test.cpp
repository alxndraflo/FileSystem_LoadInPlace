//----------------------------------------------------------------------------
// Copyright 2019, Ed Keenan, all rights reserved.
//----------------------------------------------------------------------------

#include "Framework.h"
#include "_UnitTestConfiguration.h"

#include "OList.h"
#include "Node.h"
#include "UnitTestDestructCommand.h"

// used for teardown
static OList *pOList_4 = nullptr;
static DestructCommand *pDestCommand_4 = nullptr;

// Test functions helpers
bool FileCloseTest(const char * const pFileName);
bool FileSizeTest(const char * const pFileName);

#if WriteToFile_Test_Enable
TEST_WITH_TEARDOWN(WriteToFile, FileSystem, WriteToFile_Test_Enable)
{
	//-----------------------------------------------------------------------------
	// 0) Create objects
	//-----------------------------------------------------------------------------

	Timer t1;

	//-----------------------------------------------------------------------------
	// 1) Create the original Link List timing
	//-----------------------------------------------------------------------------

	// Do not modify or data this function, you need to leave this routine alone.
	pOList_4 = new OList(25000);

	// Setup the destructor
	pDestCommand_4 = new UnitTestDestructCommand(pOList_4);
	pOList_4->SetDestructCommand(pDestCommand_4);

	// find a specific key
	Node foundNode;

	bool foundFlag = pOList_4->FindKey(0x7f9e1b10, foundNode);

	CHECK(foundNode.key == 0x7F9E1B10);
	CHECK(foundNode.x == 657018931);
	CHECK(foundNode.y == 1315507706);
	CHECK(foundNode.z == 1847085303);
	CHECK(foundFlag == true);

	//-----------------------------------------------------------------------------
	// 2) Write data (OList) to File
	//-----------------------------------------------------------------------------

		//	Make sure you are creating a fresh new file
		system("del /f *.bin");

		t1.Tic();

		// --------------------------------------------------------------
		// ---->  Create this function, OList::WritetoFile(...)  <-------
		// --------------------------------------------------------------

			// ------------------------------------------------------------------------
			// Rules:
			//
			//		File needs to be in Binary
			//	    Use: fopen,fread,fwrite,etc... 
			//		     Needs to use these functions for consistent timing across class
			//		No Streams/boost/STL/modern C++ - allowed
			//
			//		Add additional private methods or data as you see fit to the OList class
			//    
			// ------------------------------------------------------------------------
			// Using pOList... (original list) walk the list 
			//                  create and place data into a binary file 
			//                  make sure you close the file after you fill it with data
			// GRAD Students:
			//     This file needs to be LOAD in PLACE file
			//     Watch lecture, read the notes
			//
			// UNDERGRADS students:
			//     You aren't required to do LOAD in PLACE file
			//     It might be fun to try....
			//
			// Generate the Binary file
			// ------------------------------------------------------------------------
			
			pOList_4->WriteToFile("Data.bin");
		
		t1.Toc();

		CHECK(FileCloseTest("Data.bin") == true);
		CHECK(FileSizeTest("Data.bin") == true);

		Trace::out("\n    Time to create File: %f ms  \n", t1.TimeInSeconds() * 1000.0f);

} TEST_END

TEST_TEARDOWN(WriteToFile, FileSystem)
{
	delete pOList_4;
	delete pDestCommand_4;
}

#endif


// Test if the file is closed
bool FileCloseTest(const char * const pFileName)
{
	assert(pFileName);

	FILE *pTmpHandle2;
	pTmpHandle2 = fopen(pFileName, "rb");
	assert(pTmpHandle2);

	unsigned int data;
	unsigned int numBytes = fread(&data, 1, sizeof(unsigned int), pTmpHandle2);

	ferror(pTmpHandle2);

	return numBytes == sizeof(unsigned int);

}

// Test if the file is closed
bool FileSizeTest(const char * const pFileName)
{
	assert(pFileName);

	FILE *pTmpHandle2;
	pTmpHandle2 = fopen(pFileName, "rb");
	assert(pTmpHandle2);

	int error = fseek(pTmpHandle2, 0, SEEK_END);
	assert(error == 0);

	int SizeOfFile = ftell(pTmpHandle2);

	ferror(pTmpHandle2);

	return SizeOfFile > sizeof(unsigned int);

}

// ---  End of File ---------------
