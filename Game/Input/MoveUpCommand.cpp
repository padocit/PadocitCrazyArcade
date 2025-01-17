#include "MoveUpCommand.h"

#include <Actor/RenderableActor.h>
#include <Actor/Player.h>

void MoveUpCommand::execute(RenderableActor& actor)
{
	Player* player = actor.As<Player>();
	if (player)
	{
		player->MoveUp();
	}
}
