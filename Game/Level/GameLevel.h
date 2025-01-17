#pragma once

#include <Level/Level.h>
#include <Math/Vec2.h>

/* ���ڹ� ���� ���� */
class RenderableActor;
class Player;
class Block;
class Box;
class Balloon;
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
	bool CanBalloonBomb(const Vec2& pos);

	// ��ǳ�� �߰�
	void AddBalloon(Balloon* balloon);

	// ��ǳ�� vs block(box) �浹
	void ProcessCollisionBalloonAndBlock();
	
	// ��ǳ�� vs �÷��̾� �浹
	void ProcessCollisionBalloonAndPlayer();

	// ��ǳ�� ��ü���� ȣ���ϴ� ���� ����
	void DestroyFromBalloons(Balloon* balloon);

	// �÷��̾� ����
	void DestroyPlayer(Player* player);

private:

	// TODD: ���� ���
	//bool CheckGameClear();

private:
	// ������ ���� ����
	Vector<RenderableActor*> map; // wall, ground (Up-cast)
	Vector<Block*> blocks; // TODO: block <- box (���, ��ĳ���� ����?)
	Vector<Box*> boxes;
	Vector<Balloon*> balloons;

	// TODO: �÷��̾� ������ ���� (container)
	//Vector<Player*> players;
	Player* player = nullptr;

	bool isGameClear = false;

};