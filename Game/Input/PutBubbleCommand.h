#pragma once

#include <Input/ICommand.h>

class RenderableActor;
class PutBubbleCommand : public ICommand
{
public:
	virtual void execute(RenderableActor& actor);
};