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
			// TODO: ������ ����
			refLevel->DestroyPlayer(this);
			return;
		}
		if (elapsedTimeLocked >= twoDeadTimeLocked)
		{
			this->SetImage("��");
			return;
		}
		if (elapsedTimeLocked >= oneDeadTimeLocked)
		{
			this->SetImage("��");
			return;
		}
	}
}

void Player::Render()
{
	// TODO: �����丵.. (hotfix) ���� ��ġ ���������
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
	// pos.x = pos.x < 0 ? 0 : pos.x; // �ʿ����
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
	// ��ǳ�� ����
	if (countBalloon < maxCountBalloon) // �� ���� �����Ѱ�
	{
		// GameLevel�� balloons�� �߰�
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
	this->SetImage("��"); // TODO: �ð� �����鼭 ���� �������ٰ� ���� �� �� ��
}
