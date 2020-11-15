//----------------------------------------------------------------------------
// Copyright 2019, Ed Keenan, all rights reserved.
//----------------------------------------------------------------------------

#ifndef UNIT_TEST_DESTRUCTOR_FUNCTOR_H
#define UNIT_TEST_DESTRUCTOR_FUNCTOR_H

#include "DestructCommand.h"
#include "OList.h"

class UnitTestDestructCommand : public DestructCommand
{
public:
	UnitTestDestructCommand() = delete;
	UnitTestDestructCommand( const UnitTestDestructCommand &) = delete;
	UnitTestDestructCommand & operator = (const UnitTestDestructCommand &) = delete;
	virtual ~UnitTestDestructCommand() = default;

	UnitTestDestructCommand(OList *pInList);

	// This function is called in the destructor
	// Use this as a reference when you create your own functor
	virtual void Command() override;

private:
	OList *pList;
};

#endif

// End of File
