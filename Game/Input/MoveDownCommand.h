#pragma once

#include <Input/ICommand.h>

class RenderableActor;
class MoveDownCommand : public ICommand
{
public:
	virtual void execute(RenderableActor& actor);
};