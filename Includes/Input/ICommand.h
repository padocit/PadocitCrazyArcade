#pragma once

class Actor;
class ICommand // Interface
{
public:
	virtual ~ICommand() {}
	virtual void execute(Actor& actor) = 0;
};