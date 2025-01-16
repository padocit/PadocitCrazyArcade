#pragma once

#include "Level/Level.h"
#include "Container/Vector.h"

struct MenuItem
{
	using OnSelected = void (*)();

	MenuItem(const char* text, OnSelected onSelected)
	{
		size_t length = strlen(text);
		menuText = new char[length + 1];
		strcpy_s(menuText, length + 1, text);

		this->onSelected = onSelected;
	}

	~MenuItem()
	{
		delete[] menuText;
	}

	char* menuText;
	OnSelected onSelected;
};

class MenuLevel : public Level
{
	GENERATED_BODY(MenuLevel, Level)

public:
	MenuLevel();
	~MenuLevel();

	virtual void Update(float deltaTime) override;
	virtual void Render() override;

private:
	int currentIndex = 0;
	Color selectedColor = Color::Green;
	Color unselectedColor = Color::White;

	Vector<MenuItem*> menuItems;
	int length = 0;
};