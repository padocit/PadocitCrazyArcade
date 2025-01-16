#include "Balloon.h"
#include "Level/GameLevel.h"
#include "Game/Game.h"

Balloon::Balloon(const Vec2& pos, GameLevel* level)
	: RenderableActor("O"),
	elapsedTime(0.0f), bombTime(2.0f), refLevel(level)
{
	this->pos = pos;
	color = Color::Skyblue;
	balloonState = BalloonState::Normal;
}

void Balloon::Update(float deltaTime)
{
	Super::Update(deltaTime);

	// 물풍선 터지는 로직 (각자 스스로 관리)
	elapsedTime += deltaTime;
	if (elapsedTime >= bombTime)
	{
		SetStateBomb();
	}
}

void Balloon::Render()
{
	Super::Render();

	if (balloonState == BalloonState::Bomb)
	{
		// TODO: 물줄기 확장 => 물줄기 변수 크기 만큼 loop (ex. int step = 2 -> 십자 2칸씩)
		Vec2 left = this->pos + Vec2(-1, 0);
		Vec2 right = this->pos + Vec2(1, 0);
		Vec2 up = this->pos + Vec2(0, -1);
		Vec2 down = this->pos + Vec2(0, 1);

		// 4방향 그리기
		if (refLevel->CanBalloonBomb(left)) // left
		{
			Game::Get().SetCursorPos(left);
			Log("%s", this->image);
		}
		if (refLevel->CanBalloonBomb(right)) // right
		{
			Game::Get().SetCursorPos(right);
			Log("%s", this->image);
		}
		if (refLevel->CanBalloonBomb(up)) // up
		{
			Game::Get().SetCursorPos(up);
			Log("%s", this->image);
		}
		if (refLevel->CanBalloonBomb(down)) // down
		{
			Game::Get().SetCursorPos(down);
			Log("%s", this->image);
		}
	}
}

void Balloon::SetStateBomb()
{
	balloonState = BalloonState::Bomb;
	this->SetImage("+");
}

void Balloon::SetStateLock()
{
	balloonState = BalloonState::Lock;
	this->SetImage("@");
}
