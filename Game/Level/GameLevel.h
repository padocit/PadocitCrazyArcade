#pragma once

#include <Level/Level.h>
#include <Math/Vec2.h>

/* ���ڹ� ���� ���� */
class RenderableActor;
class Player;
class Block;
class Box;
class GameLevel : public Level
{
	GENERATED_BODY(GameLevel, Level)

public:
	GameLevel();

	virtual void Update(float deltaTime) override;
	virtual void Render() override;
	
	// �÷��̾� �̵� ���� ����
	bool CanPlayerMove(const Vec2& pos);

private:
	// TODD: ���� ���
	//bool CheckGameClear();

private:
	// ������ ���� ����
	Vector<RenderableActor*> map; // walls, floors (Up-cast)
	Vector<Block*> blocks; // TODO: block <- box (���, ��ĳ���� ����?)
	Vector<Box*> boxes;

	Player* player = nullptr;
	
	bool isGameClear = false;

};