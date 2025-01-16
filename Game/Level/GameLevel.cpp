#include "GameLevel.h"
#include "Engine/Engine.h"

#include "Actor/Wall.h"
#include "Actor/Ground.h"
#include "Actor/Box.h"
#include "Actor/Player.h"

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
	fseek(file, 0, SEEK_END); // FP(File Position) �ǳ����� �̵�
	size_t readSize = ftell(file); // FP ��ġ��
	fseek(file, 0, SEEK_SET); // FP ���� ù ��ġ�� �̵� // rewind(file);

	char* buffer = new char[readSize + 1];
	size_t bytesRead = fread(buffer, 1, readSize, file); // ���� �� FP ��ġ�� ��ȯ

	if (readSize != bytesRead)
	{
		std::cout << "���� ũ��� ���� �о�� ���� ũ�Ⱑ �ٸ�.\n";
		__debugbreak();
		return;
	}
	buffer[readSize] = '\0';

	// File Read Index
	int index = 0;

	// ���� ��ġ ��ǥ 
	int xPos = 0;
	int yPos = 0;

	// Parsing (�ؼ�) - �� ���ھ� ���
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
			//AddActor(new Wall(Vec2(xPos, yPos))); // �ش� �Լ��� �� �����ӿ� �� ���͸� �߰��ϹǷ� �Ұ�
			Wall* wall = new Wall(Vec2(xPos, yPos));
			actors.PushBack(wall); // �޸� ����(����)�� ����
			map.PushBack(wall);    // ������ �� ����
		}
		else if (mapChar == '.') 
		{
			Ground* ground = new Ground(Vec2(xPos, yPos));
			actors.PushBack(ground);
			map.PushBack(ground);
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

	// ���� Ŭ���� = ���� ����
	if (isGameClear)
	{
		// Engine�� Timer ���
		static Timer timer(0.1f);
		timer.Update(deltaTime);
		if (!timer.IsTimeOut())
		{
			return;
		}

		// �޽��� ���
		Engine::Get().SetCursorPos(0, Engine::Get().ScreenSize().y);
		Log("Game Clear!");

		Sleep(2000);

		Engine::Get().QuitGame();
	}
}

void GameLevel::Render() // Engine-Level-Render ��� X
{
	/* ����ȭ: ���� ���ļ� �׸��� ���� (������ ����) */

	// Map
	for (auto* actor : map)
	{
		if (actor->Pos() == player->Pos())
		{
			continue;
		}

		bool shouldRender = true;
		for (auto* box : boxes)
		{
			if (actor->Pos() == box->Pos())
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

	// TODO: Box vs Player
	// Box
	for (auto* box : boxes)
	{
		box->Render();
	}

	// Player
	player->Render();
}

bool GameLevel::CanPlayerMove(const Vec2& pos)
{
	/* ���� Ŭ���� = ���� ���� */
	if (isGameClear)
	{
		return false;
	}

	/* �ڽ� �б� ���� */
	// �ڽ� �˻�
	Box* searchedBox = nullptr;
	for (auto* box : boxes)
	{
		if (box->Pos() == pos)
		{
			searchedBox = box;
			break;
		}
	}
	// �ڽ� �б�
	if (searchedBox)
	{
		int directionX = pos.x - player->Pos().x;
		int directionY = pos.y - player->Pos().y;

		Vec2 newPosition = searchedBox->Pos() + Vec2(directionX, directionY);

		// �ڽ� �̵� ����?
		for (auto* box : boxes)
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
		for (auto* actor : map)
		{
			if (actor->Pos() == newPosition)
			{
				// RTTI
				if (actor->As<Wall>()) // �̵� �Ұ�
				{
					return false;
				}
				if (actor->As<Ground>()) // �̵� ����
				{
					searchedBox->SetPos(newPosition);
					//isGameClear = CheckGameClear();
					return true;
				}
			}
		}
	}

	/* �÷��̾� �̵� ���� �˻� */
	RenderableActor* searchedActor = nullptr;
	for (auto* actor : map) // map: wall, ground
	{
		if (actor->Pos() == pos)
		{
			searchedActor = actor;
			break;
		}
	}
	// TODO: �ʿ� �� Ȱ��ȭ
	//if (searchedActor->As<Wall>())
	//{
	//	return false;
	//}
	
	// ����ó��
	if (!searchedActor)
	{
		return false;
	}

	if (searchedActor->As<Ground>())
	{
		return true;
	}

	return false;
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
