//----------------------------------------------------------------------------
// Copyright 2019, Ed Keenan, all rights reserved.
//----------------------------------------------------------------------------

#ifndef DESTRUCT_COMMAND_H
#define DESTRUCT_COMMAND_H

class DestructCommand
{
public:
	DestructCommand() = default;
	DestructCommand(const DestructCommand &) = default;
	DestructCommand & operator = (const DestructCommand &) = default;
	virtual ~DestructCommand() = default;

	// abstract method... forces derived to implement this method
	virtual void Command() = 0;
};

#endif

// End of File
