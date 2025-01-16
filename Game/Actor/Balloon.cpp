#include "Balloon.h"
#include "Level/GameLevel.h"
#include "Game/Game.h"
#include "Math/Vec2.h"

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

	// ��ǳ�� ������ ���� (���� ������ ����)
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
		// TODO: ���ٱ� Ȯ�� => ���ٱ� ���� ũ�� ��ŭ loop (ex. int step = 2 -> ���� 2ĭ��)
		Vec2 left = this->pos + Vec2(-1, 0);
		Vec2 right = this->pos + Vec2(1, 0);
		Vec2 up = this->pos + Vec2(0, -1);
		Vec2 down = this->pos + Vec2(0, 1);

		// 4���� �׸���
		if (refLevel->CanBalloonBomb(left)) // left
		{
			RenderConsole(left);
		}
		if (refLevel->CanBalloonBomb(right)) // right
		{
			RenderConsole(right);
		}
		if (refLevel->CanBalloonBomb(up)) // up
		{
			RenderConsole(up);
		}
		if (refLevel->CanBalloonBomb(down)) // down
		{
			RenderConsole(down);
		}
	}
}

bool Balloon::Intersect(const RenderableActor& other)
{
	// bomb ���¶�� ����(offset) �� block(box) destroy

	// TODO: ���� = 1ĭ ������ (�ʿ� �� height �߰�)
	
	// other
	Vec2 otherPos = other.Pos();
	int otherMinX = otherPos.x;
	int otherMaxX = otherPos.x + other.Width();
	int otherY = otherPos.y; 

	/* ������ */
	// this 
	int minX = pos.x - bombOffset;
	int maxX = pos.x + bombOffset;

	if (otherMinX > maxX || otherMaxX < minX)
	{
		return false;
	}

	/* ������ */
	// this 
	int minY = pos.y - bombOffset;
	int maxY = pos.y + bombOffset;

	if (otherY > maxY || otherY < minY)
	{
		return false;
	}

	// ���� �� �ƴ϶�� �浹!
	return true;
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
