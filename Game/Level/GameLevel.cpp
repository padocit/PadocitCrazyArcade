#include "GameLevel.h"
#include "Engine/Engine.h"
#include "Game/Game.h"

#include "Actor/Wall.h"
#include "Actor/Ground.h"
#include "Actor/Box.h"
#include "Actor/Player.h"
#include "Actor/Block.h"
#include "Actor/Bubble.h"

#include "Engine/Timer.h"

GameLevel::GameLevel()
	: playerCount(2)
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

	// 플레이어 랜덤 스폰 위치
	Vector<Vec2> spawnPoints;

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

		/* Actors */
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

			spawnPoints.PushBack(Vec2(xPos, yPos));
		}
		++xPos;
	}
	// 플레이어 색상 결정
	for (int i = 0; i < playerCount; ++i)
	{
		switch (i)
		{
		case 0:
			playerColors.PushBack(Color::LightRed);
			break;
		case 1:
			playerColors.PushBack(Color::LightBlue);
			break;
		case 2:
			playerColors.PushBack(Color::Green);
			break;
		case 3:
			playerColors.PushBack(Color::Magenta);
			break;
		default:
			playerColors.PushBack(Color::White);
			break;
		}
	}

	// 플레이어 랜덤 스폰
	for (int i = 0; i < playerCount; ++i)
	{
		int idx = Random(0, int(spawnPoints.Size() - 1));
		Vec2 spawnPoint = spawnPoints[idx];
		spawnPoints.Erase(idx); // 겹침 방지
		players.PushBack(new Player(spawnPoint, this, playerColors[i], i));
		actors.PushBack(players[i]);
	}
	delete[] buffer;

	fclose(file);
}

void GameLevel::Update(float deltaTime)
{
	Super::Update(deltaTime);

	// ESC
	if (Engine::Get().GetKeyDown(VK_ESCAPE))
	{
		//Engine::Get().QuitGame();
		Game::Get().ToggleMenu();
	}

	// 물풍선 충돌 처리
	ProcessCollisionBubbleAndBlock();
	ProcessCollisionBubbleAndPlayer();

	// TODO: 승/패 출력
	// 게임 클리어 = 종료
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
		if (players.Size() == 0)
		{
			continue;
		}

		// 겹침 방지
		bool shouldRender = true;
		for (auto* player : players)
		{
			if (actor->Pos() == player->Pos())
			{
				shouldRender = false;
				break;
			}
		}
		for (auto* block : blocks)
		{
			if (actor->Pos() == block->Pos())
			{
				shouldRender = false;
				break;
			}
		}
		for (auto* box : boxes)
		{
			if (actor->Pos() == box->Pos())
			{
				shouldRender = false;
				break;
			}
		}
		for (auto* bubble : bubbles)
		{
			// bomb 상태라면, bubble이 가진 offset 만큼 검사
			if (bubble->GetBubbleState() == BubbleState::Bombed)
			{
				// x
				if (actor->Pos().x >= bubble->Pos().x - bubble->BombOffset()
					&& actor->Pos().x <= bubble->Pos().x + bubble->BombOffset())
				{
					shouldRender = false;
				}

				// y
				if (actor->Pos().y >= bubble->Pos().y - bubble->BombOffset()
					&& actor->Pos().y <= bubble->Pos().y + bubble->BombOffset())
				{
					shouldRender = false;
				}
			}
			else
			{
				if (actor->Pos() == bubble->Pos())
				{
					shouldRender = false;
					//break;
				}
			}
		}

		if (shouldRender)
		{
			actor->Render();
		}
	}
	// Block
	for (auto* block : blocks)
	{
		block->Render();
	}

	// Box
	for (auto* box : boxes)
	{
		box->Render();
	}

	// Bubble
	for (auto* bubble : bubbles)
	{
		bubble->Render();
	}

	// Player
	for (auto* player : players)
	{
		player->Render();
	}

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
		if (players.Size() == 0)
		{
			return false;
		}

		for (auto* player : players)
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
			for (auto* block : blocks) // 블럭에 막힘
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
	for (auto* block : blocks)
	{
		if (block->Pos() == pos)
		{
			return false;
		}
	}
	// Bubble = 이동 불가
	for (auto* bubble : bubbles)
	{
		if (bubble->Pos() == pos)
		{
			return false;
		}
	}

	return true;
}

bool GameLevel::CanBubbleBomb(const Vec2& pos)
{
	// wall: 그리기 불가능
	// ground, block, box, player: 그림

	for (auto* actor : map)
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
void GameLevel::AddBubble(Bubble* bubble)
{
	actors.PushBack(bubble); // 메모리 관리
	bubbles.PushBack(bubble); // 렌더링
}

void GameLevel::ProcessCollisionBubbleAndBlock()
{
	// 예외처리
	if (bubbles.Size() == 0 || (blocks.Size() == 0 && boxes.Size() == 0))
	{
		return;
	}

	// 순회 (bomb인 경우만 충돌 감지)
	for (auto* bubble : bubbles)
	{ 
		if (bubble->GetBubbleState() != BubbleState::Bombed)
		{
			continue;
		}

		for (int i = 0; i < blocks.Size(); ++i)
		{
			Block* block = blocks[i];

			if (!block->IsActive())
			{
				continue;
			}

			// 충돌 처리
			if (bubble->Intersect(*block))
			{
				blocks.Erase(i);
				block->Destroy();
			}
		}

		for (int i = 0; i < boxes.Size(); ++i)
		{
			Box* box = boxes[i];

			if (!box->IsActive())
			{
				continue;
			}

			// 충돌 처리
			if (bubble->Intersect(*box))
			{
				boxes.Erase(i);
				box->Destroy();
			}
		}
	}
}

void GameLevel::ProcessCollisionBubbleAndPlayer()
{
	// 예외처리
	if (bubbles.Size() == 0 || players.Size() == 0)
	{
		return;
	}

	// 순회 (bombed인 경우만 충돌 감지)
	for (auto* bubble : bubbles)
	{
		if (bubble->GetBubbleState() != BubbleState::Bombed)
		{
			continue;
		}

		for (auto* player : players)
		{
			if (!player->IsActive())
			{
				continue;
			}

			if (bubble->Intersect(*player))
			{
				player->SetStateLocked();
			}
		}
	}
}

void GameLevel::DestroyFromBubbles(Bubble* bubble)
{
	for (int i = 0; i < bubbles.Size(); ++i)
	{
		if (bubbles[i] == bubble)
		{
			bubbles.Erase(i);
			bubble->OwnPlayer().SubCountBubble();
			bubble->Destroy();
		}
	}
}

void GameLevel::DestroyPlayer(Player* destroyPlayer)
{
	// players 순회하여 찾아서 제거
	for (int i = 0; i < players.Size(); ++i)
	{
		if (players[i] == destroyPlayer)
		{
			players.Erase(i);
			destroyPlayer->Destroy();
			return;
		}
	}
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
