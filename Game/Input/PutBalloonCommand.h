#pragma once

#include <Input/ICommand.h>

class RenderableActor;
class PutBalloonCommand : public ICommand
{
public:
	virtual void execute(RenderableActor& actor);
};