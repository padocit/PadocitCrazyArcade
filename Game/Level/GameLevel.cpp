#include "GameLevel.h"
#include "Engine/Engine.h"

#include "Actor/Wall.h"
#include "Actor/Ground.h"
#include "Actor/Box.h"
#include "Actor/Player.h"
#include "Actor/Block.h"
#include "Actor/Balloon.h"

#include "Engine/Timer.h"

GameLevel::GameLevel()
{
	/* Hide cursor */
	Engine::Get().SetCursorType(CursorType::NoCursor);

	/* Load Level */

	// Open file (C style)
	FILE* file = nullptr;
	fopen_s(&file, "../Assets/Maps/Map14.txt", "rb");

	if (!file)
	{
		std::cout << "Faile to open map file.\n";
		__debugbreak();
		return;
	}

	// Read file
	fseek(file, 0, SEEK_END); // FP(File Position) 맨끝으로 이동
	size_t readSize = ftell(file); // FP 위치값
	fseek(file, 0, SEEK_SET); // FP 파일 첫 위치로 이동 // rewind(file);

	char* buffer = new char[readSize + 1];
	size_t bytesRead = fread(buffer, 1, readSize, file); // 읽은 후 FP 위치값 반환

	if (readSize != bytesRead)
	{
		std::cout << "파일 크기와 실제 읽어온 파일 크기가 다름.\n";
		__debugbreak();
		return;
	}
	buffer[readSize] = '\0';

	// File Read Index
	int index = 0;

	// 생성 위치 좌표 
	int xPos = 0;
	int yPos = 0;

	// Parsing (해석) - 한 문자씩 출력
	while (index < int(bytesRead))
	{
		char mapChar = buffer[index++];

		if (mapChar == '\n')
		{
			xPos = 0;
			yPos += 1;
			continue;
		}

		if (mapChar == 'H') // Wall 
		{
			//AddActor(new Wall(Vec2(xPos, yPos))); // 해당 함수는 한 프레임에 한 액터만 추가하므로 불가
			Wall* wall = new Wall(Vec2(xPos, yPos));
			actors.PushBack(wall); // 메모리 해제(관리)용 저장
			map.PushBack(wall);    // 렌더링 용 저장
		}
		else if (mapChar == '.') 
		{
			Ground* ground = new Ground(Vec2(xPos, yPos));
			actors.PushBack(ground);
			map.PushBack(ground);
		}
		else if (mapChar == 'B')
		{
			Ground* ground = new Ground(Vec2(xPos, yPos));
			actors.PushBack(ground);
			map.PushBack(ground);

			Block* block = new Block(Vec2(xPos, yPos));
			actors.PushBack(block);
			blocks.PushBack(block);
		}
		else if (mapChar == '#') // Box
		{
			Ground* ground = new Ground(Vec2(xPos, yPos));
			actors.PushBack(ground);
			map.PushBack(ground);

			Box* box = new Box(Vec2(xPos, yPos));
			actors.PushBack(box); 
			boxes.PushBack(box);
		}
		else if (mapChar == 'P') // TODO: Player Random Spawn
		{
			Ground* ground = new Ground(Vec2(xPos, yPos));
			actors.PushBack(ground);
			map.PushBack(ground);

			player = new Player(Vec2(xPos, yPos), this);
			actors.PushBack(player);
		}

		++xPos;
	}
	delete[] buffer;

	fclose(file);
}

void GameLevel::Update(float deltaTime)
{
	Super::Update(deltaTime);

	// TODO: 승/패
	// 게임 클리어 = 게임 종료
	if (isGameClear)
	{
		// Engine의 Timer 사용
		static Timer timer(0.1f);
		timer.Update(deltaTime);
		if (!timer.IsTimeOut())
		{
			return;
		}

		// 메시지 출력
		Engine::Get().SetCursorPos(0, Engine::Get().ScreenSize().y);
		Log("Game Clear!");

		Sleep(2000);

		Engine::Get().QuitGame();
	}
}

void GameLevel::Render() 
{
	// Engine-Level-Render 사용 X

	/* 최적화: 액터 겹쳐서 그리지 않음 (깜빡임 제거) */

	// Map
	for (auto* actor : map)
	{
		if (actor->Pos() == player->Pos())
		{
			continue;
		}

		bool shouldRender = true;
		for (auto& block : blocks)
		{
			if (actor->Pos() == block->Pos())
			{
				shouldRender = false;
				break;
			}
		}
		for (auto& box : boxes)
		{
			if (actor->Pos() == box->Pos())
			{
				shouldRender = false;
				break;
			}
		}
		for (auto& balloon : balloons)
		{
			if (actor->Pos() == balloon->Pos())
			{
				shouldRender = false;
				break;
			}
		}

		if (shouldRender)
		{
			actor->Render();
		}
	}
	// Block
	for (auto& block : blocks)
	{
		block->Render();
	}

	// Box
	for (auto& box : boxes)
	{
		box->Render();
	}

	// Balloon
	for (auto& balloon : balloons)
	{
		balloon->Render();
	}

	// Player
	player->Render();
}

bool GameLevel::CanPlayerMove(const Vec2& pos)
{
	/* 게임 클리어 = 게임 종료 */
	if (isGameClear)
	{
		return false;
	}

	/* 박스 밀기 로직 */
	// 박스 검색
	Box* searchedBox = nullptr;
	for (auto* box : boxes)
	{
		if (box->Pos() == pos)
		{
			searchedBox = box;
			break;
		}
	}
	// 박스 밀기
	if (searchedBox)
	{
		int directionX = pos.x - player->Pos().x;
		int directionY = pos.y - player->Pos().y;

		Vec2 newPosition = searchedBox->Pos() + Vec2(directionX, directionY);

		// 박스 이동 가능?
		for (auto* box : boxes) // 다른 박스에 막힘
		{
			if (box == searchedBox)
			{
				continue;
			}

			if (box->Pos() == newPosition)
			{
				return false;
			}
		}
		for (auto& block : blocks) // 블럭에 막힘
		{
			if (block->Pos() == newPosition)
			{
				return false;
			}
		}
		for (auto* actor : map) // 벽에 막힘
		{
			if (actor->Pos() == newPosition)
			{
				// RTTI
				if (actor->As<Wall>()) // 이동 불가
				{
					return false;
				}
				if (actor->As<Ground>()) // 이동 가능
				{
					searchedBox->SetPos(newPosition);
					//isGameClear = CheckGameClear();
					return true;
				}
			}
		}
	}

	/* 플레이어 이동 가능 검사 */
	RenderableActor* searchedActor = nullptr;
	for (auto* actor : map) // map: wall, ground
	{
		if (actor->Pos() == pos)
		{
			searchedActor = actor;
			break;
		}
	}
	// 예외처리
	if (!searchedActor)
	{
		return false;
	}
	if (searchedActor->As<Wall>())
	{
		return false;
	}
	// Block = 이동 불가
	for (auto& block : blocks)
	{
		if (block->Pos() == pos)
		{
			return false;
		}
	}
	// Balloon = 이동 불가
	for (auto& balloon : balloons)
	{
		if (balloon->Pos() == pos)
		{
			return false;
		}
	}

	return true;
}

bool GameLevel::CanBalloonBomb(const Vec2& pos)
{
	// TODO: 구현 (Motive = CanPlayerMove)
	// wall: 그리기 불가능
	// ground, block, box, player: 그림

	for (auto& actor : map)
	{
		if (actor->Pos() == pos)
		{
			// RTTI
			if (actor->As<Wall>()) // bomb 불가
			{
				return false;
			}
		}
	}

	return true;
}

// 일종의 외부 setter
void GameLevel::AddBalloon(Balloon* balloon)
{
	actors.PushBack(balloon); // 메모리 관리
	balloons.PushBack(balloon); // 렌더링
}

//bool GameLevel::CheckGameClear()
//{
//	int currentScore = 0;
//	int targetScore = int(targets.Size());
//
//	for (auto& box : boxes)
//	{
//		for (auto& target : targets)
//		{
//			if (box->Pos() == target->Pos())
//			{
//				++currentScore;
//				continue;
//			}
//		}
//	}
//
//	return currentScore == targetScore;
//}
