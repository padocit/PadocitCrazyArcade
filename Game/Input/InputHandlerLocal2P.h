#pragma once

#include "Input/InputHandler.h"

class InputHandlerLocal2P : public InputHandler
{
public:
	InputHandlerLocal2P();
	~InputHandlerLocal2P();

	virtual ICommand* HandleInput() override;

private:
	ICommand* left = nullptr;
	ICommand* right = nullptr;
	ICommand* up = nullptr;
	ICommand* down = nullptr;
	ICommand* period = nullptr; // .
	ICommand* comma = nullptr; // ,
};