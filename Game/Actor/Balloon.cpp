#include "Balloon.h"
#include "Level/GameLevel.h"
#include "Game/Game.h"
#include "Math/Vec2.h"

Balloon::Balloon(const Vec2& pos, GameLevel* level)
	: RenderableActor("O"),
	elapsedTime(0.0f), bombTime(2.0f), destroyTime(3.0f), refLevel(level)
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
	if (elapsedTime >= destroyTime)
	{
		refLevel->DestroyFromBalloons(this);
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
	bool horizontalIntersected = false;
	bool verticalIntersected = false;
	
	// other 1x1 ���� ��
	Vec2 otherPos = other.Pos();
	int otherX = otherPos.x;
	int otherY = otherPos.y;

	// this 
	int minX = pos.x - bombOffset;
	int maxX = pos.x + bombOffset;	
	int minY = pos.y - bombOffset;
	int maxY = pos.y + bombOffset;


	/* ������ 1x3 */
	if ((otherX <= maxX && otherX >= minX) &&
		otherY == pos.y)
	{
		return true;
	}

	/* ������ 3x1 */
	if ((otherY <= maxY && otherY >= minY) &&
		otherPos.x == pos.x)
	{
		return true;
	}

	// ���� �� �ƴ϶�� �浹!
	return false;
}

void Balloon::SetStateBomb()
{
	balloonState = BalloonState::Bomb;
	this->SetImage("+");
}
