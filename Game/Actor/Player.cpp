#include "Player.h"
#include "Engine/Engine.h"
#include "Game/Game.h"
#include "Level/GameLevel.h"
#include "Actor/Balloon.h"

Player::Player(const Vec2& pos, GameLevel* level)
	: RenderableActor("P"), refLevel(level)
{
	this->pos = pos;
	color = Color::Red;
}

void Player::Update(float deltaTime)
{
	Super::Update(deltaTime);

	// ESC
	if (Engine::Get().GetKeyDown(VK_ESCAPE))
	{
		//Engine::Get().QuitGame();
		Game::Get().ToggleMenu();
	}

	// ��ǳ�� ����
	if (Engine::Get().GetKeyDown(VK_SPACE))
	{
		// GameLevel�� balloons�� �߰�
		refLevel->AddBalloon(new Balloon(this->pos, refLevel));
	}

	// Move
	// �̵� ���� Ȯ�� - GameLevel::CanPlayerMove
	if (Engine::Get().GetKey(VK_LEFT))
	{
		if (refLevel->CanPlayerMove(Vec2(pos.x - 1, pos.y)))
		{
			this->pos.x -= 1;
		}
		// pos.x = pos.x < 0 ? 0 : pos.x; // �ʿ����
	}
	if (Engine::Get().GetKey(VK_RIGHT))
	{
		if (refLevel->CanPlayerMove(Vec2(pos.x + 1, pos.y)))
		{
			this->pos.x += 1;
		}
	}
	if (Engine::Get().GetKey(VK_UP))
	{
		if (refLevel->CanPlayerMove(Vec2(pos.x, pos.y - 1)))
		{
			this->pos.y -= 1;
		}
	}
	if (Engine::Get().GetKey(VK_DOWN))
	{
		if (refLevel->CanPlayerMove(Vec2(pos.x, pos.y + 1)))
		{
			this->pos.y += 1;
		}
	}

}
