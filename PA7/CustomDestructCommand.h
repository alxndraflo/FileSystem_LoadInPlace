//----------------------------------------------------------------------------
// Copyright 2019, Ed Keenan, all rights reserved.
//----------------------------------------------------------------------------

#ifndef CUSTOM_DESTRUCTOR_FUNCTOR_H
#define CUSTOM_DESTRUCTOR_FUNCTOR_H

#include "DestructCommand.h"
#include "OList.h"

class CustomDestructCommand : public DestructCommand
{
public:
	CustomDestructCommand() = delete;
	CustomDestructCommand(const CustomDestructCommand &) = delete;
	CustomDestructCommand & operator = (const CustomDestructCommand &) = delete;
	virtual ~CustomDestructCommand() = default;

	CustomDestructCommand(OList *pInList);

	// This function is called in the destructor
	// Use this as a reference when you create your own functor
	virtual void Command() override;

private:
	OList *pList;
};

#endif

// End of File
