#include "MoveRightCommand.h"

#include <Actor/RenderableActor.h>
#include <Actor/Player.h>

void MoveRightCommand::execute(RenderableActor& actor)
{
	Player* player = actor.As<Player>();
	if (player)
	{
		player->MoveRight();
	}
}
