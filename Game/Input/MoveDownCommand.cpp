#include "MoveDownCommand.h"

#include <Actor/RenderableActor.h>
#include <Actor/Player.h>

void MoveDownCommand::execute(RenderableActor& actor)
{
	Player* player = actor.As<Player>();
	if (player)
	{
		player->MoveDown();
	}
}
