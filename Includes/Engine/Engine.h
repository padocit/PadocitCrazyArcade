#pragma once

#include "Core.h"
#include "Math/Vec2.h"

// �Է� ó���� ���� ����ü
struct KeyState
{
	bool isKeyDown = false;  // ���� ������ ����
	bool wasKeyDown = false; // ���� ������ ����

};

// Ŀ�� ����
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

	// ���� ����
	void Run();

	// ���� �߰�
	void LoadLevel(Level* newLevel);

	// ���� �߰�/����
	void AddActor(Actor* newActor);
	void DestroyActor(Actor* targetActor);

	// ȭ�� ��ǥ �ٷ��
	void SetCursorType(CursorType cursorType);
	void SetCursorPos(const Vec2& pos);
	void SetCursorPos(int x, int y);

	inline Vec2 ScreenSize() const { return screenSize; }

	// Ÿ�� ������ ����
	void SetTargetFrameRate(float targetFrameRate);

	// �Է� ����
	bool GetKey(int key);
	bool GetKeyDown(int key);
	bool GetKeyUp(int key);

	// ���� ����
	void QuitGame();

	// singleton instance getter
	static Engine& Get();

protected:

	void ProcessInput();			
	void Update(float deltaTime);   // Tick();
	
	void Clear();					// ȭ�� ��ĥ
	void Render();					// Render();

	void SavePreviousKeyStates();

protected:

	// ��ǥ fps
	float targetFrameRate = 60.0f;

	// ��ǥ spf (second per frame)
	float targetOneFrameTime = 0.0f;

	// ������ �� ����
	bool quit;

	// Ű ���� ���� �迭
	KeyState keyState[255];

	// Singleton
	static Engine* instance;

	// ���� ����
	Level* mainLevel; // Level** levels; // [0] = main level

	// ������ ������Ʈ ����
	bool shouldUpdate = true;

	// ȭ�� ũ��
	Vec2 screenSize;

	// ȭ�� clear�� buffer(blob)
	char* emptyStringBuffer = nullptr;

};