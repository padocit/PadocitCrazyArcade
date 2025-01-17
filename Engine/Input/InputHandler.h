#pragma once

class ICommand;
class InputHandler
{
public:
	virtual ~InputHandler() {}

	virtual ICommand* HandleInput() = 0;

private:
};