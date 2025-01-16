#pragma once

#include "PreCompiledHeader.h"
#include "Core.h"
#include "RTTI.h"
#include "Container/Vector.h"

// Forward-declaration
class Actor;
class ENGINE_API Level : public RTTI
{
	// RTTI ����
	RTTI_DECLARATIONS(Level, RTTI)

public:
	Level();
	virtual ~Level();

	void AddActor(Actor* newActor);
	void ProcessAddedDestroyedActor();

	virtual void Update(float deltaTime);
	virtual void Render();

protected:
	Vector<Actor*> actors;

	// �� ������ �� ���� �ϳ��� �߰� ���� (Ȯ�� = �迭 ���)
	Actor* addRequestedActor = nullptr; 
};

