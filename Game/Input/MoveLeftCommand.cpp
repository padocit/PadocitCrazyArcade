#include "MoveLeftCommand.h"

#include <Actor/RenderableActor.h>
#include <Actor/Player.h>

void MoveLeftCommand::execute(RenderableActor& actor)
{
	Player* player = actor.As<Player>();
	if (player)
	{
		player->MoveLeft();
	}
}
