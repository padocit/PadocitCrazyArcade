#include <iostream>
#include "Engine/Engine.h"
#include "Game/Game.h"
#include "Level/GameLevel.h"

int main()
{
	CheckMemoryLeak(); // Core.h

	Game game;
	game.LoadLevel(new GameLevel());
	game.Run();
}