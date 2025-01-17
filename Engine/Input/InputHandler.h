#pragma once

class ICommand;
class InputHandler
{
public:
	void HandleInput();

private:
	ICommand* left;
	ICommand* right;
	ICommand* up;
	ICommand* down;
	ICommand* space;
};