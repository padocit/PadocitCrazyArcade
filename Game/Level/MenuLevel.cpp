#include "MenuLevel.h"
#include "Game/Game.h"

MenuLevel::MenuLevel()
{
	menuItems.PushBack(new MenuItem("Resume Game", []() { Game::Get().ToggleMenu(); }));
	menuItems.PushBack(new MenuItem("Quit Game", []() { Game::Get().QuitGame(); }));
	length = int(menuItems.Size());
}

MenuLevel::~MenuLevel()
{
	for (auto* item : menuItems)
	{
		delete item;
	}
}

void MenuLevel::Update(float deltaTime)
{
	if (Game::Get().GetKeyDown(VK_ESCAPE))
	{
		Game::Get().ToggleMenu();
	}

	if (Game::Get().GetKeyDown(VK_UP))
	{
		currentIndex = (currentIndex - 1 + length) % length;
	}
	if (Game::Get().GetKeyDown(VK_DOWN))
	{
		currentIndex = (currentIndex + 1) % length;
	}

	if (Game::Get().GetKeyDown(VK_RETURN))
	{
		menuItems[currentIndex]->onSelected();
	}
}

void MenuLevel::Render()
{
	Super::Render();

	Engine::Get().SetCursorPos(0, 0);
	
	SetColor(unselectedColor);
	Log("Crazy Arcade\n\n");

	for (int ix = 0; ix < length; ++ix)
	{
		SetColor(ix == currentIndex ? selectedColor : unselectedColor);
		Log("%s\n", menuItems[ix]->menuText);
	}
}