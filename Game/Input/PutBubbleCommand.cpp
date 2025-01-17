#include "PutBubbleCommand.h"

#include <Actor/RenderableActor.h>
#include <Actor/Player.h>

void PutBubbleCommand::execute(RenderableActor& actor)
{
	Player* player = actor.As<Player>();
	if (player)
	{
		player->PutBubble();
	}
}
