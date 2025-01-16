#include "PreCompiledHeader.h"
#include "Engine.h"
#include "Level/Level.h"
#include "Actor/Actor.h"

// static 변수 초기화
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

	// Singleton 객체 설정
	instance = this;

	// 기본 타겟 프레임 속도
	SetTargetFrameRate(60.0f);

	// set clear buffer
	int bufferSize = (screenSize.x + 1) * screenSize.y + 1; // x + 1: 개행문자, + 1: 널문자
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
	// windows timeapi (시간) 사용
	//unsigned long currentTime = 0;
	//unsigned long previousTime = timeGetTime();  // 밀리세컨드 (1/1000초)단위: 부족함
	
	// CPU clock (하드웨어) 사용  // 고해상도 카운터 (10000000)단위 - 메인보드에 있는 시계
	LARGE_INTEGER frequency;
	QueryPerformanceFrequency(&frequency);

	LARGE_INTEGER counter;
	QueryPerformanceCounter(&counter);

	// 첫 deltaTime = 0.0f
	int64_t currentTime = counter.QuadPart;
	int64_t previousTime = currentTime;

	// Game-loop
	while (true)
	{
		if (quit)
		{
			break;
		}

		// 프레임 시간 계산
		//time = timeGetTime();
		QueryPerformanceCounter(&counter);
		currentTime = counter.QuadPart;

		float deltaTime = static_cast<float>(currentTime - previousTime) /
			static_cast<float>(frequency.QuadPart);

		// 프레임 확인
		if (deltaTime >= targetOneFrameTime)
		{
			// 일부는 프레임 제한에서 뺄 수 있음. (ex. Render는 밖으로)
			ProcessInput();

			if (shouldUpdate)
			{
				Update(deltaTime);
				Render(); // 병목
			}

			SavePreviousKeyStates();

			previousTime = currentTime;

			// Actor 삭제
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
	// 예외처리 
	if (mainLevel == nullptr)
	{
		return;
	}

	shouldUpdate = false; // (이것 때문에 Engine에서의 해당 AddActor 필요)
	mainLevel->AddActor(newActor);
}

void Engine::DestroyActor(Actor* targetActor)
{
	// 예외처리 
	if (mainLevel == nullptr)
	{
		return;
	}

	shouldUpdate = false; // (이것 때문에 Engine에서의 해당 AddActor 필요)
	targetActor->Destroy();
}

void Engine::SetCursorType(CursorType cursorType)
{
	// 1. 커서 속성 구조체
	CONSOLE_CURSOR_INFO info = {};

	switch (cursorType)
	{
	case CursorType::NoCursor:
		info.dwSize = 1;		// 너비 0: bVisible 값 무시해서 보이게 돼버림
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

	// 2. 설정
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
	// 레벨 업데이트
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
	//Clear(); // 계속 같은 맵을 그리는 경우(정적) 필요X

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
