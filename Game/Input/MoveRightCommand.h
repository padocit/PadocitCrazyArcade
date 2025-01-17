#pragma once

#include <Input/ICommand.h>

class RenderableActor;
class MoveRightCommand : public ICommand
{
public:
	virtual void execute(RenderableActor& actor);
};