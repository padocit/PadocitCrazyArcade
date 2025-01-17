#include "Player.h"
#include "Engine/Engine.h"
#include "Game/Game.h"
#include "Level/GameLevel.h"
#include "Actor/Balloon.h"

Player::Player(const Vec2& pos, GameLevel* level)
	: RenderableActor("P"), refLevel(level), 
	maxCountBalloon(1), countBalloon(0),
	elapsedTimeLocked(0.0f), maxDeadTimeLocked(3.0f)
{
	this->pos = pos;
	color = Color::Red;
	playerState = PlayerState::Normal;
	
	oneDeadTimeLocked = maxDeadTimeLocked / 3.0f;
	twoDeadTimeLocked = 2.0f * oneDeadTimeLocked;
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

	if (playerState == PlayerState::Normal)
	{
		// 물풍선 생성
		if (Engine::Get().GetKeyDown(VK_SPACE))
		{
			if (countBalloon < maxCountBalloon) // 더 생성 가능한가
			{
				// GameLevel의 balloons에 추가
				refLevel->AddBalloon(new Balloon(this->pos, refLevel, this));
				AddCountBalloon();
			}
		}

		// Move
		// 이동 가능 확인 - GameLevel::CanPlayerMove
		if (Engine::Get().GetKeyDown(VK_LEFT))
		{
			if (refLevel->CanPlayerMove(Vec2(pos.x - 1, pos.y)))
			{
				this->pos.x -= 1;
			}
			// pos.x = pos.x < 0 ? 0 : pos.x; // 필요없음
		}
		if (Engine::Get().GetKeyDown(VK_RIGHT))
		{
			if (refLevel->CanPlayerMove(Vec2(pos.x + 1, pos.y)))
			{
				this->pos.x += 1;
			}
		}
		if (Engine::Get().GetKeyDown(VK_UP))
		{
			if (refLevel->CanPlayerMove(Vec2(pos.x, pos.y - 1)))
			{
				this->pos.y -= 1;
			}
		}
		if (Engine::Get().GetKeyDown(VK_DOWN))
		{
			if (refLevel->CanPlayerMove(Vec2(pos.x, pos.y + 1)))
			{
				this->pos.y += 1;
			}
		}
	}

	if (playerState == PlayerState::Locked)
	{
		elapsedTimeLocked += deltaTime;
		if (elapsedTimeLocked >= maxDeadTimeLocked)
		{
			// TODO: 터지고 죽음
			refLevel->DestroyPlayer(this);
			return;
		}
		if (elapsedTimeLocked >= twoDeadTimeLocked)
		{
			this->SetImage("●");
			return;
		}
		if (elapsedTimeLocked >= oneDeadTimeLocked)
		{
			this->SetImage("◎");
			return;
		}
	}
}

void Player::SetStateLocked()
{
	playerState = PlayerState::Locked;
	this->SetImage("○"); // TODO: 시간 지나면서 점점 차오르다가 터짐 ○ ◎ ●
}
