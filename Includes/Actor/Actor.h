#pragma once

#include "Core.h"
#include "RTTI.h"
#include "Math/Vec2.h"

class ENGINE_API Actor : public RTTI
{
	// RTTI 선언
	RTTI_DECLARATIONS(Actor, RTTI)
	friend class Level;

public:
	Actor();
	virtual ~Actor();

	// 루프 처리
	virtual void Update(float deltaTime);
	virtual void Render();

	// Getter/Setter
	virtual void SetPos(const Vec2& newPos);
	inline Vec2 Pos() const;

	inline bool IsActive() const { return isActive && !isExpired; }
	inline void SetActive(bool active) { isActive = active; }
	inline void Destroy() { isExpired = true; }

protected:
	Vec2 pos;

	// ID(Hash)/Name (객체 고유)

	bool isActive;
	bool isExpired;

};

