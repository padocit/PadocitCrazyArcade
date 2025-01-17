#pragma once

class RenderableActor;
class ICommand // Interface
{
public:
	virtual ~ICommand() {}
	virtual void execute(RenderableActor& actor) = 0;
};