#include "Bubble.h"
#include "Level/GameLevel.h"
#include "Game/Game.h"
#include "Math/Vec2.h"

Bubble::Bubble(const Vec2& pos, GameLevel* level, Player* ownPlayer)
	: RenderableActor("��"),
	elapsedTime(0.0f), bombTime(1.5f), destroyTime(2.5f), 
	refLevel(level), ownPlayer(ownPlayer)
{
	this->pos = pos;
	color = Color::Cyan;
	bubbleState = BubbleState::Normal;
}

void Bubble::Update(float deltaTime)
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
		refLevel->DestroyFromBubbles(this);
	}
}

void Bubble::Render()
{
	Super::Render();

	if (bubbleState == BubbleState::Bombed)
	{
		// TODO: ���ٱ� Ȯ�� => ���ٱ� ���� ũ�� ��ŭ loop (ex. int step = 2 -> ���� 2ĭ��)
		Vec2 left = this->pos + Vec2(-1, 0);
		Vec2 right = this->pos + Vec2(1, 0);
		Vec2 up = this->pos + Vec2(0, -1);
		Vec2 down = this->pos + Vec2(0, 1);

		// 4���� �׸���
		if (refLevel->CanBubbleBomb(left)) // left
		{
			RenderConsole(left);
		}
		if (refLevel->CanBubbleBomb(right)) // right
		{
			RenderConsole(right);
		}
		if (refLevel->CanBubbleBomb(up)) // up
		{
			RenderConsole(up);
		}
		if (refLevel->CanBubbleBomb(down)) // down
		{
			RenderConsole(down);
		}
	}
}

bool Bubble::Intersect(const RenderableActor& other)
{
	// other = 1x1 ���� ��
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

	// ���� ���̶�� �浹X
	return false;
}

void Bubble::SetStateBomb()
{
	bubbleState = BubbleState::Bombed;
	this->SetImage("+");
}
