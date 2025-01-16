#pragma once

#include "PreCompiledHeader.h"
#include "Core.h"
#include "RTTI.h"
#include "Container/Vector.h"

// Forward-declaration
class Actor;
class ENGINE_API Level : public RTTI
{
	// RTTI 정의
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

	// 한 프레임 당 액터 하나만 추가 가능 (확장 = 배열 사용)
	Actor* addRequestedActor = nullptr; 
};

