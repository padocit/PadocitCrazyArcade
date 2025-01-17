#pragma once

#include <Input/ICommand.h>

class RenderableActor;
class MoveLeftCommand : public ICommand
{
public:
	virtual void execute(RenderableActor& actor);
};