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

	// ��ǳ��-block(box) �浹ó��
	void ProcessCollisionBalloonAndBlock();

private:

	// TODD: ���� ���
	//bool CheckGameClear();

private:
	// ������ ���� ����
	Vector<RenderableActor*> map; // wall, ground (Up-cast)
	Vector<Block*> blocks; // TODO: block <- box (���, ��ĳ���� ����?)
	Vector<Box*> boxes;
	Vector<Balloon*> balloons;

	Player* player = nullptr;

	bool isGameClear = false;

};