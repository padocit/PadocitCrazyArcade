#include "InputHandlerLocal1P.h"
#include "Input/InputHandler.h"
#include "Input/MoveLeftCommand.h"
#include "Input/MoveRightCommand.h"
#include "Input/MoveUpCommand.h"
#include "Input/MoveDownCommand.h"
#include "Input/PutBalloonCommand.h"

#include <Engine/Engine.h>

InputHandlerLocal1P::InputHandlerLocal1P()
	: InputHandler()
{
	d      = new MoveLeftCommand();
	g      = new MoveRightCommand();
	r      = new MoveUpCommand();
	f      = new MoveDownCommand();
	lShift = new PutBalloonCommand();
	// TODO: lctrl = item
}

InputHandlerLocal1P::~InputHandlerLocal1P()
{
	delete d;     
	delete g;     
	delete r;     
	delete f;     
	delete lShift;
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

	// Put Balloon
	if (Engine::Get().GetKeyDown(VK_LSHIFT))
	{
		return lShift;
	}

	return nullptr;
}
