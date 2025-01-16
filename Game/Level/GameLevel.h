#pragma once

#include <Level/Level.h>
#include <Math/Vec2.h>

/* ���ڹ� ���� ���� */
class RenderableActor;
class Player;
class Box;
class GameLevel : public Level
{
	RTTI_DECLARATIONS(GameLevel, Level)

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
	Vector<Box*> boxes;

	Player* player = nullptr;
	
	bool isGameClear = false;

};