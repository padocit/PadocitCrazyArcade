#pragma once

#include "Core.h"
#include "RTTI.h"
#include "Math/Vec2.h"

class ENGINE_API Actor : public RTTI
{
	// RTTI ����
	RTTI_DECLARATIONS(Actor, RTTI)
	friend class Level;

public:
	Actor();
	virtual ~Actor();

	// ���� ó��
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

	// ID(Hash)/Name (��ü ����)

	bool isActive;
	bool isExpired;

};

