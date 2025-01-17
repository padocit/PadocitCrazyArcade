#pragma once

#include <Level/Level.h>
#include <Math/Vec2.h>

/* ���ڹ� ���� ���� */
class RenderableActor;
class Player;
class Block;
class Box;
class Bubble;
class GameLevel : public Level
{
	GENERATED_BODY(GameLevel, Level)

public:
	GameLevel();

	virtual void Update(float deltaTime) override;
	virtual void Render() override;

	// �÷��̾� �̵� ���� ����
	bool CanPlayerMove(const Vec2& pos);

	// ��ǳ�� ���� ���� ���� ����
	bool CanBubbleBomb(const Vec2& pos);

	// ��ǳ�� �߰�
	void AddBubble(Bubble* bubble);

	// ��ǳ�� vs block(box) �浹
	void ProcessCollisionBubbleAndBlock();
	
	// ��ǳ�� vs �÷��̾� �浹
	void ProcessCollisionBubbleAndPlayer();

	// ��ǳ�� ��ü���� ȣ���ϴ� ���� ����
	void DestroyFromBubbles(Bubble* bubble);

	// �÷��̾� ����
	void DestroyPlayer(Player* destroyPlayer);

private:

	// TODD: ���� ���
	//bool CheckGameClear();

private:
	// ������ ���� ����
	Vector<RenderableActor*> map; // wall, ground (Up-cast)
	Vector<Block*> blocks;
	Vector<Box*> boxes;
	Vector<Bubble*> bubbles;

	// �÷��̾� ������ ����
	Vector<Player*> players; //Player* player = nullptr;
	int playerCount;
	Vector<Color> playerColors;

	bool isGameClear = false;

};