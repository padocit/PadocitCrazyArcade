#include "PreCompiledHeader.h"
#include "Actor/Actor.h"
#include "Level.h"

Level::Level()
{
}

Level::~Level()
{
	for (Actor* actor : actors)
	{
		delete actor;
		actor = nullptr;
	}
}

void Level::AddActor(Actor* newActor)
{
	addRequestedActor = newActor;
}


void Level::ProcessAddedDestroyedActor()
{
	// Delete expired actors
	for (int i = 0; i < actors.Size(); ++i)
	{
		if (actors[i]->isExpired)
		{
			delete actors[i];
			actors[i] = nullptr;
			actors.Erase(i);

			i -= 1; // Array Shifting
		}
	}

	// Add requested actors
	if (addRequestedActor)
	{
		actors.PushBack(addRequestedActor);
		addRequestedActor = nullptr;
	}
}

void Level::Update(float deltaTime)
{
	for (Actor* actor : actors)
	{
		// actor 비활성화 또는 삭제 예정
		if (!actor->isActive || actor->isExpired)
		{
			continue;
		}

		actor->Update(deltaTime);
	}
}

void Level::Render()
{
	for (Actor* actor : actors)
	{
		// actor 비활성화 또는 삭제 예정
		if (!actor->isActive || actor->isExpired)
		{
			continue;
		}

		actor->Render();
	}
}
