#include "Player.h"
#include "Engine/Engine.h"
#include "Game/Game.h"
#include "Level/GameLevel.h"
#include "Actor/Balloon.h"
#include "Input/InputHandlerLocal1P.h"
#include "Input/InputHandlerLocal2P.h"
#include "Input/ICommand.h"

Player::Player(const Vec2& pos, GameLevel* level, Color color, int id)
	: RenderableActor("P"), refLevel(level), 
	maxCountBalloon(1), countBalloon(0),
	elapsedTimeLocked(0.0f), maxDeadTimeLocked(3.0f),
	id(id)
{
	this->pos = pos;
	this->color = color;
	playerState = PlayerState::Normal;

	prevPos = Vec2(0, 0);
	
	oneDeadTimeLocked = maxDeadTimeLocked / 3.0f;
	twoDeadTimeLocked = 2.0f * oneDeadTimeLocked;

	if (id == 0) // 1p
	{
		playerController = new InputHandlerLocal1P();
	}
	else if (id == 1) // 2p
	{
		playerController = new InputHandlerLocal2P();
	}

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
		// Command: Move, PutBalloon, UseItem
		if (playerController)
		{
			ICommand* command = playerController->HandleInput();
			if (command)
			{
				command->execute(*this);
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

void Player::Render()
{
	// TODO: 리팩토링.. (hotfix) 이전 위치 덮어버리기
	Engine::Get().SetCursorPos(prevPos);
	SetColor(Color::Gray);
	Log("%c", '.');
	SetColor(color);

	Super::Render();
}

void Player::MoveLeft()
{
	if (refLevel->CanPlayerMove(Vec2(pos.x - 1, pos.y)))
	{
		prevPos = pos;
		this->pos.x -= 1;
	}
	// pos.x = pos.x < 0 ? 0 : pos.x; // 필요없음
}

void Player::MoveRight()
{
	if (refLevel->CanPlayerMove(Vec2(pos.x + 1, pos.y)))
	{
		prevPos = pos;
		this->pos.x += 1;
	}
}

void Player::MoveUp()
{
	if (refLevel->CanPlayerMove(Vec2(pos.x, pos.y - 1)))
	{
		prevPos = pos;
		this->pos.y -= 1;
	}
}

void Player::MoveDown()
{
	if (refLevel->CanPlayerMove(Vec2(pos.x, pos.y + 1)))
	{
		prevPos = pos;
		this->pos.y += 1;
	}
}


void Player::PutBalloon()
{
	// 물풍선 생성
	if (countBalloon < maxCountBalloon) // 더 생성 가능한가
	{
		// GameLevel의 balloons에 추가
		refLevel->AddBalloon(new Balloon(this->pos, refLevel, this));
		AddCountBalloon();
	}

}

void Player::UseItem()
{
}

void Player::SetStateLocked()
{
	playerState = PlayerState::Locked;
	this->SetImage("○"); // TODO: 시간 지나면서 점점 차오르다가 터짐 ○ ◎ ●
}
