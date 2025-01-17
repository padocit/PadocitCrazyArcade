#pragma once

#include <Level/Level.h>
#include <Math/Vec2.h>

/* 소코반 게임 레벨 */
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

	// 플레이어 이동 가능 유무
	bool CanPlayerMove(const Vec2& pos);

	// 물풍선 터짐 범위 가능 유무
	bool CanBalloonBomb(const Vec2& pos);

	// 물풍선 추가
	void AddBalloon(Balloon* balloon);

	// 물풍선 vs block(box) 충돌
	void ProcessCollisionBalloonAndBlock();
	
	// 물풍선 vs 플레이어 충돌
	void ProcessCollisionBalloonAndPlayer();

	// 물풍선 객체에서 호출하는 삭제 로직
	void DestroyFromBalloons(Balloon* balloon);

	// 플레이어 제거
	void DestroyPlayer(Player* player);

private:

	// TODD: 게임 결과
	//bool CheckGameClear();

private:
	// 렌더링 순서 결정
	Vector<RenderableActor*> map; // wall, ground (Up-cast)
	Vector<Block*> blocks; // TODO: block <- box (상속, 업캐스팅 저장?)
	Vector<Box*> boxes;
	Vector<Balloon*> balloons;

	// TODO: 플레이어 여러명 관리 (container)
	//Vector<Player*> players;
	Player* player = nullptr;

	bool isGameClear = false;

};