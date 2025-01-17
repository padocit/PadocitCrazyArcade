#include "InputHandlerLocal2P.h"

#include "Input/MoveLeftCommand.h"
#include "Input/MoveRightCommand.h"
#include "Input/MoveUpCommand.h"
#include "Input/MoveDownCommand.h"
#include "Input/PutBubbleCommand.h"

#include <Engine/Engine.h>

InputHandlerLocal2P::InputHandlerLocal2P()
{
	left = new MoveLeftCommand();
	right = new MoveRightCommand();
	up = new MoveUpCommand();
	down = new MoveDownCommand();
	period = new PutBubbleCommand();
	// TODO: comma = item

}

InputHandlerLocal2P::~InputHandlerLocal2P()
{
	delete left;
	delete right;
	delete up;
	delete down;
	delete period;
}

ICommand* InputHandlerLocal2P::HandleInput()
{
	// Move
	if (Engine::Get().GetKeyDown(VK_LEFT))
	{
		return left;
	}
	if (Engine::Get().GetKeyDown(VK_RIGHT))
	{
		return right;
	}
	if (Engine::Get().GetKeyDown(VK_UP))
	{
		return up;
	}
	if (Engine::Get().GetKeyDown(VK_DOWN))
	{
		return down;
	}

	// Put Bubble
	if (Engine::Get().GetKeyDown(VK_PERIOD))
	{
		return period;
	}

	return nullptr;
}
