#pragma once

#include "Input/InputHandler.h"

class InputHandlerLocal1P : public InputHandler
{
public:
	InputHandlerLocal1P();
	~InputHandlerLocal1P();

	virtual ICommand* HandleInput() override;

private:
	ICommand* d = nullptr;
	ICommand* g = nullptr;
	ICommand* r = nullptr;
	ICommand* f = nullptr;
	ICommand* s = nullptr;
	ICommand* a = nullptr;
};