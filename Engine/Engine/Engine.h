#pragma once

#include "Core.h"
#include "Math/Vec2.h"

// 입력 처리를 위한 구조체
struct KeyState
{
	bool isKeyDown = false;  // 현재 프레임 상태
	bool wasKeyDown = false; // 이전 프레임 상태

};

// 커서 종류
enum class CursorType
{
	NoCursor,
	SolidCursor,
	NormalCursor,
};

class Level;
class Actor;
class ENGINE_API Engine
{
public:

	Engine();
	virtual ~Engine();

	// 엔진 실행
	void Run();

	// 레벨 추가
	void LoadLevel(Level* newLevel);

	// 액터 추가/삭제
	void AddActor(Actor* newActor);
	void DestroyActor(Actor* targetActor);

	// 화면 좌표 다루기
	void SetCursorType(CursorType cursorType);
	void SetCursorPos(const Vec2& pos);
	void SetCursorPos(int x, int y);

	inline Vec2 ScreenSize() const { return screenSize; }

	// 타겟 프레임 설정
	void SetTargetFrameRate(float targetFrameRate);

	// 입력 관련
	bool GetKey(int key);
	bool GetKeyDown(int key);
	bool GetKeyUp(int key);

	// 엔진 종료
	void QuitGame();

	// singleton instance getter
	static Engine& Get();

protected:

	void ProcessInput();			
	void Update(float deltaTime);   // Tick();
	
	void Clear();					// 화면 덧칠
	void Render();					// Render();

	void SavePreviousKeyStates();

protected:

	// 목표 fps
	float targetFrameRate = 60.0f;

	// 목표 spf (second per frame)
	float targetOneFrameTime = 0.0f;

	// 종료할 때 설정
	bool quit;

	// 키 상태 저장 배열
	KeyState keyState[255];

	// Singleton
	static Engine* instance;

	// 메인 레벨
	Level* mainLevel; // Level** levels; // [0] = main level

	// 프레임 업데이트 유무
	bool shouldUpdate = true;

	// 화면 크기
	Vec2 screenSize;

	// 화면 clear용 buffer(blob)
	char* emptyStringBuffer = nullptr;

};