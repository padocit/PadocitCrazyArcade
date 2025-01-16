#include "PreCompiledHeader.h"
#include "Engine.h"
#include "Level/Level.h"
#include "Actor/Actor.h"

// static ���� �ʱ�ȭ
Engine* Engine::instance = nullptr;

Engine& Engine::Get()
{
	// singleton instance
	return *instance;
}


Engine::Engine()
	: quit(false), mainLevel(nullptr), screenSize(40, 25)
{
	// random seed
	srand(unsigned int(time(nullptr)));

	// Singleton ��ü ����
	instance = this;

	// �⺻ Ÿ�� ������ �ӵ�
	SetTargetFrameRate(60.0f);

	// set clear buffer
	int bufferSize = (screenSize.x + 1) * screenSize.y + 1; // x + 1: ���๮��, + 1: �ι���
	emptyStringBuffer = new char[bufferSize];

	memset(emptyStringBuffer, ' ', bufferSize);

	for (int j = 0; j < screenSize.y; ++j)
	{
		//for (int i = 0; i < screenSize.x; ++i)
		//{
		//	emptyStringBuffer[i + (screenSize.x + 1) * j] = ' ';
		//}
		emptyStringBuffer[screenSize.x + (screenSize.x + 1) * j] = '\n';
	}
	emptyStringBuffer[bufferSize - 1] = '\0';

	// debug
#if _DEBUG
	char buffer[2048];
	strcpy_s(buffer, 2048, emptyStringBuffer);
#endif

}

Engine::~Engine()
{
	if (mainLevel != nullptr)
	{
		delete mainLevel;
	}

	delete[] emptyStringBuffer;
}

void Engine::Run()
{
	// windows timeapi (�ð�) ���
	//unsigned long currentTime = 0;
	//unsigned long previousTime = timeGetTime();  // �и������� (1/1000��)����: ������
	
	// CPU clock (�ϵ����) ���  // ���ػ� ī���� (10000000)���� - ���κ��忡 �ִ� �ð�
	LARGE_INTEGER frequency;
	QueryPerformanceFrequency(&frequency);

	LARGE_INTEGER counter;
	QueryPerformanceCounter(&counter);

	// ù deltaTime = 0.0f
	int64_t currentTime = counter.QuadPart;
	int64_t previousTime = currentTime;

	// Game-loop
	while (true)
	{
		if (quit)
		{
			break;
		}

		// ������ �ð� ���
		//time = timeGetTime();
		QueryPerformanceCounter(&counter);
		currentTime = counter.QuadPart;

		float deltaTime = static_cast<float>(currentTime - previousTime) /
			static_cast<float>(frequency.QuadPart);

		// ������ Ȯ��
		if (deltaTime >= targetOneFrameTime)
		{
			// �Ϻδ� ������ ���ѿ��� �� �� ����. (ex. Render�� ������)
			ProcessInput();

			if (shouldUpdate)
			{
				Update(deltaTime);
				Render(); // ����
			}

			SavePreviousKeyStates();

			previousTime = currentTime;

			// Actor ����
			if (mainLevel)
			{
				mainLevel->ProcessAddedDestroyedActor();
			}
			shouldUpdate = true;
		}
	}
}
void Engine::LoadLevel(Level* newLevel)
{
	mainLevel = newLevel; 
}

void Engine::AddActor(Actor* newActor)
{
	// ����ó�� 
	if (mainLevel == nullptr)
	{
		return;
	}

	shouldUpdate = false; // (�̰� ������ Engine������ �ش� AddActor �ʿ�)
	mainLevel->AddActor(newActor);
}

void Engine::DestroyActor(Actor* targetActor)
{
	// ����ó�� 
	if (mainLevel == nullptr)
	{
		return;
	}

	shouldUpdate = false; // (�̰� ������ Engine������ �ش� AddActor �ʿ�)
	targetActor->Destroy();
}

void Engine::SetCursorType(CursorType cursorType)
{
	// 1. Ŀ�� �Ӽ� ����ü
	CONSOLE_CURSOR_INFO info = {};

	switch (cursorType)
	{
	case CursorType::NoCursor:
		info.dwSize = 1;		// �ʺ� 0: bVisible �� �����ؼ� ���̰� �Ź���
		info.bVisible = FALSE;
		break;

	case CursorType::SolidCursor:
		info.dwSize = 100;
		info.bVisible = TRUE;
		break;

	case CursorType::NormalCursor:
		info.dwSize = 20;
		info.bVisible = TRUE;
		break;
	}

	// 2. ����
	SetConsoleCursorInfo(GetStdHandle(STD_OUTPUT_HANDLE), &info);
}

void Engine::SetCursorPos(const Vec2& pos)
{
	SetCursorPos(pos.x, pos.y);
}

void Engine::SetCursorPos(int x, int y)
{
	static HANDLE handle = GetStdHandle(STD_OUTPUT_HANDLE);
	COORD coord = { static_cast<short>(x), static_cast<short>(y) };
	SetConsoleCursorPosition(handle, coord);
}

void Engine::SetTargetFrameRate(float targetFrameRate)
{
	this->targetFrameRate = targetFrameRate;
	targetOneFrameTime = 1.0f / targetFrameRate;
}

bool Engine::GetKey(int key)
{
	return keyState[key].isKeyDown;
}
bool Engine::GetKeyDown(int key)
{
	return keyState[key].isKeyDown && !keyState[key].wasKeyDown;
}
bool Engine::GetKeyUp(int key)
{
	return !keyState[key].isKeyDown && keyState[key].wasKeyDown;
}
void Engine::QuitGame()
{
	quit = true;
}


void Engine::ProcessInput()
{
	for (int i = 0; i < 255; ++i)
	{
		keyState[i].isKeyDown = (GetAsyncKeyState(i) & 0x8000) ? true : false;
	}
}

void Engine::Update(float deltaTime)
{
	// ���� ������Ʈ
	if (mainLevel != nullptr)
	{
		mainLevel->Update(deltaTime);
	}

}

void Engine::Clear()
{
	SetCursorPos(0, 0);

	std::cout << emptyStringBuffer;

	//int height = 29;
	//for (int i = 0; i < height; ++i)
	//{
	//	Log("                               \n");
	//}

	SetCursorPos(0, 0);
}

void Engine::Render()
{
	//Clear(); // ��� ���� ���� �׸��� ���(����) �ʿ�X

	if (mainLevel != nullptr)
	{
		mainLevel->Render();
	}
}

void Engine::SavePreviousKeyStates()
{
	for (int i = 0; i < 255; ++i)
	{
		keyState[i].wasKeyDown = keyState[i].isKeyDown;
	}
}
