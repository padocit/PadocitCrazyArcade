#include "InputHandlerLocal1P.h"

#include "Input/MoveLeftCommand.h"
#include "Input/MoveRightCommand.h"
#include "Input/MoveUpCommand.h"
#include "Input/MoveDownCommand.h"
#include "Input/PutBubbleCommand.h"

#include <Engine/Engine.h>

InputHandlerLocal1P::InputHandlerLocal1P()
	: InputHandler()
{
	d = new MoveLeftCommand();
	g = new MoveRightCommand();
	r = new MoveUpCommand();
	f = new MoveDownCommand();
	s = new PutBubbleCommand();
	// TODO: a = item
}

InputHandlerLocal1P::~InputHandlerLocal1P()
{
	delete d;     
	delete g;     
	delete r;     
	delete f;     
	delete s;
}

ICommand* InputHandlerLocal1P::HandleInput()
{
	// Move
	if (Engine::Get().GetKeyDown(int('D')))
	{
		return d;
	}
	if (Engine::Get().GetKeyDown(int('G')))
	{
		return g;
	}
	if (Engine::Get().GetKeyDown(int('R')))
	{
		return r;
	}
	if (Engine::Get().GetKeyDown(int('F')))
	{
		return f;
	}

	// Put Bubble
	if (Engine::Get().GetKeyDown(int('S')))
	{
		return s;
	}

	return nullptr;
}
