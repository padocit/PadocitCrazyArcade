#include "PutBalloonCommand.h"

#include <Actor/RenderableActor.h>
#include <Actor/Player.h>

void PutBalloonCommand::execute(RenderableActor& actor)
{
	Player* player = actor.As<Player>();
	if (player)
	{
		player->PutBalloon();
	}
}
