#pragma once

#include <Input/ICommand.h>

class RenderableActor;
class MoveUpCommand : public ICommand
{
public:
	virtual void execute(RenderableActor& actor);
};