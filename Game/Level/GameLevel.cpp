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

	// �÷��̾� ���� ���� ��ġ
	Vector<Vec2> spawnPoints;

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

		/* Actors */
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
	// �÷��̾� ���� ����
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

	// �÷��̾� ���� ����
	for (int i = 0; i < playerCount; ++i)
	{
		int idx = Random(0, int(spawnPoints.Size() - 1));
		Vec2 spawnPoint = spawnPoints[idx];
		spawnPoints.Erase(idx); // ��ħ ����
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

	// ��ǳ�� �浹 ó��
	ProcessCollisionBubbleAndBlock();
	ProcessCollisionBubbleAndPlayer();

	// TODO: ��/�� ���
	// ���� Ŭ���� = ����
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

void GameLevel::Render()
{
	// Engine-Level-Render ��� X

	/* ����ȭ: ���� ���ļ� �׸��� ���� (������ ����) */

	// Map
	for (auto* actor : map)
	{
		if (players.Size() == 0)
		{
			continue;
		}

		// ��ħ ����
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
			// bomb ���¶��, bubble�� ���� offset ��ŭ �˻�
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
		if (players.Size() == 0)
		{
			return false;
		}

		for (auto* player : players)
		{
			int directionX = pos.x - player->Pos().x;
			int directionY = pos.y - player->Pos().y;

			Vec2 newPosition = searchedBox->Pos() + Vec2(directionX, directionY);

			// �ڽ� �̵� ����?
			for (auto* box : boxes) // �ٸ� �ڽ��� ����
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
			for (auto* block : blocks) // ���� ����
			{
				if (block->Pos() == newPosition)
				{
					return false;
				}
			}
			for (auto* actor : map) // ���� ����
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
	// ����ó��
	if (!searchedActor)
	{
		return false;
	}
	if (searchedActor->As<Wall>())
	{
		return false;
	}
	// Block = �̵� �Ұ�
	for (auto* block : blocks)
	{
		if (block->Pos() == pos)
		{
			return false;
		}
	}
	// Bubble = �̵� �Ұ�
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
	// wall: �׸��� �Ұ���
	// ground, block, box, player: �׸�

	for (auto* actor : map)
	{
		if (actor->Pos() == pos)
		{
			// RTTI
			if (actor->As<Wall>()) // bomb �Ұ�
			{
				return false;
			}
		}
	}

	return true;
}

// ������ �ܺ� setter
void GameLevel::AddBubble(Bubble* bubble)
{
	actors.PushBack(bubble); // �޸� ����
	bubbles.PushBack(bubble); // ������
}

void GameLevel::ProcessCollisionBubbleAndBlock()
{
	// ����ó��
	if (bubbles.Size() == 0 || (blocks.Size() == 0 && boxes.Size() == 0))
	{
		return;
	}

	// ��ȸ (bomb�� ��츸 �浹 ����)
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

			// �浹 ó��
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

			// �浹 ó��
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
	// ����ó��
	if (bubbles.Size() == 0 || players.Size() == 0)
	{
		return;
	}

	// ��ȸ (bombed�� ��츸 �浹 ����)
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
	// players ��ȸ�Ͽ� ã�Ƽ� ����
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
